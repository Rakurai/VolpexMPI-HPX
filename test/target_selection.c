#include "mpi.h"
#include <stdio.h>

#define MAX_LEN	(1024L * 64L)

int main(int argc, char *argv[])
{
    int myid, numprocs,i,j;
    MPI_Request request[2];
    MPI_Status status[2];
    int buf; 
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    printf("ID : %d, Rank : %d\n", SL_this_procid, myid);




double stime, etime;
stime = SL_Wtime();

for(i=0;i<1;i++){

	for(j=0; j<numprocs; j++){
	if(j != myid){
		MPI_Irecv(&buf, 1, MPI_INT, j, 1, MPI_COMM_WORLD, &request[0]);
		MPI_Isend(&buf,1 , MPI_INT,j,1 , MPI_COMM_WORLD, &request[1]);
		MPI_Waitall(2, request, status);

//		MPI_Wait(&request, &status);
//		MPI_Wait(&request2, &status);
	}
	}
}

etime = SL_Wtime();
printf("[%d]:Total time taken = %f \n", SL_this_procid,etime-stime);

MPI_Finalize();
	return 0;
}
