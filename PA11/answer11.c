#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "answer11.h"


HuffNode* HuffNode_create(int value)
{
    HuffNode* new_node = malloc(sizeof(HuffNode));
    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void HuffNode_destroy(HuffNode* tree)
{
    if(tree == NULL){
	return;
    }
    HuffNode_destroy(tree->left);
    HuffNode_destroy(tree->right);
    free(tree);
}

void tree_print(HuffNode* root, int indent)
{
if(root == NULL){
    return;
 }
int i;
for(i=0;i<indent;++i){
    printf("  ");
 }
printf("%p '%d' (%p %p)", root, root->value, root->left, root->right);
printf("\n\n");
tree_print(root->left, indent - 1);
tree_print(root->right, indent + 1);
}

StackNode * List_createNode(int value)
{
    StackNode * new_node = malloc(sizeof(StackNode));
    new_node->tree = HuffNode_create(value);
    new_node->next = NULL;
    return new_node;
}

Stack * Stack_create()
{
    Stack* empty_stack = malloc(sizeof(Stack));
    empty_stack->head = NULL;
    return empty_stack;
}

void print_stack(Stack* node)
{
    Stack* itr = node;
    itr->head = node->head;
    while(itr->head != NULL){
	printf("[%p %p]", itr->head,itr->head->next);
	tree_print(itr->head->tree, 0);
	if(itr->head->next !=NULL){
	    printf("==>");
	}
	itr->head = itr->head->next;
    }
}

void List_destroy(StackNode* list){
    if(list == NULL){
	return;
    }
    List_destroy(list->next);
    HuffNode_destroy(list->tree);
    free(list);
}
void Stack_destroy(Stack * stack)
{
    if(stack == NULL){
	return;
    }
    List_destroy(stack->head);
    free(stack);
}
int Stack_isEmpty(Stack * stack)
{
    if(stack != NULL){
	return 1;
    }
    return 0;
}

HuffNode * Stack_popFront(Stack * stack)
{
    StackNode* temp = stack->head;
    HuffNode* tree = temp->tree;      //is this legal???
    temp = stack->head->next;
    HuffNode_destroy(stack->head->tree);
    free(stack->head);
    stack->head = temp;
    return(tree);
}

void Stack_pushFront(Stack * stack, HuffNode * tree)
{
    StackNode * new_head = malloc(sizeof(StackNode));
    new_head->tree = tree;
    new_head->next = stack->head;
    stack->head = new_head;
    //free(new_head);
}
HuffNode * HuffTree_readTextHeader(FILE * fp){return 0;}
HuffNode * HuffTree_readBinaryHeader(FILE * fp){return 0;}
