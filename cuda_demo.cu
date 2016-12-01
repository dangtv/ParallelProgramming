
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>

#define N 10000
#define BlX 100

__global__ void Cong(int *a, int *b, int *c) {
	int i;
	i = blockIdx.x*blockDim.x + threadIdx.x;
	*(c + i) = *(a + i) + *(b + i);
}

int main()
{
	int *Ah, *Bh, *Ch, *Ad, *Bd, *Cd;
	int size = N * sizeof(int);
	Ah = (int*)malloc(size);
	Bh = (int*)malloc(size);
	Ch = (int*)malloc(size);

	cudaMalloc((void**)&Ad, size);
	cudaMalloc((void**)&Bd, size);
	cudaMalloc((void**)&Cd, size);

	for (int i = 0; i < N; i++)
	{
		*(Ah + i) = i;
		*(Bh + i) = 2 * i;
	}
	cudaMemcpy(Ad, Ah, size, cudaMemcpyHostToDevice);
	cudaMemcpy(Bd, Bh, size, cudaMemcpyHostToDevice);

	dim3 dimBlock(BlX, 1, 1);
	dim3 dimGrid(N / BlX, 1, 1);

	Cong<<<dimGrid, dimBlock>>>(Ad, Bd, Cd);
	cudaMemcpy(Ch, Cd, size, cudaMemcpyDeviceToHost);
	for (int i = 0; i < 20; i++)
	{
		printf("%d\n", *(Ch + i));
	}

	free(Ah); free(Bh); free(Ch);
	cudaFree(Ad); cudaFree(Bd); cudaFree(Cd);
	return 0;
}