#include <stdio.h>
#include <mpi.h>
// command for build : mpicc -o <name for executable> <filename>
// command for execute : mpiexec -n <number of processors> <executable>

/*
*	function broadcast MPI
*	@since PP-8
*	@param buffer, message count, MPI datatype, id sender, MPI Commworld
*/
int bcast(void *buffer, int count, MPI_Datatype datatype, int root, MPI_Comm comm) {
	int i, id, size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	if(id == root) {
		for(i = 0; i < size; i++) {
			if(i != root) {
				MPI_Send(buffer, count, datatype, i, 0, comm);
			}
		}
	} else {
		MPI_Recv(buffer, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, NULL);
	}

	return 0;
}

int main(int argc, char **argv)
{
	int size, id, i, *x;

	MPI_Init(&argc, &argv);

	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);

	// printf("before P[%d] x = %d\n", id, x);
	// fflush(stdout);
	if(id == 0) {
		int data[5] = {1, 2, 3};
		x = data;
	}

	bcast(&x, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("after P[%d] x = %d\n", id, x);

	MPI_Finalize();
	return 0;

}