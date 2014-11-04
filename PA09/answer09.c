#include "answer09.h"

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

BusinessNode * create_node(char * stars, char * name, char * address)\
{
    BusinessNode * new_node = malloc(sizeof(BusinessNode));
    new_node->stars = stars;
    new_node->name = name;
    new_node->address = address;
    new_node->left = NULL;
    new_node->right = NULL;
    return(new_node);
}

void print_node(BusinessNode * node)
{
    printf("================\n");
    printf("%s\n",node->name);
    printf("Stars: %s\n", node->stars);
    printf("Address: %s\n", node->address);
    printf("================\n");
}

void print_tree(BusinessNode * tree)
{
    if(tree == NULL)
	{
	    return;
	}
    print_node(tree);
    print_tree(tree->left);
    print_tree(tree->right);
}
	
BusinessNode * tree_insert(BusinessNode * node, BusinessNode * root)
{
    if(root == NULL)
	{
	    return node;
	}
    if(strcmp(node->name,root->name) <= 0)
	{
	    root->left = tree_insert(node, root->left);
	}
    else
	{
	    root->right = tree_insert(node, root->right);
	}
    return root;
}

BusinessNode * load_tree_from_file(char * filename)
{
    FILE * fp = NULL;
    BusinessNode * node = NULL;
    char* entry = NULL;
    ssize_t read;
    size_t len = 0;
    int length_arr = 1;
    char* delim = "\t";
    int i;
    BusinessNode * root = NULL;
    char ** entry_Arr;

    fp = fopen(filename,"r");
    if(fp == NULL){
	fprintf(stderr,"Error! Failed to open file.\n");
	return NULL;
    }
   
    while((read = getline(&entry, &len, fp)) != -1){
	entry_Arr = explode(entry,delim, &length_arr);
	for(i = 0; i < 3; i++)
	    {
		printf("1: %s\n", entry_Arr[i]);
	    }
	node = create_node(entry_Arr[0], entry_Arr[1] , entry_Arr[2]);
	root = tree_insert(node,root);
	if(entry_Arr != NULL){
	    free(entry_Arr);
	}
    }    
    if(entry){
	free(entry);
    }
    return root;
}

BusinessNode * tree_search_name(char * name, BusinessNode * root)
{
    if(root == NULL){
	return NULL;
    }
    if(strcmp(name,root->name) == 0){
	return root;
    }
    if(strcmp(name,root->name) < 0){
	return(tree_search_name(name,root->left));
    }
    
    return(tree_search_name(name,root->right));
}

void destroy_tree(BusinessNode * root)
{
    if(root == NULL){
	return;
    }
    destroy_tree(root->left);
    destroy_tree(root->right);
    free(root->name);
    free(root->stars);
    free(root->address);
    free(root);
}
