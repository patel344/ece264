#include "answer03.h"
#include <string.h>

char * strcat_ex(char * * dest, int * n, const char * src)
{
	//Local Declarations
    char* buffer = NULL;

    //Executalbe Statements
	if ((*dest == NULL )|| (*n < (strlen(*dest) + strlen(src) + 1)))
	{  
		*n = 1 + 2 * (strlen(*dest) + strlen(src));
		buffer =  (char*) malloc(*n);
		//*buffer = '\0';
		//if(*dest != NULL){
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
	int arrInd = 0; // this is the next position where we'll create a string
	int last = 0; // 1 + the last index we saw a delimiter. Init to 0.

	//Executable Statements
	// Count how many delimiters are in 'str'
	for (i = 0; i < strlen(str); i++) 
	{
  		if (strchr(delims, str[i]) != NULL)
  		{
  			N++;
  		}
	}

	// Create the return array
	char * * strArr = malloc((N+1) * sizeof(char *));

	//Filling the Arrays
	for(i = 0; i < strlen(str); i++) 
    {
    	if (strchr(delims, str[i]) != NULL)
    	 {
    	 	*strArr = strArr[arrInd];
    	 	last = i + 1;
    	 	arrInd++;
     	 }
    }

    for(i = last; i < strlen(str); i++)
    {
    	*strArr = strArr[N];
    }
    
    *arrLen = strlen(*strArr);

    return strArr;

}
char * implode(char * * strArr, int len, const char * glue){return 0;}
void sortStringArray(char * * arrString, int len){}
void sortStringCharacters(char * str){}
void destroyStringArray(char * * strArr, int len){} 