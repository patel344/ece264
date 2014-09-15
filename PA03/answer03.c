#include "answer03.h"
#include <string.h>
#include <stdio.h>

char * strcat_ex(char * * dest, int * n, const char * src)
{
	//Local Declarations
    char* buffer = NULL;

    //Executalbe Statements
	if ((*dest == NULL )|| (*n < (strlen(*dest) + strlen(src) + 1)))
	{  
		*n = 1 + 2 * (strlen(*dest) + strlen(src));
		buffer = (char*) malloc(*n * sizeof(char));
		//*buffer = '\0';
		//if(*dest != NULL)
	    buffer = strcpy(buffer,*dest);
		free(*dest);
		*dest = buffer;
		*dest = strcat(*dest,src);
	}
        else
        {
               *dest = strcat(*dest,src);
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

	//Filling the Arrays
	for(i = 0; i < strlen(str); i++) 
    {
       
    	if (strchr(delims,str[i]) != NULL)
    	 {
            newArray = malloc(strlen(str) * sizeof(char));
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

    newArray = malloc(strlen(str) * sizeof(char));
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
    int length;
    char * newArray;
    for(i = 0; i < len; i++)
    {
        length = strlen(strArr[i]);
        length += length;
    }

    newArray = malloc((1 + 2 * length) * sizeof(char));
    for(i = 0; i < len; i++)
    {
        strcat_ex(&newArray,&length,strArr[i]);
        strcat_ex(&newArray,&length,glue);
    }
	return newArray;
}
 static int cmpstringp(const void *p1, const void *p2)
 {
    return strcmp(* (char * *) p1, * (char * *) p2);
 }

void sortStringArray(char * * arrString, int len)
{
    int i;

    qsort(*arrString,len,sizeof(char*), cmpstringp);

    for (i = 0; i < len; i++)
    {
        puts(arrString[i]);
    }
}
void sortStringCharacters(char * str){}
void destroyStringArray(char * * strArr, int len){} 