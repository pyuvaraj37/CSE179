
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>


__global__ void sim_cell_onelife(int* d_cell, int m, int n) {

	 __shared__ int s_arr[100];
	 int neighbor = 0;  
	 
	 int r = threadIdx.x % m;
	 int c = threadIdx.x / m;
	 int cell = d_cell[r + c * m];
	 int row = r - 1; 
	 int col = c - 1; 


	 s_arr[r + c * m] = d_cell[r + c * m];
	 __syncthreads(); 

	 for (int i = row; i < row + 3; i++) {

	 	for (int j = col; j < col + 3; j++) {

	 		if (i >= 0 && j >= 0) {

	 			if (i < m && j < n) {

	 				if (i != r || j != c) {

	 					if (s_arr[i + j * m] == 1) {

	 						neighbor += 1; 

	 					}
	 				}
	 			}
	 		}
	 	}
	 }

	 if (cell == 1 && neighbor <= 1) {
	 	cell = 0; 
	 } else if (cell == 0 && neighbor == 2) {
	 	cell = 1;
	 } else if (cell == 0 && neighbor == 3){ 
	 	cell = 1; 
	 } else if (cell == 1 && neighbor >= 4) {
	 	cell = 0; 
	 }

	__syncthreads(); 

	d_cell[r + c * m] = cell;

}


int main(void) {
	
	int *cell; 
	int *d_cell; 
	int t_num; 
	int size; 
	int m, n, k; 

	struct timeval gpu_start, gpu_end;

	// m x n
	printf("Enter M: \n");
	scanf("%d", &m);

	printf("Enter N: \n");
	scanf("%d", &n);

	printf("Enter K: \n");
	scanf("%d", &k);

	t_num = n * m; 
	size = t_num * sizeof(int);

	cell = (int *)malloc(size);

	printf("-------BEFORE LIFE CYCLE--------\n");

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cell[i + j * m] = rand() % (1 - 0 + 1) + 0; 
		}
	}

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", cell[i + j * m]);
		}
		printf("\n");
	}		

	printf("-------AFTER %d LIFE CYCLES-------\n", k);
	cudaMalloc((void **)&d_cell, size);
	
	cudaMemcpy(d_cell, cell, size, cudaMemcpyHostToDevice);

	gettimeofday(&gpu_start, NULL);
	for (int i = 0; i < k; i++) {
		sim_cell_onelife<<<1,t_num>>>(d_cell, m, n);
	}
	gettimeofday(&gpu_end, NULL);

	memset(cell, 0, size);

	cudaMemcpy(cell, d_cell, size, cudaMemcpyDeviceToHost);

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			printf("%d ", cell[i + j * m]);
		}
		printf("\n");
	}	

	free(cell);
	cudaFree(d_cell);
	printf("GPU run time: %ld\n",(gpu_end.tv_usec - gpu_start.tv_usec));

}