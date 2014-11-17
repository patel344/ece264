#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "answer10.h"

typedef struct Review_t{
    long file_offset;
    int Business_ID;
} Review;

typedef struct Bus_Location_t{
    int Business_ID;
    char* address, *state, *city, *zip;
    struct Bus_Location_t * next;
} Bus_Location;

typedef struct Bus_Tree_t{
    char* name;
    Bus_Location * locations;
    struct Bus_Tree_t *left;
    struct Bus_Tree_t *right;
} Bus_Tree;

struct YelpDataBST{
    Bus_Tree* locations;
    Review* reviews;
    const char* reviews_path; //file of reviews
    const char* business_path;
};
int List_length(Bus_Location* list)
{
    int len = 0;
    while(list != NULL){
	len++;
	list = list->next;
    }
    return len;
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


void destroyStringArray(char** strArr, int len)
{
    int i;
    for(i=0; i<len; i++){
	free(strArr[i]);
    }
    free(strArr);
    strArr = NULL;
}
Bus_Location* Bus_Loc_create(int Business_ID, char* address, char* state, char* city, char* zip)
{
    Bus_Location* new_loc = malloc(sizeof(Bus_Location));
    new_loc->Business_ID = Business_ID;
    new_loc->address = strdup(address);
    new_loc->state = strdup(state);
    new_loc->city = strdup(city);
    new_loc->zip = strdup(zip);
    new_loc->next = NULL;
    return (new_loc);
}
struct YelpDataBST* data_create(const char* business_path, const char* reviews_path)
{
    struct YelpDataBST* data = malloc(sizeof(struct YelpDataBST));
    data->reviews = NULL;
    data->locations = NULL;
    data->business_path = business_path;
    data->reviews_path = reviews_path;
    return data;
}
Bus_Location* Bus_Loc_push(Bus_Location* head, int Business_ID, char* address, char* state, char* city, char* zip)
{
    Bus_Location* newhead = Bus_Loc_create(Business_ID, address, state, city, zip);
    newhead->next = head;
    return newhead;
}
void Bus_Loc_destroy(Bus_Location* head)
{
    Bus_Location* itr = head;
    while(itr != NULL){
	Bus_Location* next = itr->next;
	free(itr->address);
	free(itr->state);
	free(itr->city);
	free(itr->zip);
	free(itr);
	itr = next;
    }
}
void Bus_Loc_print(Bus_Location* head)
{
    Bus_Location* itr = head;
    while(itr != NULL){
	if(itr != head){
	printf("==>");
	}
	printf("[%p #%d '%s' '%s' %p]", itr, itr->Business_ID, itr->state, itr->zip, itr->next);
	itr = itr->next;
    }
}
void Bus_Loc_test()
{
    Bus_Location* head = Bus_Loc_create(44,"address", "city", "NV", "83324");
    head = Bus_Loc_push(head, 30, "a2", "c2", "MI", "33322");
    Bus_Loc_print(head);
    // Bus_Loc_destroy(head);
}

Bus_Tree* tree_create(const char* name)
{
    Bus_Tree* node = malloc(sizeof(Bus_Tree));
    node->name = strdup(name);
    node->locations = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Bus_Tree* tree_insert(Bus_Tree* root, char* name, int Business_ID, char* address, char* state, char* city, char* zip)
{
    if(root == NULL){
	root = tree_create(name);
	root->locations = Bus_Loc_push(root->locations,Business_ID, address, state, city, zip);
    }
    else if(strcmp(name,root->name) < 0){
	root->left = tree_insert(root->left, name, Business_ID, address, state, city, zip);
    }
    else if(strcmp(name,root->name) > 0){
	root->right = tree_insert(root->right, name, Business_ID, address, state, city, zip);
    }
    else{
	root->locations = Bus_Loc_push(root->locations,Business_ID, address, state, city, zip);
    }
    return root;
}
void tree_destroy(Bus_Tree* root)
{
    if(root == NULL){
	return;
    }
    tree_destroy(root->left);
    tree_destroy(root->right);
    free(root->name);
    Bus_Loc_destroy(root->locations);
    free(root);
}
void tree_print(Bus_Tree* root, int indent)
{
    if(root == NULL){
	return;
    }
    int i;
    for(i=0;i<indent;++i){
	printf("  ");
    }
    printf("%p '%s' (%p %p)", root, root->name, root->left, root->right);
    Bus_Loc_print(root->locations);
    printf("\n\n");
    tree_print(root->left, indent - 1);
    tree_print(root->right, indent + 1);
}


/* int compar_loc(Location_offset * node, Location_offset * head, const char* businesses_path) */
/* { */
/*     FILE* fp_node = NULL; */
/*     FILE* fp_head = NULL; */
/*     char* entry_node = NULL; */
/*     char* entry_head = NULL; */
/*     ssize_t read_node; */
/*     ssize_t read_head; */
/*     size_t len_node = 0; */
/*     size_t len_head = 0; */
/*     int length_arr = 1; */
/*     char* delim = "\t"; */
/*     char** entry_Arr_node; */
/*     char** entry_Arr_head; */

/*     //FIND COMPONENTS FOR NODE */
/*     fp_node = fopen(businesses_path,"r"); */
/*     fseek(fp_node, node->file_offset, SEEK_SET); */
/*     read_node = getline(&entry_node, &len_node, fp_node); */
/*     entry_Arr_node = explode(entry_node, delim, &length_arr); */
/*     char* state_node = entry_Arr_node[4]; */
/*     char* city_node = entry_Arr_node[3]; */
/*     char* zip_code_node = entry_Arr_node[5]; */
/*     char* address_node = entry_Arr_node[6]; */
/*     /\* free(entry_Arr_node[0]); *\/ */
/*     /\* free(entry_Arr_node[1]); *\/ */
/*     /\* free(entry_Arr_node[2]); *\/ */
/*     fclose(fp_node); */
    
/*     //FIND COMPONENTS FOR HEAD */
/*     fp_head = fopen(businesses_path, "r"); */
/*     fseek(fp_head, head->file_offset, SEEK_SET); */
/*     read_head = getline(&entry_head, &len_head, fp_head); */
/*     entry_Arr_head = explode(entry_head, delim, &length_arr); */
/*     char* state_head = entry_Arr_head[4]; */
/*     char* city_head = entry_Arr_head[3]; */
/*     char* zip_code_head = entry_Arr_head[5]; */
/*     char* address_head = entry_Arr_head[6]; */
/*     /\* free(entry_Arr_head[0]); *\/ */
/*     /\* free(entry_Arr_head[1]); *\/ */
/*     /\* free(entry_Arr_head[2]); *\/ */
/*     fclose(fp_head); */
    
/*     if(strcmp(state_node,state_head) > 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(state_node,state_head) < 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(city_node,city_head) > 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(city_node,city_head) < 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(zip_code_node,zip_code_head) > 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(zip_code_node,zip_code_head) < 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(address_node,address_head) > 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(address_node,address_head) < 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     /\* free(entry_Arr_head[3]); *\/ */
/*     /\* free(entry_Arr_head[4]); *\/ */
/*     /\* free(entry_Arr_head[5]); *\/ */
/*     /\* free(entry_Arr_head[6]); *\/ */
/*     /\* free(entry_Arr_head); *\/ */
/*     /\* free(entry_Arr_node[3]); *\/ */
/*     /\* free(entry_Arr_node[4]); *\/ */
/*     /\* free(entry_Arr_node[5]); *\/ */
/*     /\* free(entry_Arr_node[6]); *\/ */
/*     /\* free(entry_Arr_node); *\/ */
/*     /\* free(entry_head); *\/ */
/*     /\* free(entry_node); *\/ */
/*     return 0; */
/* } */

/* int compar_rev(Review_offset * node, Review_offset * head, const char* reviews_path) */
/* { */
/*     FILE* fp_node = NULL; */
/*     FILE* fp_head = NULL; */
/*     char* entry_node = NULL; */
/*     char* entry_head = NULL; */
/*     ssize_t read_node; */
/*     ssize_t read_head; */
/*     size_t len_node = 0; */
/*     size_t len_head = 0; */
/*     int length_arr = 1; */
/*     char* delim = "\t"; */
/*     char** entry_Arr_node; */
/*     char** entry_Arr_head; */

/*     //FIND COMPONENTS FOR NODE */
/*     fp_node = fopen(reviews_path,"r"); */
/*     fseek(fp_node, node->file_offset, SEEK_SET); */
/*     read_node = getline(&entry_node, &len_node, fp_node); */
/*     entry_Arr_node = explode(entry_node, delim, &length_arr); */
/*     char* stars_node = entry_Arr_node[1]; */
/*     char* review1_node = entry_Arr_node[2]; */
/*     char* review2_node = entry_Arr_node[3]; */
/*     char* review3_node = entry_Arr_node[4]; */
/*     char* text_node = entry_Arr_node[5]; */
/*     free(entry_Arr_node[0]); */
/*     fclose(fp_node); */
    
/*     //FIND COMPONENTS FOR HEAD */
/*     fp_head = fopen(reviews_path, "r"); */
/*     fseek(fp_head, head->file_offset, SEEK_SET); */
/*     read_head = getline(&entry_head, &len_head, fp_head); */
/*     entry_Arr_head = explode(entry_head, delim, &length_arr); */
/*     char* stars_head = entry_Arr_head[1]; */
/*     char* review1_head = entry_Arr_head[2]; */
/*     char* review2_head = entry_Arr_head[3]; */
/*     char* review3_head = entry_Arr_head[4]; */
/*     char* text_head = entry_Arr_head[5]; */
/*     free(entry_Arr_head[0]); */
/*     fclose(fp_head); */
    
/*       if(strcmp(stars_node,stars_head) > 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(stars_node,stars_head) < 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(review1_node,review1_head) > 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(review1_node,review1_head) < 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(review2_node,review2_head) > 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(review2_node,review2_head) < 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(review3_node,review3_head) > 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     if(strcmp(review3_node,review3_head) < 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(text_node,text_head) > 0) */
/* 	{ */
/* 	    return 1; */
/* 	} */
/*     if(strcmp(text_node,text_head) < 0) */
/* 	{ */
/* 	    return -1; */
/* 	} */
/*     return 0; */
/* } */

struct YelpDataBST* create_business_bst(const char* businesses_path, const char* reviews_path)
{
    Bus_Tree* bus_tree = NULL;
    FILE* fp_bus = NULL;
    FILE* fp_rev = NULL;
    char* entry_bus = NULL;
    char* entry_rev = NULL;
    ssize_t read_bus;
    ssize_t read_rev;
    size_t len_bus = 0;
    size_t len_rev = 0;
    int length_arr = 1;
    char* delim = "\t";
    char** entry_Arr_bus;
    char** entry_Arr_rev;
    int i;
    int diff_ids = 0;
    int last_busid = -1;
    long file_offset = 0;
    fp_bus = fopen(businesses_path, "r");
    while((read_bus = getline(&entry_bus, &len_bus, fp_bus)) != -1){
	  entry_Arr_bus = explode(entry_bus, delim, &length_arr);
	  for (i=0;i<7;i++){
	      printf("%d: %s\n",(i+1),entry_Arr_bus[i]);
	  }
	  bus_tree = tree_insert(bus_tree,entry_Arr_bus[1],atoi(entry_Arr_bus[0]),entry_Arr_bus[2],entry_Arr_bus[4],entry_Arr_bus[3],entry_Arr_bus[5]);
	  destroyStringArray(entry_Arr_bus, length_arr);
    }
    free(entry_bus);
    fclose(fp_bus);
    
    fp_rev = fopen(reviews_path, "r");
    while((read_rev = getline(&entry_rev, &len_rev, fp_rev)) != -1){
	  entry_Arr_rev = explode(entry_rev, delim, &length_arr);
	  for (i=0;i<6;i++){
	      printf("%d: %s\n",(i+1),entry_Arr_rev[i]);
	  }
	  int bus_id = atoi(entry_Arr_rev[0]);
	  if(bus_id != last_busid){
	      diff_ids ++;
	      last_busid = bus_id;
	  }
	   destroyStringArray(entry_Arr_rev, length_arr);
    }
    Review* reviews = malloc(sizeof(Review) * diff_ids);
    fseek(fp_rev, 0, SEEK_SET);
    last_busid = -1;
    diff_ids = 0;
    while((read_rev = getline(&entry_rev, &len_rev, fp_rev)) != -1){
	entry_Arr_rev = explode(entry_rev, delim, &length_arr);
	 for (i=0;i<6;i++){
	     printf("%d: %s\n",(i+1),entry_Arr_rev[i]);
	 }
	 int bus_id = atoi(entry_Arr_rev[0]);
	 if(bus_id != last_busid){
	         reviews[diff_ids].Business_ID = bus_id;
	         reviews[diff_ids].file_offset = file_offset;
	         diff_ids++;
	         last_busid = bus_id;
	  }
	  file_offset = ftell(fp_rev);
	  destroyStringArray(entry_Arr_rev, length_arr);
    }
    for(i=0;i<diff_ids; i++){
	printf("#%d: ID: %d   Offset: %ld\n\n", (1+i),reviews[i].Business_ID, reviews[i].file_offset);
    }
    free(entry_rev);
    fclose(fp_rev);
  
    struct YelpDataBST* data = data_create(businesses_path,reviews_path);
    data->locations = bus_tree;
    data->reviews = reviews;
    for(i=0;i<diff_ids; i++){
	printf("#%d: ID: %d   Offset: %ld\n\n", (1+i),data->reviews[i].Business_ID, data->reviews[i].file_offset);
    }
    //free(reviews);
    tree_print(data->locations,0);
    return data;
}

struct Review* create_review_array(long offset, int id, const char* reviews_path)
{
    FILE* fp_rev = NULL;
    char* entry_rev = NULL;
    ssize_t read_rev;
    size_t len_rev = 0;
    int length_arr = 1;
    char* delim = "\t";
    char** entry_Arr_rev;
    int i;
    int k = 0;
    int num_reviews = 0;
    
    struct Review* reviews_array = NULL;
    fp_rev = fopen(reviews_path,"r");
    fseek(fp_rev,offset,SEEK_SET);
    while((read_rev = getline(&entry_rev, &len_rev, fp_rev)) != -1){
	entry_Arr_rev = explode(entry_rev, delim, &length_arr);
	if(id == atoi(entry_Arr_rev[0])){
	    num_reviews++;
	}
	destroyStringArray(entry_Arr_rev,length_arr);
    }

    reviews_array = malloc(sizeof(struct Review) * num_reviews);
    fseek(fp_rev,offset,SEEK_SET);
    while((read_rev = getline(&entry_rev, &len_rev, fp_rev)) != -1){
	    entry_Arr_rev = explode(entry_rev, delim, &length_arr);
	    for (i=0;i<6;i++){
		printf("%d: %s\n",(i+1),entry_Arr_rev[i]);
	    }
	    if(id == atoi(entry_Arr_rev[0])){
		reviews_array[k].stars = (uint8_t)atoi(entry_Arr_rev[1]);
		reviews_array[k].text = entry_Arr_rev[5];
		printf("#%d: stars: %d   Text: %s\n\n", (1+k),reviews_array[k].stars, reviews_array[k].text); 
		k++;
		destroyStringArray(entry_Arr_rev,length_arr);
	    }
	    else{
		destroyStringArray(entry_Arr_rev,length_arr);
		break;
	    }
	    
	}
    free(entry_rev);
    fclose(fp_rev);
    return reviews_array;
}
struct Location* create_loc_array(Bus_Location* locations, Review* review_offset, const char* reviews_path)
{
    int list_length = List_length(locations);
    Bus_Location* temp = locations;
    long* offsets = malloc(sizeof(long) * list_length);
    int* ids = malloc(sizeof(int) * list_length);
    struct Location* loc_array = malloc(sizeof(struct Location) * list_length);
    int i = 0;
    int k = 0;

    while(temp != NULL && k < list_length){
	if(temp->Business_ID == review_offset[k].Business_ID){
	// ids[k] = review_offset[i].Business_ID;
	//offsets[k] = review_offset[i].file_offset;
	loc_array[k].reviews = create_review_array(review_offset[k].file_offset,review_offset[k].Business_ID,reviews_path);
	k++;
	}
	else{
	    loc_array[i].reviews = NULL;
	}
	temp = temp->next;
    }

    for(i=0;i<list_length;i++){
	loc_array[i].address = locations->address;
	loc_array[i].state = locations->state;
	loc_array[i].city = locations->city;
	loc_array[i].zip_code =locations->zip;
	printf("#%d: address: %s  state: %s city: %s  zip: %s\n\n", (1+i),loc_array[i].address,loc_array[i].state,loc_array[i].city,loc_array[i].zip_code);
	locations = locations->next;
    }
    free(offsets);
    free(ids);
    return loc_array;
}
Bus_Tree * tree_search_name(char* name, Bus_Tree* root)
{
    if(root == NULL){
	return NULL;
    }
    if(strcmp(name,root->name) == 0){
	return root;
    }
    if(strcmp(name, root->name) < 0){
	return(tree_search_name(name,root->left));
    }
    return(tree_search_name(name,root->right));
}
    
struct Business* get_business_reviews(struct YelpDataBST* bst, char* name, char* state, char* zip_code)
{
    int check_zip = 0;
    int check_state = 0;
    if(zip_code != NULL){
	check_zip = 1;
    }
    if(state != NULL){
	check_state = 1;
    }
    Bus_Tree* locs_tree_root = tree_search_name(name, bst->locations);
    struct Location* location_array = create_loc_array(locs_tree_root->locations,bst->reviews,bst->reviews_path);
    if(((check_state && strcmp(state,locs_tree_root->locations->state) == 0) || !check_state) && ((check_zip && strcmp(zip_code,locs_tree_root->locations->zip) == 0) || !check_zip)){}
	
    return 0;
}
void destroy_business_bst(struct YelpDataBST* bst)
{}
void destroy_business_result(struct Business* b)
{}

