#include <mpi.h>
#include <stdio.h>
#define ROOT 0
int main()
{
	int id, ldata;
	int *data;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	if (id == ROOT) {
		int number[4] = {5,6,7,8};
		data = number;
	}
	MPI_Scatter(data, 1, MPI_INT, &ldata, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
	printf("P[%d] local data: %d\n", id, ldata);
	
	fflush(stdout);
	ldata = id * id;
	MPI_Gather(&ldata, 1, MPI_INT, data, 1, MPI_INT, ROOT, MPI_COMM_WORLD);
	if(id == ROOT) {
		printf("P[0] data: %d %d %d %d\n", data[0], data[1], data[2], data[3]);
	}
	MPI_Finalize();
	return 0;
}