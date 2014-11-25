#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "answer11.h"

void tree_print(HuffNode* root, int indent);
StackNode * List_createNode(int value);
void print_stack(Stack* node);
void List_destroy(StackNode* list);
int main(int argc, char** argv)
{
    /*HuffNode* tree = HuffNode_create(32);
    tree->left = HuffNode_create(23);
    tree->right = HuffNode_create(54);
    tree_print(tree,0);
    HuffNode_destroy(tree);
    */

    Stack* newStack = Stack_create();
    newStack->head = List_createNode(45);
    newStack->head->tree->left = HuffNode_create(33);
    newStack->head->tree->right = HuffNode_create(87);
   
    newStack->head->next = List_createNode(53);
    newStack->head->next->tree->left = HuffNode_create(9);
    newStack->head->next->tree->right = HuffNode_create(100);
    //print_stack(newStack);
    HuffNode* popped_tree = Stack_popFront(newStack);
    //print_stack(newStack);
    //tree_print(popped_tree,0);
    //Stack_destroy(newStack);
    Stack_pushFront(newStack, popped_tree);
    //print_stack(newStack);
    List_destroy(newStack->head->next);
    free(newStack->head);
    free(newStack);
    //print_stack(newStack);
    //Stack_destroy(newStack);
    


    return 0;
}
