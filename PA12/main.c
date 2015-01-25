#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "answer12.h"

int prime(uint128 n)
{
    if(n == 2){
	return 1;
    }
    if( n == 1){
	return 0;
    }
    if(n % 2 == 0){
	return 0;
    }
    uint128 max = floor(sqrt(n));
    uint128 i;
    for(i = 3; i <= max; i+=2){
	if(n % ((2 * i) + 1) == 0){
	    return 0;
	}
    }
    return 1;
}

void prime_test(uint128 * n)
{
    if(*n == 2){
	*n = 1;
	return;
    }
    if(*n == 1){
	*n = 0;
	return;
    }
    if(*n % 2 == 0){
	*n = 0;
	return;
    }
    uint128 max = floor(sqrt(*n));
    uint128 i;
    for(i = 3; i <= max; i+=2){
	//	if(*n % ((2 * i) + 1) == 0){
	//  *n = 0;
	//   return;
	//	}
	if(*n % i == 0){
	    *n = 0;
	    return;
	}
    }
    *n = 1;
    return;
}

int main(int argc, char** argv)
{
    uint128 value = alphaTou128(" 340282366920938463463374607431768211455th");
    char * string = u128ToString(123777);
    printf("%s\n", string);
    free(string);
    
    uint128 n = 0;
    prime_test(&n);
    printf("0 = %d\n", (int) n);

    n = 15;
    prime_test(&n);
    printf("15 = %d\n", (int) n);

    n = 9;
    prime_test(&n);
    printf("9 = %d\n", (int) n);

    n = 3;
    prime_test(&n);
    printf("3 = %d\n", (int) n);

    n = 4;
    prime_test(&n);
    printf("4 = %d\n", (int) n);

    n = 22;
    prime_test(&n);
    printf("22 = %d\n", (int) n);
    
    n = 1039;
    prime_test(&n);
    printf("1039 = %d\n", (int) n);


    
    int ret = prime(3);
    printf("3 = %d\n", ret);
    ret = prime(4);
    printf("4 = %d\n", ret);
    ret = prime(47);
    printf("47 = %d\n", ret);
    ret = prime(1);
    printf("1 = %d\n", ret);
    ret = prime(0);
    printf("0 = %d\n", ret);
    
    /* uint128 value2 = alphaTou128("38924078314341"); */
    /* ret = primalityTestParallel(value, 4); */
    /* printf("%d\n", ret); */
    /* uint128 val = alphaTou128("34050958923936410041"); */
    /* ret = primalityTestParallel(val, 4); */
    /* printf("%d\n", ret); */
    ret = primalityTestParallel(5,4);
    printf("%d\n", ret); 
    ret = primalityTestParallel(3,1);
    printf("%d\n", ret);
    return 0;
}

