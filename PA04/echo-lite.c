#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
	//Local Declarations
	int showHelp = FALSE;
	int i;
	
	//Executable Statements
	if (argc > 1)
	{
		for(i = 1; i < argc; i++)
		{
			if(strcmp(argv[i],"--help") == 0)
			{
				showHelp = TRUE;
			}
		}
	
		if(showHelp)
		{
			printf("--help\n");
			return EXIT_SUCCESS;
		}
	 
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
	else
	{
		printf("\n");
	}
	return EXIT_SUCCESS;
}

