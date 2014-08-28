#include <stdlib.h>
#include "answer01.h"

int arraySum(int * array, int len)
{
    int i;
    int sum = 0;
    
    for (i = 0; i < len; i++)
    {
      sum = sum + array[i];
    }
    return(sum);
}

int arrayCountNegative(int * array, int len)
{
    int i;
    int count = 0;
 
    for (i = 0; i < len; i++)
    {
      if (array[i] < 0)
      {
        count = count + 1;
      }
    }
    return(count);
}

int arrayIsIncreasing(int * array, int len)
{    
    return 0;
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    return 0;
}

int arrayFindSmallest(int * array, int len)
{
    return 0;
}
