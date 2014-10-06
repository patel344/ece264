#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

//FROM COURSE NOTES (PAGE 205)
void printPartition(int * arr, int length)
{
	int i;
	for(i = 0; i < length - 1; i++)
	{
		printf("%d + ", arr[i]);
	}
	printf("%d\n", arr[length - 1]);
}
//FROM COURSE NOTES (PAGE 205)
void generalPartition(int * arr, int i, int value, int caseNum)
{
	int num;
	if (value == 0)
	{	
		printPartition(arr,i);
		return;
	}

	if (caseNum == 1)
	{
		for (num = 1; num <= value; num++)
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, 1);
		}
	}
	if (caseNum == 2)
	{
		int min = 1;
		if (i != 0)
		{
			min = arr[i-1] + 1;
		}
		for (num = min; num <= value; num++) //for increasing numbers only
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, 2);
		}
	}
	if (caseNum == 3)
	{
		for (num = 1; num <= value; num++)
		{
			if (value < arr[i - 1])
			{
				arr[i] = num;
				generalPartition(arr, i + 1, value - num, 3);
			}
		}
	}
	if (caseNum == 4)
	{
		for (num = 1; num <= value; num += 2) //odd numbers only
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, 4);
		}
	}
	if (caseNum == 5)
	{
		for (num = 2; num <= value; num += 2) //even numbers only
		{
			arr[i] = num;
			generalPartition(arr, i + 1, value - num, 5);
		} 
	}
	if (caseNum == 6)
	{
		for (num = 1; num <= value; num ++)
		{
			int valid = 0;
			
			if (i == 0) //no restricition for first number
			{
				valid = 1;
			}
			else
			{
				valid = (arr[i - 1] % 2) != (num % 2);
			}

			if (valid == 1)
			{
				arr[i] = num;
				generalPartition(arr, i + 1, value - num, 6);
			}
		}
	}
	if (caseNum == 7)
	{}
}
//MODIFIED FROM COURSE NOTES (PAGE 206) ALL FUNCTIONS BELOW
void partitionAll(int value)
{
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,1);
	free(arr);
}
void partitionIncreasing(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,2);
	free(arr);
}
void partitionDecreasing(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,3);
	free(arr);
}
void partitionOdd(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,4);
	free(arr);
}
void partitionEven(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,5);
	free(arr);
}
void partitionOddAndEven(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,6);
	free(arr);
}
void partitionPrime(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	arr = malloc(value * sizeof(int));
	generalPartition(arr,0,value,7);
	free(arr);
}

