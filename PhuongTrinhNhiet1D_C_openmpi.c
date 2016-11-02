/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <malloc.h>
#include <mpi.h>
#include <math.h>
#include <sys/time.h>

#define M 20
#define Time 1
#define dx 0.1
#define dt 0.01
#define D  0.1

int i;
int rank, size;
float t = 0, *T, *dT, *Ts, *dTs;
MPI_Status stat;

void DHB2(float *Ts, float Tl, float Tr, float *dTs, int ms) {
    int i;
    float c, l, r;
    for (i = 0; i < ms; i++) {

        // ignore last point

        c = *(Ts + i);
        l = (i == 0) ? Tl : *(Ts + i - 1);
        r = (i == ms - 1) ? Tr : *(Ts + i + 1);
        *(dTs + i) = D * (l - 2 * c + r) / (dx * dx);
    }
}

int main(int argc, char** argv) {

    // Khai bao bien

    T = (float *) malloc((M) * sizeof (float));
    dT = (float *) malloc((M) * sizeof (float));
    float Tl;
    float Tr;

    // Khoi tao
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    int mc = M / size;

    for (i = 0; i < M; i++) *(T + i) = 25.0;

    Ts = T + rank*mc;
    dTs = dT + rank*mc;
    while (t < Time) {
       
        //Truyền thông phần tử Tl
        // rank = 0 ung voi truong hop o ngoai cung ben trai nen ko nhan ve gi
        // Tl cua rank 0 mac dinh bang 0
        if (rank == 0) {

            Tl = 100;
            MPI_Send(Ts + mc - 1, 1, MPI_FLOAT, rank + 1, rank, MPI_COMM_WORLD);

        } else if (rank == size - 1) {

            MPI_Recv(&Tl, 1, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD, &stat);

        } else {

            MPI_Send(Ts + mc - 1, 1, MPI_FLOAT, rank + 1, rank, MPI_COMM_WORLD);
            MPI_Recv(&Tl, 1, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD, &stat);
        }


        // Truyền thông phần tử Tr
        // rank size - 1 ung voi core cuoi cung nen ko co Tr
        // Tr cua rank size-1 bang 25
        if (rank == size - 1) {

            Tr = 25;
            MPI_Send(Ts, 1, MPI_FLOAT, rank - 1, rank, MPI_COMM_WORLD);

        } else if (rank == 0) {

            MPI_Recv(&Tr, 1, MPI_FLOAT, rank + 1, rank + 1, MPI_COMM_WORLD, &stat);

        } else {

            MPI_Send(Ts, 1, MPI_FLOAT, rank - 1, rank, MPI_COMM_WORLD);
            MPI_Recv(&Tr, 1, MPI_FLOAT, rank + 1, rank + 1, MPI_COMM_WORLD, &stat);
        }
        
        DHB2(Ts, Tl, Tr, dTs, mc);
        for (i = 0; i < mc; i++)
            *(Ts + i) = *(Ts + i) + *(dTs + i) * dt;
        t = t + dt;
    }

    // ham gather: mc la kich thuoc cua du lieu gui di va nhan ve
    MPI_Gather(Ts, mc, MPI_INT, T, mc, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank == 0)
        for (i = 0; i < M; i++) printf("%f \n", *(T + i));
    
    MPI_Finalize();
    return 0;
}
