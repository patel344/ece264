#include "answer02.h"

size_t my_strlen(const char * str)
{
	//Local Declarations
	int len = 0;
	int i = 0;
    
    //Executable Statements
	while (str[i] != 0)
 	{
 		len = len + 1;
 		i++;
 	}
   return(len);
}

int my_countchar(const char * str, char ch)
{
	//Local Declarations
	int i = 0;
	int count = 0;
    
    //Executable Statements
	while (str[i] != 0)
	{
		if (str[i] == ch)
		{
			count = count + 1;
		}
		i++;
	}
	return(count);
}

char * my_strchr(const char * str, int ch)
{
	//Local Declarations
	int i;
	int len = my_strlen(str);
	
	//Executable Statements
	for (i = 0; i <= len; i++)
	{
        	if ( (char)ch == str[i])
    		{
    	       		return((char *) &str[i]); //Might exit function here
    										 //Returns pointer to character 'ch' in char array 'str'
   	        }
	}
	return NULL;
}

char * my_strrchr(const char * str, int ch)
{
	//Local Declarations
	int i;
	int len = my_strlen(str);
	
	//Executable Statements
	for (i = len; i >= 0; i--)
	{
		if ( (char)ch == str[i])
    	{
    		return (char *) &str[i]; //Might exit function here
    								 //Returns pointer to character 'ch' in char array 'str'
   	    }
	}
	return NULL;
}

char * my_strstr(const char * haystack, const char * needle)
{
	//Local Declarations
    int ch = (int) needle[0];

    //Executable Statements
    if (ch == 0)
    {
    	return (char *) haystack; //Might exit function here
    }
    return (my_strchr(haystack,ch));
}

char * my_strcpy(char * dest, const char * src)
{
	//Local Declarations
	int i;
	int len = my_strlen(src);
	
	//Executable Statements
	for (i = 0; i < len; i++)
	{
		 dest[i] = src[i];
	}
	dest[i] = '\0';
    
	return dest;
}

char * my_strcat(char * dest, const char * src)
{
	//Executalbe Statements
	my_strcpy(dest + my_strlen(dest), src);
	return dest;
	
}

int my_isspace(int ch)
{
	//Executable Statements
	if (ch == '\f' || ch == '\t' || ch == '\n' || ch == '\r' || ch == '\v' || ch == ' ')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int my_atoi(const char * str)
{
	//Local Declarations
	int ret = 0;
	int value = 0;
    
    //Executable Statements
    while (my_isspace(*str) == 1)
    {
    	str++;
    }
    if (*str == '-')
    {
    	str++;
    	value = 1;
    }

    while (*str >= '0' && *str <= '9')
	{
		ret *= 10;
        ret += *str - '0';
		str++;
	}
	if (value == 1)
    {
    	return -ret; //For negative values
    }
    else
    {
    	return ret;
    }
}
