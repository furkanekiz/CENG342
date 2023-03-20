#include <hellomake.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

   int rows = atoi(argv[1]);
   int cols = atoi(argv[2]);
   char *filename = argv[3];

   matrixVectorMultiply(rows, cols, filename);

   return(0);
}
