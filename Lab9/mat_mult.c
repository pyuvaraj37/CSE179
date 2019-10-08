#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	int numprocs, rank, namelen;
	int n, block; 
	int dest, row, offset; 
	struct timeval start, end;
	
	int tag = 0;
	int indexr, indexc;

	printf("Enter n: \n");
	scanf("%d", &n);

	printf("Enter b: \n");
	scanf("%d", &block);

	int k = (n * n / block)^(1/2); 

	int a[n][n];
	int b[n][n];
	int c[n][n];

	MPI_Init(&argc, &argv);	
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;


	if (rank == 0) {

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = rand();
				b[i][j] = rand(); 
			}
		}

		//Each process gets their part of the matrix 
		for (dest = 1; dest < numprocs; dest++) {

			indexc = dest % k; 
			indexr = dest / k; 
			tag = dest; 
			
			for (int i = indexr * block; i < indexr * block + block; i++) {
				MPI_Send((int*)a[i][indexc * block], 
				block, 
				MPI_INT, 
				dest, 
				tag, 
				MPI_COMM_WORLD);
				tag++;
				MPI_Send((int*)b[indexc * block][i], 
				block, 
				MPI_INT, 
				dest, 
				tag, 
				MPI_COMM_WORLD);


			}

		}
		for (dest = 1; dest < numprocs; dest++) {
			for (int i = indexr * block; i < indexr * block + block; i++) {

				MPI_Recv((int*)c[i][indexc * block], 
					block, 
					MPI_INT, 
					dest, 
					tag, 
					MPI_COMM_WORLD, 
					&status);
			}
		}

		gettimeofday(&start, NULL);
		for (int i = indexr * block; i < indexr * block + block; i++) {
			for (int j = indexc * block; indexc * block + block; j++) {
				c[i][j] += a[i][j] * b[j][i];
			}
		}

		gettimeofday(&end, NULL);

	}

	if (rank > 0) {

		indexc = rank % k; 
		indexr = rank / k; 
		tag = rank; 
			
		for (int i = indexr * block; i < indexr * block + block; i++) {

			MPI_Recv((int*)a[i][indexc * block], 
				block, 
				MPI_INT, 
				0, 
				tag, 
				MPI_COMM_WORLD, 
				&status);
			tag++;
			MPI_Recv((int*)b[indexc * block][i], 
				block, 
				MPI_INT, 
				0, 
				tag, 
				MPI_COMM_WORLD, 
				&status);
			tag++;
		}

		for (int i = indexr * block; i < indexr * block + block; i++) {
			for (int j = indexc * block; indexc * block + block; j++) {
				c[i][j] += a[i][j] * b[j][i];
			}
		}

		indexc = rank % k; 
		indexr = rank / k; 
		tag = rank; 

		for (int i = indexr * block; i < indexr * block + block; i++) {

				MPI_Send((int*)c[i][indexc * block], 
				block, 
				MPI_INT, 
				0, 
				tag, 
				MPI_COMM_WORLD);
				tag++;
		}
	}
	

	MPI_Finalize();
	printf("Ran for %ld ms\n", (end.tv_usec - start.tv_usec));

}