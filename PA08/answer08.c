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

List* append(List* result, List* list){
	List* begin = result;
	if(result == NULL){
		return list;
	}
	while(result->next != NULL){
		result = result->next;
	}
	result->next = list;
	return (begin);
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
	List * right = rhs->next;
	List * left = lhs->next;
	while(lhs != NULL && rhs != NULL){ 
		if(compar(lhs->str,rhs->str) <= 0){
			lhs->next = NULL;
			result = append(result,lhs);
			lhs = left;
			if(lhs != NULL){
				left = lhs->next;
			}
		}
		else{
			rhs->next = NULL;
			result = append(result,rhs);
			rhs = right;
			if(rhs != NULL){
				right = rhs->next;
			}
		}
	}
		if(lhs == NULL && rhs != NULL){  //IF LHS List is Shorter
			return(append(result,rhs));
		}
		if(lhs != NULL && rhs == NULL){ //IF RHS List is Shorter
			return(append(result,lhs));
		}
	return(result);
}

void split_list(List* list, List** newHead){ //SPLITS LIST INTO TWO SEPARATE LISTS OF EQUAL(ISH) LENGTHS
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
	list = List_sort(list,compar);   //RECURSIVE CASE
	newHead = List_sort(newHead,compar); //RECURSIVE CASE
	list = List_merge(list,newHead,compar); //MERGE THE TWO SORTED LISTS
	return (list);
}
