# openmp
gcc -fopenmp main.cpp
# build with open MPI 
mpicc nhan2matran_MPI_Bcast_demo.c
# run with openMPI 
mpirun -np 4 a.out 
