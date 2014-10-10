#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer05.h"

#define ALL 1
#define INCREASING 2
#define DECREASING 3
#define ODD 4
#define EVEN 5
#define ODDANDEVEN 6
#define PRIME 7

int checkPrime(int number)
{
	int n;
	for (n = 2; n < number; n++)
	{
		if (number % n == 0)
		{
			return 0;
		}
	}
	return 1;
}
//FROM COURSE NOTES (PAGE 205)
void printPartition(int * arr, int length)
{
	int i;
	printf("= ");
	for(i = 0; i < length - 1; i++)
	{	
		printf("%d + ", arr[i]);
	}
	printf("%d\n", arr[length - 1]);
}
//MODIFIED FROM COURSE NOTES (PAGE 205)
void generalPartition(int * arr, int i, int value, int caseNum)
{
	int num;
	if (value == 0)
	{	
		printPartition(arr,i);
		return;
	}

	if (caseNum == ALL)
	{
		for (num = 1; num <= value; num++)
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, ALL);
		}
	}
	if (caseNum == INCREASING)
	{
		int min = 1;
		if (i != 0)
		{
			min = arr[i-1] + 1;
		}
		for (num = min; num <= value; num++) //for increasing numbers only
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, INCREASING);
		}
	}
	if (caseNum == DECREASING)
	{
		int min = value;;
		if (i != 0)
		{
			min = arr[i-1] - 1;
		}
		for (num = min; num >= 1; num--)
		{
			arr[i] = num;
			generalPartition(arr, i + 1, value - num, DECREASING);
		}
	}
	if (caseNum == ODD)
	{
		for (num = 1; num <= value; num += 2) //odd numbers only
		{
			arr[i] = num;
			generalPartition(arr,i + 1, value - num, ODD);
		}
	}
	if (caseNum == EVEN)
	{
		for (num = 2; num <= value; num += 2) //even numbers only
		{
			arr[i] = num;
			generalPartition(arr, i + 1, value - num, EVEN);
		} 
	}
	if (caseNum == ODDANDEVEN)
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
				generalPartition(arr, i + 1, value - num, ODDANDEVEN);
			}
		}
	}
	if (caseNum == PRIME)
	{
		for (num = 2; num <= value; num++)
		{
			if ((checkPrime(num)) == 1)
			{
				arr[i] = num;
				generalPartition(arr, i + 1, value - num, PRIME);
			}
		}
	}
}
//MODIFIED FROM COURSE NOTES (PAGE 206) ALL FUNCTIONS BELOW
void partitionAll(int value)
{
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,ALL);
		free(arr);
	}
}
void partitionIncreasing(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,INCREASING);
		free(arr);
	}
}
void partitionDecreasing(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,DECREASING);
		free(arr);
	}
}
void partitionOdd(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,ODD);
		free(arr);
	}
}	
void partitionEven(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,EVEN);
		free(arr);
	}
}
void partitionOddAndEven(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,ODDANDEVEN);
		free(arr);
	}
}
void partitionPrime(int value)
{ 
	int * arr;

	if (value <= 0)
	{
		fprintf(stderr,"Must enter a positive Value\n");
	}
	else
	{
		arr = malloc(value * sizeof(int));
		generalPartition(arr,0,value,PRIME);
		free(arr);
	}
}

