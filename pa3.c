#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grid.h"
#include <time.h>

int main(int argc, char ** argv){

    if (argc != 5) {
        return EXIT_FAILURE;
    }
    clock_t start, end;
    double execution_time;
    start = clock();
    
    readGrid(argv[1], argv[2], argv[3], argv[4]);
     
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;  
    printf("Time taken to execute in seconds : %f\n", execution_time);

    return EXIT_SUCCESS;
}
