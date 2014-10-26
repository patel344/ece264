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
List * List_merge(List * lhs, List * rhs, int (*compar)(const char *, const char*)){
	List * result = NULL;
	if(compar(lhs->str,rhs->str) <= 0){
		result = lhs;
		result->next = List_merge(lhs->next,rhs,int(*)compar(lhs->str,rhs->str));
	}
	else{
		result = lhs;
		result->next = List_merge(lhs,rhs->next,int(*)compar(lhs->str,rhs->str));
	}
	return(result);
}
