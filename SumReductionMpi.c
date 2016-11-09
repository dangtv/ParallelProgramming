/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include <mpi.h>
#include <mpi/mpi.h>


#define  n       16

int main(int argc, char** argv) {

    // khai bao
    int i, j, count, rank, size;
    float *sohang, *mang, *sum;
    MPI_Status stat;


    // khoi tao
    // mang toan bo
    if (rank == 0) {
        mang = (float *) malloc((n) * sizeof (float));
        for (i = 0; i < n; i++) *(mang + i) = 13 + i;

    }
    
    sohang = (float *) malloc(2 * sizeof (float));
    sum = (float *) malloc(sizeof (float));

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    //printf("khoi tao xong \n");
    // chia mien tinh toan
    MPI_Scatter(mang, 2, MPI_FLOAT, sohang, 2, MPI_FLOAT, 0, MPI_COMM_WORLD);
    // tinh tong
    printf("scatter xong \n");

    while (size > 1) {
        if (rank < size) {
            //printf("ok %f\n", *(sohang + 1));
            *sum = *sohang + *(sohang + 1);
            //printf("=================ok %f\n", *sum);
            if (rank > (size-1) / 2) {
                MPI_Send(sum, 1, MPI_FLOAT, size - rank - 1, rank, MPI_COMM_WORLD);
            } else {
                MPI_Recv(sohang + 1, 1, MPI_FLOAT, size - rank - 1, size - rank - 1, MPI_COMM_WORLD, &stat);
                *sohang = *sum;
            }
            
        }
        size = size / 2;
    }
    
    //in 
    if(rank ==0){
        *sum = *sohang + *(sohang + 1);
        printf("tong la: %f\n", *sum);
    }

    // tong hop ket qua

    MPI_Finalize();
    //
    
    return 0;
}