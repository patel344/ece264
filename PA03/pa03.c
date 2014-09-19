#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "answer03.h"

int main(int argc, char * * argv)
{
  int n = 0;
  int i;
  int len;
  char * s1 = NULL;
  char * s2 = strdup("How did it get so late so soon?");
  char * * array;
  char * str;
 // char *strs[] = {"stre","riyi"};
  //char strng [] = "Alhpa";

  
 //strcat_ex
 printf("strcat_ex (\"%s\") = %s\n", s1, strcat_ex(&s1, &n, "Happy"));		
 free(s1);

 array = explode(" ", " ", &len);
 for (i = 0; i < len; i++)
 {
 	printf("array[%d] = %s\n", i, array [i]);
 }
 str = implode(array, len, ",");
 printf("(%s)\n", str); // (100, 224, 147, 80)
free(str);

 sortStringArray(array, len);
 for (i = 0; i < len; i++)
 {
 	printf("array[%d] = %s\n", i, array [i]);
 }
destroyStringArray(array,len);

 sortStringCharacters(s2);
 printf("charsort = %s\n",s2);
 free(s2);
 
return 0;
}
