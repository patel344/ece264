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
	printf("Before Insertion\n");
	print_tree(root);

	//Inserts a Node
	printf("\n\nAfter Insertion\n");
	tree_insert(insert,root);
	print_tree(root);

	//Loads tree from file
        BusinessNode * root2 = load_tree_from_file("shortfile.tsv");
	//print_tree(root2);
	
	//Searches tree for a name
	BusinessNode * root3 = tree_search_name("Culver's", root2);
	print_tree(root3);
	
	//Destroy Tree
	destroy_tree(root2);
	free(insert);
	free(root->left->right);
	free(root->right);
	free(root->left);
	free(root);
	
		
   	return 0;	
}
