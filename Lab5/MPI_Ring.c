#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]) {

	int numprocs, rank, namelen;
	//Rank # that will be sent to Rank + 1
	int message;
	//Tag is zero for all for easy send/receive
	int tag = 0;
	//Status of Receive
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);


	//Thread 0 has a different receive since it receives from Thread (numproc - 1) (Last)
	if (rank != 0) {
		MPI_Recv(&message, 
			1, 
			MPI_INT, 
			rank - 1, 
			tag, 
			MPI_COMM_WORLD, 
			&status);
		printf("Process: %d received message: %d from Process: %d.\n", rank, message, rank - 1);
	} 
	//All Threads send messsage = their rank. EX Thread 1, message = 1. 
	message = rank;  
	MPI_Send(&message, 
		1, 
		MPI_INT, 
		(rank + 1)%numprocs, 
		tag, 
		MPI_COMM_WORLD);

	//Thread 0 must receive last, since all the other threads are waiting to receive first
	if (rank == 0) {
		MPI_Recv(&message, 
			1, 
			MPI_INT, 
			numprocs - 1, 
			tag, 
			MPI_COMM_WORLD, 
			&status);
		printf("Process: %d received message: %d from Process: %d.\n", rank, message, numprocs - 1);
	}
	

	MPI_Finalize();
	return 0; 

}