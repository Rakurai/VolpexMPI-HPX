#ifndef __dummympi_h__
#define __dummympi_h__


#define MPI_SUCCESS 0
#define MPI_Comm int
#define MPI_COMM_WORLD 87

#define MAXNAMELEN 64

#if defined(c_plusplus) || defined(__cplusplus)
extern "C" {
#endif

int MPI_Init (int *argc, char ***argv );
int MPI_Comm_size ( MPI_Comm comm, int *size );
int MPI_Comm_rank ( MPI_Comm comm, int *rank );
int MPI_Finalize (void);

int PMPI_Comm_size ( MPI_Comm comm, int *size );
int PMPI_Comm_rank ( MPI_Comm comm, int *rank );
int PMPI_Finalize (void);


#if defined(c_plusplus) || defined(__cplusplus)
}
#endif


#endif
