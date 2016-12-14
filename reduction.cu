// MP 4 Reduction
// Given a list (lst) of length n
// Output its sum = lst[0] + lst[1] + ... + lst[n-1];
// Due Tuesday, January 15, 2013 at 11:59 p.m. PST

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#define BLOCK_SIZE 512 //@@ You can change this


__global__ void findmax(float * input, float * output, int len) {
	__shared__ float partialMax[BLOCK_SIZE];
	
	unsigned int t = threadIdx.x;
	unsigned int start = blockIdx.x * blockDim.x;
	
	partialMax[t] = (t < len) ? input[start + t] : 0;
	__syncthreads();
	//@@ Load a segment of the input vector into shared memory

	for(unsigned int stride = blockDim.x/2; stride >= 1; stride >>= 1) {
		if(t < stride)
			partialMax[t] = (partialMax[t] < partialMax[t + stride]) ? partialMax[t + stride]:partialMax[t];
		__syncthreads();
	}
	
	if(t == 0) {
		output[blockIdx.x + t] = partialMax[t];
	}
	//@@ Traverse the reduction tree
    //@@ Write the computed sum of the block to the output vector at the 
    //@@ correct index    //@@ Load a segment of the input vector into shared memory
    //@@ Traverse the reduction tree
    //@@ Write the computed sum of the block to the output vector at the 
    //@@ correct index
}

int main(int argc, char ** argv) {
 
    int ii;
    float * hostInput; // The input 1D list
    float * hostOutput; // The output list
    float * deviceInput;
    float * deviceOutput;
    int numInputElements = 40960; // number of elements in the input list
    int numOutputElements; // number of elements in the output list


    hostInput = (float*) malloc(numInputElements * sizeof(float));
    for(int i = 0; i < numInputElements; i++) {
        hostInput[i] = i;
    }

    numOutputElements = numInputElements / (BLOCK_SIZE);
    if (numInputElements % (BLOCK_SIZE)) {
        numOutputElements++;
    }
    hostOutput = (float*) malloc(numOutputElements * sizeof(float));

    //@@ Allocate GPU memory here
	cudaMalloc((void **) &deviceInput, numInputElements * sizeof(float));
	cudaMalloc((void **) &deviceOutput, numOutputElements * sizeof(float));
	
    //@@ Copy memory to the GPU here
	
	cudaMemcpy(deviceInput, hostInput, numInputElements * sizeof(float), cudaMemcpyHostToDevice);

    //@@ Initialize the grid and block dimensions here
	
	dim3 DimGrid((numInputElements - 1)/BLOCK_SIZE + 1, 1, 1);
	dim3 DimBlock(BLOCK_SIZE, 1, 1);

    //@@ Launch the GPU Kernel here
	findmax<<<DimGrid, DimBlock>>>(deviceInput, deviceOutput, numInputElements);
	
    cudaDeviceSynchronize();

    //@@ Copy the GPU memory back to the CPU here
	cudaMemcpy(hostOutput, deviceOutput, numOutputElements * sizeof(float), cudaMemcpyDeviceToHost);
	

    /********************************************************************
     * Reduce output vector on the host
     * NOTE: One could also perform the reduction of the output vector
     * recursively and support any size input. For simplicity, we do not
     * require that for this lab.
     ********************************************************************/
    for (ii = 1; ii < numOutputElements; ii++) {
        hostOutput[0] = (hostOutput[0]<hostOutput[ii]) ? hostOutput[ii]:hostOutput[0];
    }
    printf("%f\n", hostOutput[0]);

    //@@ Free the GPU memory here
	cudaFree(deviceInput);
	cudaFree(deviceOutput);

    free(hostInput);
    free(hostOutput);    
  
    return 0;
}
