// Furkan Ekiz - 19050161003
// CENG342 - Homework3

#include <stdio.h>
#include <hellomake.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <mpi.h>

void multiply(double **matrix, int start, int finish, int matrixSize, double *vector, double *result) {
    for (int i = start; i < finish; i++) {
        //result[i] = 0.0;
        for (int j = 0; j < matrixSize; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

void matrixVectorMultiply(int matrixSize1, int rank, int numproc, char* filename){
   long id = 19050161003;
   double startTime1, finishTime1, startTime2, finishTime2;
   FILE *fp;

   double **matrix = (double **)malloc(matrixSize1 * sizeof(double *));
   for (int i = 0; i < matrixSize1; i++){
	matrix[i] = (double *)malloc(matrixSize1 * sizeof(double));
   }

   //set the seed for random number generator
   srand(id);

   //fill the matrix with random values
   for (int i = 0; i < matrixSize1; i++){
	for (int j = 0; j < matrixSize1; j++){
	    matrix[i][j] = ((double)rand() / RAND_MAX) * 100.0 + 1;
	}
   }
   
   double *vector = (double *)malloc(matrixSize1 * sizeof(double));
   for (int i = 0; i < matrixSize1; i++) {
        vector[i] = (double)rand() / RAND_MAX * 100.0 + 1.0;
   }
   
   double *result = (double *)malloc(matrixSize1 * sizeof(double));
   
   startTime1 = MPI_Wtime();
   
   int sop = matrixSize1 / numproc;
   int start = rank * sop;
   int finish;
   if(rank == numproc -1){
   	finish = matrixSize1;
   }else{
   	finish = start + sop;
   }
    
   multiply(matrix, start, finish, matrixSize1, vector, result);
   
   finishTime1 = MPI_Wtime();
   
   if(rank == 0){
   	startTime2 = MPI_Wtime();
   	
   	double *res = (double *)malloc(matrixSize1 * sizeof(double));
   	
   	for(int i = 0; i < sop; i++){
   		res[i] = result[i];
   	}
   	
   	for(int i = 1; i < numproc; i++){
   		MPI_Recv(res + i * sop, sop, MPI_DOUBLE, i, 999, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
   	}
   	
   	finishTime2 = MPI_Wtime();
   	
   //Write to file
    fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open output file.\n");
        return;
    }
    
    // print matrix to txt file
    fprintf(fp, "Matrix:\n");
    for (int i = 0; i < matrixSize1; i++) {
        for (int j = 0; j < matrixSize1; j++) {
            fprintf(fp, "%lf ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    // print vector to txt file
    fprintf(fp, "\nVector:\n");
    for (int i = 0; i < matrixSize1; i++) {
        fprintf(fp, "%lf ", vector[i]);
    }
    fprintf(fp, "\n");
    
    // print result to txt file
    fprintf(fp, "\nResult:\n");
    for (int i = 0; i < matrixSize1; i++) {
        fprintf(fp, "%lf ", res[i]);
    }
    fprintf(fp, "\n");
    
    fclose(fp);
    
    free(res);
    
    printf("Elapsed time is %lf seconds for parallel mxv with %d processes\n",(finishTime1 - startTime1) + (finishTime2 - startTime2), numproc);
   }
   else{
   	MPI_Send(result + start, sop, MPI_DOUBLE, 0, 999, MPI_COMM_WORLD);
   }
    
    free(matrix);
    free(vector);
    free(result);
    
    return;
}
