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
	if(argc == 1)
	{
		fprintf(stderr,"ERROR\n");
		return 2;
	}
		
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
		if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--invert-match") == 0)
		{
			invertMatch = TRUE;
		}
		else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i],"--line-number") == 0)
		{
			lineNumber = TRUE;
		}
		else if(strcmp(argv[i], "-q") == 0|| strcmp(argv[i],"--quiet") == 0)
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
	FILE *fp = stdin;
	if(fp == NULL)
	{
		printf("ERROR\n");
		return 2;
	}
		
	char s[2000];
	int counter = 0;
	int match;
	int numMatch = 0;
	while(fgets(s,2000,fp))
	{
		match = strstr(s,pattern) != NULL;
		counter++;
		if((match && !invertMatch) || (!match && invertMatch))
		{
			numMatch++;
			if(!quiet)
			{
				if(lineNumber)
				{
					printf("%d:", counter);	
				}
				printf("%s",s);
			}	
		}
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
	if(numMatch > 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
