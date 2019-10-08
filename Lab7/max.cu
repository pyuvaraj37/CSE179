
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define MAX_THREADS_PER_BLOCK 1024

__global__ void findMaxInBlock(int *d_arr, int* gpu_return) {

	extern __shared__ int s_arr[];

	int tid = threadIdx.x;
	int index = blockIdx.x * MAX_THREADS_PER_BLOCK + threadIdx.x; 
	s_arr[tid] = d_arr[index];
	__syncthreads(); 

	for (int offset = 1; offset < blockDim.x; offset *=2) {

		if (tid % (2*offset) == 0) {
			if (s_arr[tid] < s_arr[tid + offset]) {
				s_arr[tid] = s_arr[tid + offset];
			}
		}
		__syncthreads();

	}

	if (tid == 0) {
		gpu_return[blockIdx.x] = s_arr[tid];
	}

}

void random_ints(int* a, int N) {

   int i;
   for (i = 0; i < N; ++i)
   		a[i] = rand() % (10000 + 1 - 0) + 0;

}

int main(void) {
	
	struct timeval cpu_start, cpu_end;
	struct timeval gpu_start, gpu_end;

	int *arr, *d_arr;
	int cpu_result, cpu_return; 
	int *gpu_result, *gpu_return;
	int N;
	scanf("%d", &N);

	int array_size = N * sizeof(int); 
	int integer_size = sizeof(int);

	int block_number = N / MAX_THREADS_PER_BLOCK;
	int thread_number = MAX_THREADS_PER_BLOCK;

	gpu_result = (int *)malloc(integer_size * block_number);

	arr = (int *)malloc(array_size); 
	random_ints(arr, N);

	cudaMalloc((void **) &d_arr, array_size);

	cudaMemcpy(d_arr, arr, array_size, cudaMemcpyHostToDevice);

	gettimeofday(&gpu_start, NULL);

	findMaxInBlock<<<block_number
			,thread_number>>>
			(d_arr, gpu_return);

	gettimeofday(&gpu_end, NULL);

	cudaMemcpy(gpu_result, gpu_return, integer_size * block_number, cudaMemcpyDeviceToHost);
	
	cpu_return = 0;
	gettimeofday(&cpu_start, NULL);
	for (int i = 0; i < N; i++) {
		int num = arr[i];
		if (cpu_return < num) {
			cpu_return = num;
		}
	}
	gettimeofday(&cpu_end, NULL);
	cpu_result = cpu_return; 
	

	printf("GPU result: %d GPU run time: %ld\n", gpu_result[1],(gpu_end.tv_usec - gpu_start.tv_usec));
	printf("CPU result: %d CPU run time: %ld\n",cpu_result, (cpu_end.tv_usec - cpu_start.tv_usec));

}
