#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "answer11.h"

void tree_print(HuffNode* root, int indent);
StackNode * List_createNode(int value);
void print_stack(Stack* node);
void List_destroy(StackNode* list);
int read_bit(FILE* fp, unsigned char* bit, unsigned char* whichbit, unsigned char* curbyte);
int get_bit(FILE* fp, int* rem_num, char* bitarr);
int main(int argc, char** argv)
{
    /*HuffNode* tree = HuffNode_create(32);
    tree->left = HuffNode_create(23);
    tree->right = HuffNode_create(54);
    tree_print(tree,0);
    HuffNode_destroy(tree);
    */

    /* Stack* newStack = Stack_create(); */
    /* newStack->head = List_createNode(45); */
    /* newStack->head->tree->left = HuffNode_create(33); */
    /* newStack->head->tree->right = HuffNode_create(87); */
   
    /* newStack->head->next = List_createNode(53); */
    /* newStack->head->next->tree->left = HuffNode_create(9); */
    /* newStack->head->next->tree->right = HuffNode_create(100); */
    /* //print_stack(newStack); */
    /* HuffNode* popped_tree = Stack_popFront(newStack); */
    /* //print_stack(newStack); */
    /* //tree_print(popped_tree,0); */
    /* //Stack_destroy(newStack); */
    /* Stack_pushFront(newStack, popped_tree); */
    /* //print_stack(newStack); */
    /* Stack_popPopCombinePush(newStack); */
    /* //List_destroy(newStack->head->next); */
    /* //free(newStack->head); */
    /* //free(newStack); */
    /* print_stack(newStack); */
    /* Stack_destroy(newStack); */
    
    FILE* fp = fopen("05-badges.txt-huff","r");
    HuffNode* tree = HuffTree_readTextHeader(fp);
    HuffNode_destroy(tree);
  
    FILE* fp2 = fopen("test2.bit", "rb");
    unsigned char whichbit = 0;
    unsigned char curbyte = 0;
    unsigned char bit = 0;
    int rem_num = 0;

    char bitarr;
    for(rem_num = 0; rem_num <8; rem_num ++){
	int bit_val = get_bit(fp2, &rem_num, &bitarr);
	printf("%d\n", bit_val);
    }
    FILE* bin_fp = fopen("07-description.bit-huff","rb");
    HuffNode* bin_tree = HuffTree_readBinaryHeader(bin_fp);
    HuffNode_destroy(bin_tree);
    return 0;
}
