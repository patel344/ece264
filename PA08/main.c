#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "answer08.h"
int comparstr(const char *p1, const char *p2); 
/*int comparstr(const char *p1, const char *p2) {
		return strcmp(p1,p2);
}*/
List* append(List* result,List* list);
void listprint(List* node);
void listprint(List* node){
	while(node != NULL){
		printf("[%p ('%s' %p)]",node,node->str,node->next);
		if(node->next != NULL)
			printf(" ==> ");
		node = node->next;
	}
	printf("\n");
}
void split_list(List* list, List** newHead);
void test_split(List * list)
{
	List * newHead = NULL;
	printf("\n\n*****\nBefore split\n");
	printf("list: ");
	listprint(list);
	split_list(list, &newHead);
	printf("\nAfter split\n");
	printf("lhs: "); listprint(list);
	printf("rhs: "); listprint(newHead);
}

int main(int argc, char** argv){
	List* Sort1 = NULL;
	List* Sort2 = NULL;
	List* Result = NULL;
	
	Sort1 = NULL;
	Sort2 = NULL;
	//Sort1 = List_createNode("B");
	//Sort1->next = List_createNode("G");
	//Sort1->next->next = List_createNode("X");

	//Sort2 = List_createNode("A");
	//Sort2->next = List_createNode("D");
	//Sort2->next->next = List_createNode("F");
	//Sort2->next->next->next = List_createNode("Z");

	// print the lists before sorting
	printf("Sort1: "); listprint(Sort1);
	printf("Sort2: "); listprint(Sort2);

//	test_split(Sort1);
//	test_split(Sort2);

	Result = List_merge(Sort1,Sort2,comparstr);
	printf("\n\nMerged: "); listprint(Result);
        
//	Result = append(Sort1,Sort2);
//	printf("\n\nappended: "); listprint(Result);
	Result = List_sort(Sort2,comparstr);
	printf("\n\nSorted: "); listprint(Result);	
	return 0;
}
