#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

	int numprocs, rank, namelen;
	int src, dest; 
	int ndims = 2;
	int dims[2] = {4,4};
	int periods[2] = {1, 1};
	int reorder = 1; 
	int coords[2];
	int tag = 0; 
	int nbrs[4];
	int newRank;
	int outbuf;
	int inbuf[4] = {MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL, MPI_PROC_NULL};

	int i;

	MPI_Request request[8];
	MPI_Status status[8];
	MPI_Comm cartcomm;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);

	if (numprocs == 16) {

		MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &cartcomm);
		MPI_Comm_rank(cartcomm, &rank);
		MPI_Cart_coords(cartcomm, rank, 2, coords);
		MPI_Cart_rank(cartcomm, coords, &newRank);

		MPI_Cart_shift(cartcomm, 0, 1, &nbrs[0], &nbrs[1]);
    	MPI_Cart_shift(cartcomm, 1, 1, &nbrs[2], &nbrs[3]);

    	for (i=0; i<4; i++) {
        	dest = nbrs[i];
        	src = nbrs[i];
        	MPI_Isend(&rank, 1, MPI_INT, dest, tag, 
        		MPI_COMM_WORLD, &request[i]);
        	MPI_Irecv(&inbuf[i], 1, MPI_INT, src, tag, 
        		MPI_COMM_WORLD, &request[i+4]);
        }

      MPI_Waitall(8, request, status);
      printf("rank= %d:  %d %d %d %d\n", rank, inbuf[0], inbuf[1], inbuf[2], inbuf[3]);
	}

	MPI_Finalize();
}