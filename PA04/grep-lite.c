#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
	int showHelp = FALSE;
	int invertMatch = FALSE;
	int lineNumber = FALSE;
	int quiet = FALSE;
	int badSwitch = FALSE;
		
	int i;
		
	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "--help") == 0)
		{
			showHelp = TRUE;
		}
	}

	if(showHelp)
	{
		printf("Usage: grep-lite [OPTION]... PATTERN\n"
		       "Search for PATTERN in standard input. PATTERN is a\n"
		       "string. grep-lite will search standard input line by\n"
		       "line, and (by default) print out those lines which\n"
		       "contain pattern as a substring.\n\n"

			 "-v, --invert-match     print non-matching lines\n"
			 "-n, --line-number      print line numbers with output\n"
			 "-q, --quiet            suppress all output\n\n"

	               "Exit status is 0 if any line is selected, 1 otherwise;\n"
		       "if any error occurs, then the exit status is 2.\n");	
		return EXIT_SUCCESS;
        }

	for(i = 1; i < argc - 1; i++)
	{
		if(strcmp(argv[i], "-v") == 0)
		{
			invertMatch = TRUE;
		}
		else if(strcmp(argv[i], "-n") == 0)
		{
			lineNumber = TRUE;
		}
		else if(strcmp(argv[i], "-q") == 0)
		{
			quiet = TRUE;
		}	
		else
		{
			badSwitch = TRUE;
			fprintf(stderr,"Unknown Switch: '%s'\n", argv[i]);
		}
	}
	
	if(badSwitch)
	{
		fprintf(stderr,"Aborting...\n");
		return EXIT_FAILURE;
	}
        
	if(argc > 1 && *(argv[i]) == '-')
	{
		fprintf(stderr,"Last line must not contain - as first character\n");
		return 2;
	}
	
	
	char* pattern = argv[i];
	char * s;
	for(i = 1; i < argc; i++)
	{
		FILE *fp = fopen(argv[i],"r");
		if(fp == NULL)
		{
			printf("ERROR\n");
			return 1;
		}
		
		s = malloc(2000 * sizeof(char));
		while(!feof(fp))
		{
			int counter = 0;
			int match = strstr(s,pattern) != NULL;
			counter++;
			if((match && !invertMatch) || (!match && invertMatch))
			{
				if(lineNumber)
				{
					printf("%d:", counter);	
				}
				printf("%s\n",s);
			}
		}
		free(s);
		fclose(fp);
	}
	
	/*
 *    while loop, reading each line, "line" {
 *       int match = strstr(s, pattern) != NULL;
 *       if((match && !invert) || (!match && invert)) {
 *	     if(printLine) 
 *	          printf("%d:", lineno);
 *	     printf("%s\n", line);
 *       }
 *    }
 */

	return 0;
}
