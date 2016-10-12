/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   multiple_matrix.c
 * Author: dang
 *
 * Created on October 5, 2016, 3:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
/*
 * 
 */

int rank, size;
MPI_Status stat;
// nhan 2 ma tran, ket qua tra ve la 1 ma tran

void matrix_multiple(int *a, int aheight, int awidth, int *b, int bheight, int bwidth) {
    int Mc;
    Mc = aheight / size;
    int * ketqua;
    int *ketqualocal;
    int *alocal;
    int *blocal;

    //    if (awidth == bheight) return NULL; // loi nhan ma tran ko dung kich thuoc
    int sum = 0;
    // chia mien tinh toan
    if (rank == 0) {
        ketqua = (int*) malloc(aheight * bwidth * sizeof (int));
        printf("CPU 0 gui: \n");
        for (int i = 1; i < size; i++) {
            MPI_Send(a + i * awidth*Mc, awidth*Mc, MPI_INT, i, i, MPI_COMM_WORLD);
            MPI_Send(b, bwidth* bheight, MPI_INT, i, 1000 + i, MPI_COMM_WORLD);
        }
        printf("CPU 0 gui xong: \n");

        for (int i = 0; i < Mc; i++) {
            for (int k = 0; k < bwidth; k++) {
                sum = 0;

                for (int j = 0; j < awidth; j++) {


                    sum += (*(a + i * awidth + j)) * (*(b + j * bwidth + k));
                }
                printf("CPU 0 dang tinh ket qua \n");
                *(ketqua + i * bwidth + k) = sum;
                printf("CPU 0 dang tinh xong sum: %d \n", *(ketqua + i * bwidth + k));
            }
            printf("CPU0 tinh xong %d \n", i);
        }
        printf("CPU0 tinh xong");
        for (int i = 1; i < size; i++) {
            MPI_Recv(ketqua + i * bwidth*Mc, Mc*bwidth, MPI_INT, i, i, MPI_COMM_WORLD, &stat);
        }
        printf("CPU0 nhan duoc: ");

        printf("ket qua cuoi la: \n");
        for (int i = 0; i < aheight; i++) {
            for (int j = 0; j < bwidth; j++) {
                printf("%d, ", *(ketqua + i * bwidth + j));

            }
            printf("\n");
        }

    }
    if (rank > 0) {
        alocal = (int*) malloc(Mc * awidth * sizeof (int));
        blocal = (int*) malloc(bwidth * bheight * sizeof (int));
        ketqualocal = (int*) malloc(Mc * bwidth * sizeof (int));
        printf("CPU %d nhan: \n", rank);
        MPI_Recv(alocal, Mc * awidth, MPI_INT, 0, rank, MPI_COMM_WORLD, &stat);
        MPI_Recv(blocal, bheight*bwidth, MPI_INT, 0, 1000 + rank, MPI_COMM_WORLD, &stat);
        printf("CPU %d nhan xong: \n", rank);
        for (int i = 0; i < Mc; i++) {
            for (int k = 0; k < bwidth; k++) {
                sum = 0;

                for (int j = 0; j < awidth; j++) {


                    sum += (*(alocal + i * awidth + j)) * (*(blocal + j * bwidth + k));
                }
                *(ketqualocal + i * bwidth + k) = sum;
            }

        }
        MPI_Send(ketqualocal, Mc * bwidth, MPI_INT, 0, rank, MPI_COMM_WORLD);

        printf("CPU %d gui xong: \n", rank);
    }
}

int main(int argc, char** argv) {


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //    printf("so pro: %d ", size);
    int a[6][3] = {
        {1, 2, 1},
        {1, 1, 1},
        {1, 1, 2},
        {2, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };
    int b[3][2] = {
        {1, 1},
        {1, 1},
        {1, 1}
    };
    matrix_multiple((int*) a, 6, 3, (int *) b, 3, 2);
    MPI_Finalize();
    return (EXIT_SUCCESS);
}

