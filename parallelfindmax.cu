
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#define BLOCK_SIZE 512 //


__global__ void findmax(float * input, float * output, int len) {
	__shared__ float partialMax[BLOCK_SIZE];
	
	unsigned int t = threadIdx.x;
	unsigned int start = blockIdx.x * blockDim.x;
	
	partialMax[t] = (start + t < len) ? input[start + t] : 0;
	__syncthreads();


	for(unsigned int stride = blockDim.x/4; stride >= 1; stride >>= 1) {
		if(t < stride){
			partialMax[t] = (partialMax[t] < partialMax[t + stride]) ? partialMax[t + stride]:partialMax[t];
			partialMax[t] = (partialMax[t] < partialMax[t + 2*stride]) ? partialMax[t + 2*stride]:partialMax[t];
			partialMax[t] = (partialMax[t] < partialMax[t + 3*stride]) ? partialMax[t + 3*stride]:partialMax[t];
		}
		__syncthreads();
	}
	
	if(t == 0) {
		output[blockIdx.x + t] = partialMax[t];
	}

}

int main(int argc, char ** argv) {
 
    int ii;
    float * hostInput; // The input 1D array
    float * hostOutput; // The output array
    float * deviceInput;
    float * deviceOutput;
    int numInputElements = 4099; // number of elements in the input array
    int numOutputElements; // number of elements in the output array


    hostInput = (float*) malloc(numInputElements * sizeof(float));
    for(int i = 0; i < numInputElements; i++) {
        hostInput[i] = (i-2000)*(i-2000);
    }

    numOutputElements = numInputElements / (BLOCK_SIZE);
    if (numInputElements % (BLOCK_SIZE)) {
        numOutputElements++;
    }
    hostOutput = (float*) malloc(numOutputElements * sizeof(float));


	cudaMalloc((void **) &deviceInput, numInputElements * sizeof(float));
	cudaMalloc((void **) &deviceOutput, numOutputElements * sizeof(float));
	

	
	cudaMemcpy(deviceInput, hostInput, numInputElements * sizeof(float), cudaMemcpyHostToDevice);


	
	dim3 DimGrid((numInputElements - 1)/BLOCK_SIZE + 1, 1, 1);
	dim3 DimBlock(BLOCK_SIZE, 1, 1);


	findmax<<<DimGrid, DimBlock>>>(deviceInput, deviceOutput, numInputElements);
	
    cudaDeviceSynchronize();

	cudaMemcpy(hostOutput, deviceOutput, numOutputElements * sizeof(float), cudaMemcpyDeviceToHost);
	


    for (ii = 1; ii < numOutputElements; ii++) {
        hostOutput[0] = (hostOutput[0]<hostOutput[ii]) ? hostOutput[ii]:hostOutput[0];
    }
    printf("%f\n", hostOutput[0]);

	cudaFree(deviceInput);
	cudaFree(deviceOutput);

    free(hostInput);
    free(hostOutput);    
  
    return 0;
}
