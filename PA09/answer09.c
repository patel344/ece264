#include "answer09.h"

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
	printf("================\n\n");
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
		return (create_node(root->stars, root->name, root->address));
	}
	if(strcmp(root->address,node->address) == 0)
	{
		return node;
	}
	if(strcmp(root->name,node->name) <= 0)
	{
		node->left = tree_insert(node->left , root);
	}
	else
	{
		node->right = tree_insert(node->right , root);
	}
	return node;
}
