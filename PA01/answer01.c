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
    int i = 0;
    int value = 1;

    while (i < len && value == 1)
    {
      if (array[i + 1] >= array[i])
      {
        value = 1;
      }
      else
      {
        value = 0;
      }
    i++;
    } 
    return(value);
}

int arrayIndexRFind(int needle, const int * haystack, int len)
{
    int i;
    int index = -1;
    
    for (i = 0; i < len; i++)
    {
      if (haystack[i] == needle)
      {
        index = i;
      }
    }
    return(index);
}

int arrayFindSmallest(int * array, int len)
{
    int i;
    int min;
    int index;

    if (len != 0)
    {
      for (i = (len - 1); i < 0; i--)
      {
        if (array[i] > array[i - 1])
        {
          min = array[i -1];
        }
      }
      index = array[min];
     }
     else 
     {
       index = 0;
     }
    return(index);
}
