#include "answer09.h"

int main(int argc, char** argv)
{	
	//Create a Binary Tree
	BusinessNode * root = create_node("5.0", "random name", "random address");
   	root->left = create_node("3.5", "another name", "another address");
   	root->right = create_node("4.0", "yet another name", "some address");
   	root->left->right = create_node("1.5", "name 3", "address 3");
 	
	//Create a Node
	BusinessNode * insert = create_node("4.3", "James Brown", "65 Sutton Pt");

	//Prints First Node	
	print_node(root);
 	
	//Prints Entire Tree
	print_tree(root);

	//Inserts a Node
	tree_insert(root, insert);	

   	return 0;	
}
