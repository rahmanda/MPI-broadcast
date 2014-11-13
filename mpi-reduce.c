#include <mpi.h>
#include <stdio.h>
#define ROOT 2
int main()
{
	int id, x, sum;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	x = id * 2;
	printf("P[%d] x: %d\n", id, x);
	MPI_Reduce(&x, &sum, 1, MPI_INT, MPI_SUM, ROOT, MPI_COMM_WORLD);
	if (id == ROOT)
		printf("P[%d] sum: %d\n", id, sum);
	MPI_Finalize();
	
	return 0;
}