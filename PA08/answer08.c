#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "answer08.h"

List * List_createNode(const char * str){
	List * new_node = malloc(sizeof(List));
	new_node->str = strdup(str);
	new_node->next = NULL;
	return new_node;
}

void List_destroy(List * list){
	if(list == NULL){
		return;
	}
	List_destroy(list->next);
	free(list->str);
	free(list);
}

int List_length(List * list){
	int len = 0;
	while(list != NULL){
		len++;
		list = list -> next;
	}
	return len;
}

int comparstr(const char *p1, const char *p2) {
    return strcmp(p1,p2);
}

List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*)){
	List * result = NULL;
	if(lhs == NULL || rhs == NULL){
		if(lhs == NULL && rhs == NULL){
			return result;
		}
		else if(lhs == NULL){
			return rhs;
		}
		else{
			return lhs;
		}
	}
	else{
		if(compar(lhs->str,rhs->str) <= 0){
			result = List_createNode(lhs->str);
			result->next = List_merge(lhs->next,rhs,compar);
		}
		else{
			result = List_createNode(rhs->str);
			result->next = List_merge(lhs,rhs->next,compar);
		}
		return(result);
	}
}

void split_list(List* list, List** newHead){
   	int i, len = List_length(list);
	List* itr = list;
	*newHead = list->next;
	for(i = 1; i < (len / 2); i++){
		itr = itr->next; //itr is now the last node of the first list
		*newHead = (*newHead)->next; //new head of second list
	}
	itr->next = NULL; //splits the list
}	


List * List_sort(List * list, int (*compar)(const char *, const char*)){
	List* newHead = NULL;
	if(List_length(list) < 2){
		return list;  //BASE CASE
	}
	split_list(list,&newHead);
	List_sort(list,compar);
	List_sort(newHead,compar);
	//list = List_merge(newHead,list,compar);
	
	return (List_merge(list,newHead,compar));
}
