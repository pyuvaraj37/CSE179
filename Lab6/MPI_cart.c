#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

	int numprocs, rank, namelen;
	int src, dest; 
	int ndims = 2;
	int dims[2] = {4,4};
	int periods[ndims];
	int reorder = 0; 
	int coords[2];
	int tag = 0; 
	int newRank;

	MPI_Status status[8];
	MPI_Comm cartcomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (numprocs == 16) {

		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &newRank);
		MPI_Cart_coords(cartcomm, newRank, 2, coords);

		printf("Coordinates: (%d,%d)\n", coords[0],coords[1]);
		printf("Local rank: %d, MPI_COMM_WORLD rank: %d\n", newRank, rank);
	}

	MPI_Finalize();
}