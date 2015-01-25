#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include "answer12.h"

int my_isspace(int ch)
{
    //Executable Statements
    if (ch == '\f' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == ' ')
	{
	    return 1;
	}
    else
	{
	    return 0;
	}
}

uint128 alphaTou128(const char * str)
{
    //Local Declarations
    uint128 ret = 0;
    
    //Executable Statements
    
    while (my_isspace(*str) == 1)
	{
	    str++;
	}
    if(*str == '-'){
	return ret;
    }
    while (*str >= '0' && *str <= '9')
	{
	    ret *= 10;
	    ret += *str - '0';
	    str++;
	}
    return ret;
}
char * u128ToString(uint128 value)
{
    int x = 0;
    int n = 0;
    char y;
    uint128 temp = value;
    int count = 0;
    
    if(temp == 0){
	count = 1;
    }
    while(temp != 0){
	temp = temp / 10;
	count ++;
    }
    char* buffer = malloc(sizeof(char) * (count + 1));
    for(x = count - 1; x >= 0; x--){
	n = value % 10;
	y = (char) n + '0';
	buffer[x] = y;
	value = value / 10;
    }
    buffer[count] = '\0';
    return (buffer);
}

typedef struct __threadArgs{
    uint128 start;
    uint128 stop;
    int* isPrime;
    uint128 n;
} threadArgs;

void* primeTest(void* arg){
    threadArgs* t_arg = (threadArgs*)arg;
     if(t_arg->start < 3){
	t_arg->start = 3;
    }
    if(t_arg->start % 2 == 0){
	t_arg->start++;
    }
    if(t_arg->stop % 2 == 0 && ((t_arg->stop) < (t_arg->n - 1))){
	t_arg->stop++;
    }

    uint128 i; 
    for(i = t_arg->start; i <= t_arg->stop; i=i+2){
	if(*(t_arg->isPrime) == 0){
	    return NULL;
	}
	if(t_arg->n % i == 0){
	    *(t_arg->isPrime) = 0;
	    return NULL;
	}
    }
    return NULL;
}
int primalityTestParallel(uint128 value, int n_threads)
{
    if(value == 2 || value == 3){
	return 1;
    }
    if(value == 1 || value % 2 == 0){
	return 0;
    }
    int i;
    uint128 max = floor(sqrt(value));
    uint128 chunk_size = (max + 1 + (uint128)n_threads) / (uint128)n_threads;
    int primecheck = 1;
    threadArgs* t_args = malloc(sizeof(threadArgs) * n_threads);
    for(i = 0; i < n_threads; i++){
	t_args[i].start = chunk_size * i;
	t_args[i].stop = chunk_size * (i + 1);
	t_args[i].isPrime = &primecheck;
	t_args[i].n = value;
    }
    
    pthread_t* thread = malloc(sizeof(pthread_t) * n_threads);
    
    for(i = 0; i < n_threads; i++){
	pthread_create(&thread[i], NULL, primeTest, &t_args[i]);
    }
    
    for(i = 0; i < n_threads; i++){
	pthread_join(thread[i],NULL);
    }
    free(thread);
    free(t_args);
    return primecheck;
}
