#include <stdio.h>
#include <hellomake.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

void multiply(double **matrix, int rows, int cols, double *vector, double *result) {
    for (int i = 0; i < rows; i++) {
        //result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}

/*void printMatrix(double **matrix, int rows, int cols) {
    fprintf(fp, "Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp, "%lf ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }
}

void printVector(double *vector, int size) {
    fprintf(fp, "Vector:\n");
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%lf ", vector[i]);
    }
    fprintf(fp, "\n");
}*/

void matrixVectorMultiply(int rows, int cols, char* filename){
   long id = 19050161003;

   double **matrix = (double **)malloc(rows * sizeof(double *));
   for (int i = 0; i < rows; i++){
	matrix[i] = (double *)malloc(cols * sizeof(double));
   }

   //set the seed for random number generator
   srand(id);

   //fill the matrix with random values
   for (int i = 0; i < rows; i++){
	for (int j = 0; j < cols; j++){
	    matrix[i][j] = ((double)rand() / RAND_MAX) * 100.0 + 1;
	}
   }
   
   double *vector = (double *)malloc(cols * sizeof(double));
   for (int i = 0; i < cols; i++) {
        vector[i] = (double)rand() / RAND_MAX * 100.0 + 1.0;
   }
   
   double *result = (double *)malloc(rows * sizeof(double));
    
   multiply(matrix, rows, cols, vector, result);
   
   FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open output file.\n");
        return;
    }
    
    // print matrix to txt file
    fprintf(fp, "Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(fp, "%lf ", matrix[i][j]);
        }
        fprintf(fp, "\n");
    }

    // print vector to txt file
    fprintf(fp, "\nVector:\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%lf ", vector[i]);
    }
    fprintf(fp, "\n");
    
    // print result to txt file
    fprintf(fp, "\nResult:\n");
    for (int i = 0; i < rows; i++) {
        fprintf(fp, "%lf ", result[i]);
    }
    fprintf(fp, "\n");
    
    fclose(fp);
    
    free(matrix);
    free(vector);
    free(result);
    
    return;
}
