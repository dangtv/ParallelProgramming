#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <mpi/mpi.h>

#define  m       20
#define  n       20
#define  T       2
#define  dt      0.01
#define  dx      0.1
#define  D       0.1
//=========================

void DisplayMatrix(float *A, int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) printf("  %.2f", *(A + i * col + j));
        printf("\n");
    }
}
//=========================

void Write2File(float *C) {
    FILE *result = fopen("result2.txt", "a");
    int i, j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            fprintf(result, "%lf\t", *(C + i * n + j));
        }
        fprintf(result, "\n");
    }

    fclose(result);
}
//=========================

void KhoiTao(float *C) {
    int i, j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++) {
            if (i >= (m / 2 - 5) && i < (m / 2 + 5) && j >= (n / 2 - 5) && j < (n / 2 + 5))
                *(C + i * n + j) = 80.0;
            else
                *(C + i * n + j) = 25.0;
        }
}
//=========================

//void FD(float *C, float *dC) {
//    int i, j;
//    float c, u, d, l, r;
//    for (i = 0; i < m; i++)
//        for (j = 0; j < n; j++) {
//            c = *(C + i * n + j);
//            u = (i == 0) ? *(C + i * n + j) : *(C + (i - 1) * n + j);
//            d = (i == m - 1) ? *(C + i * n + j) : *(C + (i + 1) * n + j);
//            l = (j == 0) ? *(C + i * n + j) : *(C + i * n + j - 1);
//            r = (j == n - 1) ? *(C + i * n + j) : *(C + i * n + j + 1);
//            *(dC + i * n + j) = (D / (dx * dx))*(u + d + l + r - 4 * c);
//        }
//}

void FD(float *Cs, float *Cu, float *Cd, float *dCs, int ms) {
    int i, j;
    float c, u, d, l, r;
    for (i = 0; i < ms; i++)
        for (j = 0; j < n; j++) {
            c = *(Cs + i * n + j);
            u = (i == 0) ? *(Cu + j) : *(Cs + (i - 1) * n + j);
            d = (i == ms - 1) ? *(Cd + j) : *(Cs + (i + 1) * n + j);
            l = (j == 0) ? *(Cs + i * n + j) : *(Cs + i * n + j - 1);
            r = (j == n - 1) ? *(Cs + i * n + j) : *(Cs + i * n + j + 1);
            *(dCs + i * n + j) = (D / (dx * dx))*(u + d + l + r - 4 * c);
        }
}

//=========================

int main(int argc, char** argv) {

    // khai bao
    int i, j, count, rank, size;
    MPI_Status stat;

    float t;
    time_t t1, t2;
    t = 0;
    float *C, *dC, *Cs, *dCs;
    float *Cu, *Cd;



    // khoi tao
    // mang toan bo
    if (rank == 0) {
        C = (float *) malloc((m * n) * sizeof (float));
        dC = (float *) malloc((m * n) * sizeof (float));
    }

    // mang cuc bo ma core xu ly
    //    Cs = (float *) malloc((ms * n) * sizeof (float));
    //    dCs = (float *) malloc((ms * n) * sizeof (float));

    // khoi tao bien
    Cu = (float *) malloc((n) * sizeof (float));
    Cd = (float *) malloc((n) * sizeof (float));

    KhoiTao(C);
//    Write2File(C);

    if (rank == 0) {
        printf("Gia tri khoi tao:\n");
        DisplayMatrix(C, m, n);
    }
    count = 0;
    t1 = time(NULL);

    // chia mien tinh toan
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    // ms la so hang cua mien tinh toan
    int ms = m / size;

    Cs = C + rank * ms*n;
    dCs = dC + rank * ms*n;

    while (t <= T) {
        // truyen thong
        //Truyền thông bien tren (up Cu)
        // rank = 0 ung voi truong hop o ngoai cung ben trai nen ko nhan ve gi
        // Tl cua rank 0 mac dinh bang 0
        if (rank == 0) {
            for (i = 0; i < n; i++) *(Cu+i) = *(Cs+i);

            MPI_Send(Cs + (ms - 1) * n, n, MPI_FLOAT, rank + 1, rank, MPI_COMM_WORLD);

        } else if (rank == size - 1) {

            MPI_Recv(Cu, n, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD, &stat);

        } else {

            MPI_Send(Cs + (ms - 1) * n, n, MPI_FLOAT, rank + 1, rank, MPI_COMM_WORLD);
            MPI_Recv(Cu, n, MPI_FLOAT, rank - 1, rank - 1, MPI_COMM_WORLD, &stat);
        }


        // Truyền thông bien duoi (down Cd)
        // rank size - 1 ung voi core cuoi cung nen ko co Tr
        // Tr cua rank size-1 bang 25
        if (rank == size - 1) {
            for (i = 0; i < n; i++) *(Cd+i) = *(Cs+(ms-1)*n+i);
            MPI_Send(Cs, n, MPI_FLOAT, rank - 1, rank, MPI_COMM_WORLD);

        } else if (rank == 0) {

            MPI_Recv(Cd, n, MPI_FLOAT, rank + 1, rank + 1, MPI_COMM_WORLD, &stat);

        } else {

            MPI_Send(Cs, n, MPI_FLOAT, rank - 1, rank, MPI_COMM_WORLD);
            MPI_Recv(Cd, n, MPI_FLOAT, rank + 1, rank + 1, MPI_COMM_WORLD, &stat);
        }

        // xu ly

        FD(Cs, Cu, Cd, dCs, ms);
        for (i = 0; i < ms; i++)
            for (j = 0; j < n; j++)
                *(Cs + i * n + j) = *(Cs + i * n + j) + dt * (*(dCs + i * n + j));
        t = t + dt;
        count = count + 1;
        //        if (count % 5 == 0) Write2File(C);
    }

    MPI_Gather(Cs, ms*n, MPI_INT, C, ms*n, MPI_INT, 0, MPI_COMM_WORLD);

    // in ket qua
    t2 = time(NULL);
    //FD(C, dC);
    if (rank == 0) {
        printf("Gia tri cuoi cung:\n");
        DisplayMatrix(C, m, n);
        printf("\tThe Calculation time:%ld\n", (long) (t2 - t1));
    }
    MPI_Finalize();
    //
    
    return 0;
}

