// Furkan Ekiz - 19050161003
// CENG342 - Homework3

#include <mpi.h>
#include <hellomake.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

   int rank, numproc;

   int matrixSize1 = atoi(argv[1]);
   int matrixSize2 = atoi(argv[2]);
   char *filename = argv[3];
   
   MPI_Init(NULL, NULL);
   
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &numproc);
   
   //matrixVectorMultiply(matrixSize1, rank, numproc, filename);
   matrixVectorMultiply(matrixSize2, rank, numproc, filename);

   MPI_Finalize();
   return(0);
}
