#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"


int main(int argc, char ** argv)
{
        printf("Partition 4\n");
        partitionAll(4); 
	printf("\n");
       // printf("Partition 0\n");
       // partitionAll(0);
	//printf("\n");
        //printf("Partition 1\n");
        //partitionAll(1);
	//printf("\n");
        //printf("Partition 7\n");
        //partitionAll(7);
	//printf("\n");
        //printf("Partition-1\n");
        //partitionAll(-1);
	//printf("\n");
	printf("Partition Increasing\n");
	partitionIncreasing(4);
	printf("\n");
	printf("Partition Decreasing\n");
	partitionDecreasing(4);
	printf("\n");
	printf("Partition Odd\n");
	partitionOdd(4);
	printf("\n");
	printf("Partition even\n");
	partitionEven(4);
	printf("\n");
	printf("Partition OddnEven\n");
	partitionOddAndEven(4);
	printf("\n");
        return EXIT_SUCCESS;
}

