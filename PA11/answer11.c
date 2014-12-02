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
    if(stack->head != NULL){
	return 1;
    }
    return 0;
}

HuffNode * Stack_popFront(Stack * stack) //do I need to call HuffNode_destroy()
{
    if(stack->head == NULL){
	printf("Empty\n");
	return 0;
    }
    StackNode* temp = stack->head;
    stack->head = temp->next;
    HuffNode* tree = temp->tree;
    free(temp);
    return tree;
}

void Stack_pushFront(Stack * stack, HuffNode * tree)  //do I need to free new_head
{
    StackNode * new_head = malloc(sizeof(StackNode));
    new_head->tree = tree;
    new_head->next = stack->head;
    stack->head = new_head;
}
void Stack_popPopCombinePush(Stack * stack)
{
    HuffNode* tn1 = Stack_popFront(stack);
    HuffNode* tn2 = Stack_popFront(stack);
    HuffNode* tn = malloc(sizeof(HuffNode));
    tn->value = tn1->value + tn2->value;
    tn->left = tn2;
    tn->right = tn1;
    Stack_pushFront(stack,tn);
}
HuffNode * HuffTree_readTextHeader(FILE * fp)
{
    Stack * stack = Stack_create();
    int read;
    int done = 0;
    int char_val;
    if(fp == NULL){
	return NULL;
    }
    while(done == 0){
	read = fgetc(fp);
	if(!read){
	    break;
	}
	if(read == '1'){
	    char_val = fgetc(fp);
	    StackNode* value = List_createNode(char_val);
	    Stack_pushFront(stack, value->tree);
	    free(value);
	}
	else if(read == '0'){
	    if(Stack_isEmpty(stack) == 1){
		if(stack->head->next == NULL){
		    done = 1;
		}
		else{
		    Stack_popPopCombinePush(stack);
		}
	    }
	}
	else{
	    printf("%d\n",read);
	    printf("Error, neither a 0 or 1 was read\n");
	}
    }
    HuffNode* tree = stack->head->tree;
    free(stack->head);
    free(stack);
    return (tree);
}
//MODIFIED FROM AARONS STEP THROUGH OF BITWISE OPERATIONS
int get_bit(FILE* fp, int* rem_num, char* bitarr)
{
    if(*rem_num == 0){ //empty
	int ch = fgetc(fp);
	if(ch == -1){
	    return -1;
	}
	*bitarr = ch;
       	*rem_num = 8;
    }
    //ready to dispense bit nummber (*rem_num -1)
    int bit_no = *rem_num - 1;
    *rem_num -= 1; //done with this bit
    return(*bitarr & (1 << bit_no)) >> bit_no;
}
//MODIFIED FROM COURSE NOTES ON PAGE 481
HuffNode * HuffTree_readBinaryHeader(FILE * fp)
{
    int done = 0;
    int rem_num = 0;
    char bitarr;
    Stack* stack = Stack_create();
    
    while(done == 0){
	int bit_val = get_bit(fp, &rem_num, &bitarr);
	if(bit_val == 1){
	    int bitcount;
	    unsigned char value = 0;
	    for(bitcount = 0; bitcount < 8; bitcount++){
		value <<= 1; //shift left by one
		bit_val = get_bit(fp, &rem_num, &bitarr);
		value |= bit_val;
	    }
	    
	    StackNode* ret_val = List_createNode(value);
	    Stack_pushFront(stack, ret_val->tree);
	    free(ret_val); 
	}
	else if(bit_val == 0){
	    if(Stack_isEmpty(stack) == 1){  
		if(stack->head->next == NULL){ 
		    done = 1;
		}
		else{
		    Stack_popPopCombinePush(stack);
		}
	    }
	}
	else{
	    printf("Error, not reading correct bit values\n");
	}
    }
    HuffNode* tree = stack->head->tree;
    free(stack->head);
    free(stack);
    return tree;
}
