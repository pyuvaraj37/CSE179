#include <stdio.h>
#include <mpi.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {

	MPI_File fh;
	int buff[10], rank, numprocs;
	int offset;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Status status;

	for (int i = 0; i < 10; i++) {
		buff[i] = (rank * 10) + i;
		//printf("%d\n", buff[i]);
	}

	offset = rank * 10 * sizeof(int);

	MPI_File_open(MPI_COMM_WORLD, "io.bin", MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
	MPI_File_write_at(fh, offset, buff, 10, MPI_INT, &status);
	MPI_File_close(&fh);

	int rbuf[10];
	MPI_File_open(MPI_COMM_WORLD, "io.bin", MPI_MODE_RDWR, MPI_INFO_NULL, &fh);
	MPI_File_read_at(fh, offset, rbuf, 10, MPI_INT, &status);
	MPI_File_close(&fh);
	for (int i = 0; i < 10; i++) {
		printf("Rank %d: wrote: %d and read: %d\n",rank, buff[i], rbuf[i]);
	}


	MPI_File_open(MPI_COMM_WORLD, "io.bin", MPI_MODE_RDWR, MPI_INFO_NULL, &fh);

	for (int i = 0; i < 5; i++) {
		offset =  (2 * rank + (numprocs * i * 2)) * sizeof(int); 
		int *write = rbuf + 2 * i; 
		MPI_File_write_at(fh, offset, write, 2, MPI_INT, &status);
	}
	
	MPI_File_close(&fh);


	MPI_Finalize();

}
