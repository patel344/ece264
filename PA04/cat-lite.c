#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int main(int argc, char * * argv)
{
	int showHelp = FALSE;
	int i;
	FILE * fp;

	for(i = 1; i < argc; i++)
	{
		if(strcmp(argv[i], "--help") == 0)
		{
			showHelp = TRUE;
		}
	}
	
	if(showHelp)
	{
		printf("Usage: cat-lite [--help] [FILE]...\n"
                       "With no FILE, or when FILE is -, read standard input.\n\n"

                       "Examples:\n"
                       "cat-lite README   Print the file README to standard output.\n"
                       "cat-lite f - g    Print f's contents, then standard input,\n" 
                                         "then g's contents.\n"
                       "cat-lite          Copy standard input to standard output.\n");
	
		return EXIT_SUCCESS;
	}

	
	for(i = 1; i < argc; i++)
	{	
		if (*argv[i] == '-')
		{
			fp = stdin;
			char ch = fgetc(fp);
			while(!feof(fp))
			{
				fprintf(stdout,"%c",ch);
				ch = fgetc(fp);
			}
		}
		
		else
		{
			fp = fopen(argv[i],"r");
			if(fp == NULL)
			{
				fprintf(stderr, "cat cannot open %s\n", argv[i]);
				return EXIT_FAILURE;
			}
			
			char ch = fgetc(fp);
			while(!feof(fp))
			{
				fprintf(stdout, "%c", ch);
				ch = fgetc(fp);
			}
			fclose(fp);
		}
	}
	return 0;
}
