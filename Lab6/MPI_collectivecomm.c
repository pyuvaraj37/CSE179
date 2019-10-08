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

	int message = 10; 

	gettimeofday(&start, NULL);
	//Only Process 0 modifies the value, and sends it
	if(rank == 0) {
		message = message * message; 
		for(int i = 1; i < numprocs; i++) {
			printf("Process 0 sending %d to Process %d.\n",message, i);
			MPI_Send(&message, 
				1, 
				MPI_INT, 
				i, 
				tag, 
				MPI_COMM_WORLD);
		}

	} else {
		//Other processes will only receive from 0
		MPI_Recv(&message, 
			1, 
			MPI_INT, 
			0, 
			tag, 
			MPI_COMM_WORLD, 
			&status);
		printf("Process %d receive %d to Process 0.\n",rank, message);

	}
	gettimeofday(&end, NULL);

	printf("Process %d ran for %ld ms.\n", rank, (end.tv_usec - start.tv_usec));


	MPI_Finalize();
}