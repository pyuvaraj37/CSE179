#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

	int numprocs, rank, namelen;

	struct timeval start, end;

	int tag = 0; 
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;

	int message[numprocs];
	int holder; 

	gettimeofday(&start, NULL);
	
	if(rank == 0) {

		for (int i = 0; i < numprocs; i++) {
			message[i] = i;
		}
		printf("Process 0 has an array [");
		for (int i = 0; i < numprocs; i++) {
			printf(" %d", message[i]);
		}
		printf("].\n");

	} 

	MPI_Scatter(message,
			1,
			MPI_INT,
			&holder,
			1,
			MPI_INT,
			0,
			MPI_COMM_WORLD);

		
	printf("Process %d received %d\n",rank, holder);
	holder += rank; 
	printf("and sends %d\n", holder);

	MPI_Gather(&holder,
			1, 
			MPI_INT,
			message,
			1,
			MPI_INT,
			0,
			MPI_COMM_WORLD);

	if(rank == 0) {
		printf("Process 0 now has an array [");
		for (int i = 0; i < numprocs; i++) {
			printf(" %d", message[i]);
		}
		printf("].\n");
	}

	gettimeofday(&end, NULL);

	printf("Process %d ran for %ld ms.\n", rank, (end.tv_usec - start.tv_usec));


	MPI_Finalize();
}