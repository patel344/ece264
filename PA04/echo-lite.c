#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * * argv)
{
	//Local Declarations
	int i;
	
	//Executable Statements
	for(i = 1; i < argc - 1; i++)       //Parses user entry from the second string to the second to last string
	{
		printf("%s%c",argv[i],32);  //Prints each string ensuring only a space in between
		
		if(*argv[i] == '"') 
		{
			printf("%c",32);    //Places a space if a quote is denoted
		}
	}

	printf("%s\n", argv[i]);            //Prints out the last string 

	
	return EXIT_SUCCESS;
}

