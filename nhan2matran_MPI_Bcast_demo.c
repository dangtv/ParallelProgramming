/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MPI_Bcast_demo.c
 * Author: dang
 *
 * Created on October 12, 2016, 3:31 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <mpi.h>
#include <math.h>
#include <sys/time.h>
#include <mpi/mpi.h>
// Nhap cac kich thuoc cua ma tran
#define  m       8
#define  n       8
#define  p       4
//==================================
void DisplayMatrix(float *A, int row,  int col){
  int i,j;
  for(i=0;i<row;i++){
    for(j=0;j<col;j++) printf("  %0.0f",*(A+i*col+j));
    printf("\n");
  }
}
//==================================
main(int argc, char *argv[])
{

  int NP, rank, mc;
  int i, j, k, sum = 0;
  MPI_Status status;
//==================================
// Khai bao ma tran A, B, C
// va ma tran con Ac, Bc, CC
  float *A, *B, *C, *Ac, *Bc, *Cc;
  A = (float *) malloc ((m*n)*sizeof(float));
  B = (float *) malloc ((n*p)*sizeof(float));
  C = (float *) malloc ((m*p)*sizeof(float));
//==================================
// Khoi tao MPI
  MPI_Init(&argc,&argv);
//==================================
// Tinh so process, gan ID cho tung process  
  MPI_Comm_size(MPI_COMM_WORLD,&NP);    
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
//==================================
// Tinh kich thuoc cua ma tran con
  mc = m/NP;
// Cap phat bo nho cho cac ma tran con
  Ac = (float *) malloc ((mc*n)*sizeof(float));
  Bc = (float *) malloc ((n*p)*sizeof(float));
  Cc = (float *) malloc ((mc*p)*sizeof(float));
//==================================
// Khoi Tao Du Lieu (Mat tran A, B) tai Core 0
  if (rank==0) {
  //Ma tran A
   for (  i = 0 ; i < m ; i++ )
    for ( j = 0 ; j < n ; j++ ){
      if (i==j) 
        *(A+i*n+j) = 1.0;
      else
        *(A+i*n+j) = 0.0;
    }
    printf("The matrix A:\n");
    DisplayMatrix(A, m, n);
  //Ma tran B
   for (  i = 0 ; i < n ; i++ )
    for ( j = 0 ; j < p ; j++ ){
      *(B+i*p+j) = 1.0*(i*p+j);
    }
    printf("The matrix B\n");
    DisplayMatrix(B, n, p);
  }
//==================================
// Gui Ma tran A tu Core 0 den tat ca cac Core
  if (rank==0){
    for (  i = 0 ; i < mc; i++ )
      for ( j = 0 ; j < n ; j++ ){
       *(Ac+i*n+j) = *(A+i*n+j);
    }
    for (i=1;i<NP;i++)
    MPI_Send(A+i*mc*n,mc*n,MPI_FLOAT,i,i,
             MPI_COMM_WORLD);
  } else
  {
    MPI_Recv(Ac,mc*n,MPI_FLOAT,0,rank,
             MPI_COMM_WORLD,&status);    
  }
  //
  //printf( "Ma tran Ac tai core %d is:\n", rank);
  //DisplayMatrix(Ac, mc, n);
//==================================
// Gui Ma tran B tu Core 0 den tat ca cac Core
  MPI_Bcast(B,n*p, MPI_INT,0,MPI_COMM_WORLD);
  //printf( "Ma tran Bc tai core %d is:\n", rank);
  //DisplayMatrix(Bc, n, p);
//==================================  
 // Nhan Ma Tran: A x B = C
  for ( i = 0 ; i < mc ; i++ )
    {
      for ( j = 0 ; j < p ; j++ )
      {
        for ( k = 0 ; k < n ; k++ )
        {
          sum = sum + (*(Ac + i*n + k)) * (*(B + k*p + j));
        }
 
        *(Cc + i*p + j) = sum;
        sum = 0.0;
      }
    }
  //printf( "Ma tran Cc tai core %d is:\n", rank);
  //DisplayMatrix(Cc, mc, p);
//==================================
// Gui Ma tran C tu tat ca cac Core ve Core 0
if(rank==0)
{
  for(i=0;i<mc;i++)
    for(j=0;j<p;j++)
      *(C+i*p+j)=*(Cc+i*p+j);

    for(i=1;i<NP;i++)
      MPI_Recv(C+i*mc*p,mc*p,MPI_FLOAT,i,i,MPI_COMM_WORLD,&status);
}
else
{ 
    MPI_Send(Cc,mc*p,MPI_FLOAT,0,rank,MPI_COMM_WORLD);
}
// In Ket Qua Tai Core 0
  if (rank==0)
    {
      printf( "Ma tran C:\n");
      DisplayMatrix(C, m, p);
    }
//==================================
  MPI_Finalize();
  return 0;
}



