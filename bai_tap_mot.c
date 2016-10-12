/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   bai_tap_m.c
 * Author: dang
 *
 * Created on September 28, 2016, 4:35 PM
 */


//Bài tập: viết chương trình MPI chạy trên NP process 
//tại CPU0: khởi tạo 2 mảng  
//A[M]  
//B[M]  (M % NP = 0) 
//C[M]  
//chia miên tính toán Mc = M/NP 
//tại CPU0 chia dữ liệu, gửi từng phần đến các CPU tương ứng  
//tính toán: 
//Mỗi CPU   C=A+B trên miền của mình  
//tập hợp dữ liẹu: 
//các CPU khác 0 gửi C về CPU0 
//CPU0 nhận tập hợp, in ra

#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
/*
 * 
 */
#define NP 4
#define M 20
int main(int argc, char** argv) {
    int a[M] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int b[M] = {3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22};
    int c[M];
    int Mc = M/NP;
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Status stat;
    int ac[Mc];
    int bc[Mc];
    int cc[Mc];
    
    if(rank ==0){
        printf("CPU 0 gui: \n");
        for (int i = 1;i < NP+1;i++){
            MPI_Send(a + (i-1)*Mc,Mc,MPI_INT,i,0,MPI_COMM_WORLD);
            MPI_Send(b+ (i-1)*Mc,Mc,MPI_INT,i,0,MPI_COMM_WORLD);
        }
        printf("CPU 0 gui xong: \n");
        for (int i = 1;i < NP+1;i++){
            MPI_Recv(c+(i-1)*Mc,Mc,MPI_INT,i,0,MPI_COMM_WORLD, &stat);
        }
        printf("CPU0 nhan duoc: ");
        for (int i=0;i<M;i++){
            printf("%d, ", c[i]);
        }
    }
    if(rank>0){
        printf("CPU %d nhan: \n", rank);
            MPI_Recv(ac,Mc,MPI_INT,0,0,MPI_COMM_WORLD,&stat);
            MPI_Recv(bc,Mc,MPI_INT,0,0,MPI_COMM_WORLD,&stat);
            printf("CPU %d nhan xong: \n", rank);
            for (int i=0;i<Mc;i++) {cc[i] = ac[i]+bc[i]; }
            MPI_Send(cc,Mc,MPI_INT,0,0,MPI_COMM_WORLD);
            
        }
    
    MPI_Finalize();
    return (EXIT_SUCCESS);
}

