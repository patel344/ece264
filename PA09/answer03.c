#include "answer03.h"
#include <string.h>
#include <stdio.h>

char * strcat_ex(char * * dest, int * n, const char * src)
{
	//Local Declarations
    char* buffer;

    //Executalbe Statements
	if ((*dest == NULL )|| (*n < (strlen(*dest) + strlen(src) + 1)))
	{  if(*dest != NULL)
       {
          *n = 1 + 2 * (strlen(*dest) + strlen(src)); 
       }
       else
       {
         *n = 1 + 2 * (strlen(src)); 
       }
	   buffer = malloc(*n * sizeof(char));
        *buffer = '\0'; 
        if(*dest != NULL)
        {
        buffer = strcpy(buffer,*dest);
        }
		free(*dest);
		*dest = buffer;
		*dest = strcat(*dest,src);
       // dest[strlen(*dest) - 1] = '\0';
	}
    else
    {
        *dest = strcat(*dest,src);
        //dest[strlen(*dest) - 1] = '\0';
    }
    
	return *dest;
}

char * * explode(const char * str, const char * delims, int * arrLen)
{
	//Local Declarations
	int N = 0;
	int i = 0;
	int k = 0;
	int arrInd = 0; // this is the next position where we'll create a string
	int last = 0; // 1 + the last index we saw a delimiter. Init to 0.
	char * * strArr;
	char * newArray;

	//Executables Statements
	// Count how many delimiters are in 'str'
	for (i = 0; i < (strlen(str)); i++) 
	{
  		if (strchr(delims, str[i]) != NULL)
  		{
  			N++;
  		}
	}
	// Create the return array
	strArr = malloc((N+1) * sizeof(char *));
    //strArr = NULL;
	//Filling the Arrays
    if(N != 0)
    {


	   for(i = 0; i < strlen(str); i++) 
        {
       
    	   if (strchr(delims,str[i]) != NULL)
    	   {
                newArray = malloc((1 + strlen(str)) * sizeof(char));
                *newArray = '\0';
    	    	for (k = last; k < i; k++)
    	    	{
                  newArray[k-last] = str[k];
    	       	}

    	    newArray[k-last] = '\0';
    	    strArr[arrInd] = newArray;
    	    last = i + 1;
    	    arrInd++;		
     	   } 
        }
    }
    
    
    newArray = malloc((1 + strlen(str)) * sizeof(char));
    *newArray = '\0';
    for(i = last; i < strlen(str); i++)
    {
    	newArray[i-last] = str[i];
    }
    newArray[i-last] = '\0';
    strArr[N] = newArray;
    *arrLen = N+1;
    return strArr;

}
char * implode(char * * strArr, int len, const char * glue)
{
    int i;
    int length = 0;
    char * newArray;
    for(i = 0; i < len; i++)
    {
        length = strlen(strArr[i]);
        length += length;
    }

    newArray = malloc((1 + 2 * length) * sizeof(char));
    *newArray = '\0';
    for(i = 0; i < len; i++)
    {
        newArray = strcat_ex(&newArray,&length,strArr[i]);
        if (i != (len-1))
        {
             newArray = strcat_ex(&newArray,&length,glue);  
        }
    }
    //newArray[length - 1]= '\0';
	return newArray;
}
 static int cmpstringp(const void *p1, const void *p2)
 {
    const char * left = * (char **) p1;
    const char * right = * (char **) p2;
    return strcmp(left,right);
 }

void sortStringArray(char * * arrString, int len)
{
    qsort(arrString,len,sizeof(char*), cmpstringp);
}
 static int cmpcharp(const void *p1, const void *p2)
 {
    char * char_left = (char *) p1;
    char * char_right = (char*) p2;
    return (*char_left - *char_right);
 }
void sortStringCharacters(char * str)
{
    qsort(str,strlen(str),sizeof(char),cmpcharp);
}
void destroyStringArray(char * * strArr, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
       free(strArr[i]); 
    }
    free(strArr);
    strArr = NULL;
} 