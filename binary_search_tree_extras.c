#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define COUNT 10

struct node
{
  int data;
  struct node* left; // Left node / Smaller node
  struct node* right; // right node / Larger Node
};

typedef struct node TNode;

// Let us now generate a random array for the Binary Search Tree
int * genrandarr(int n)
{
    int * arr = malloc(n * sizeof(int));
    if(arr)
    {
        for (int i = 0; i < n; i++)
            {
                arr[i] = rand() % 10000;
            }
    }
    return arr;
}


// traversing the tree in order as this makes the most sense to me
void PreOrder(struct node* root)
{
    if (root == NULL) return;
    printf("-> %d ", root->data);
    PreOrder(root->left);
    PreOrder(root->right);
}

// Create a new Node
TNode* MakeANode(val)
{
    TNode* NewNode = malloc(sizeof(TNode));
    NewNode->data = val;
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}


// Function to insert data into a specific binary search tree

TNode* InsertInTree(TNode* root, int data)
{

	if(root==NULL) return MakeANode(data);

	if (data < root->data)
    {
        root->left = InsertInTree(root->left , data);
    }

	else if (data > root->data)
    {
        root->right = InsertInTree(root->right, data);
    } 
	return root;
}


TNode* genTree(TNode* root, int* a, int n)
{
    // Inserting values into the tree based on the randomly generated array
    for (int i = 0; i < n; i++)
    {
        root = InsertInTree(root, a[i]);
    }
    return root;
}


// Code based on snippet from geeksforgeeks to print 2D model
void PrintTree2D(TNode* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increasing the distance between levels to form that req. negative space
    space += COUNT;
 
    // Processing the right child first
    PrintTree2D(root->right, space);

    // Printing the current node with required spaces
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Now we process the left child recursively
    PrintTree2D(root->left, space);
}

// Inorder traversal
void PrintInOrder(TNode* root)
{
    if (root == NULL) return;
    PrintInOrder(root->left);
    printf(" -> %d", root->data);
    PrintInOrder(root->right);
}

// ! Function to free memory allocated to a BST.
void FreetheTree(TNode* root)
{
	free(root);
}

/*
    Psuedo Code for Binary Tree Deletion:
    1. If the node to be deleted is a leaf node, simply delete it.
    2. If the node to be deleted has only one child, then switch the positions of the two and the delete it.
    This would depend on whether the left child or the right child is the child in question.
    If we used the right branch, then we would have to switch the positions of the right child and the parent.
    Using successors.
    For the left, we would have to switch the positions of the left child and the parent. Using predecessors.
*/


// Function to find the 'successor' value of a node in a Binary Tree
int SuccesorNode(TNode* root)
{
	// Looking for the successor of the root node
	// First we move to the right side to get a node with a larger value
	root = root->right;
	// Now, loop until we reach end of the left branch to get the successor
	while (root->left) root = root->left;
	return root->data; // So we just return the value at the current node which will be the value of the successor
}

// Function to find the 'predecessor' value of a node in a Binary Tree
int PredecessorNode(TNode* root)
{
	// Looking for the predecessor of the root node
    // First we move to the left side to get a node with a smaller value
	root = root->left;
	// Looping until we reach the end of the right branch to get the predecessor
	while (root->right) root = root->right;
	return root->data; // So we just return the value at the current node - the value of the predecessor
}

// Now for the function to delete a specified node from the Binary Tree
TNode* DeleteFromTree(TNode* root, int x)
{
	// If the root is NULL then simply return it (nothing to delete)
	if (root == NULL) return root;

	// If the element-to-be-deleted is smaller than the current value, we start deletion from the left branch
    // And if it is greater, than we start deletion from the right branch
    if (x < root->data) root->left = DeleteFromTree(root->left, x);
    else if (x > root->data) root->right = DeleteFromTree(root->right, x);

	// Alternatively, we are either at the required element, or that element is the root of the tree
	else
    {
		// Checking if root is null (leaf node)
        // If it is then simply set to NULL and return
		if (root->left == NULL && root->right == NULL) root = NULL;

		// If Right node exists, then recursively replace the current node with its successor's data
		else if (root->right)
        { 
			root->data = SuccesorNode(root);
			root->right = DeleteFromTree(root->right, root->data);
		}

		// Else only a Left node exists, in which case we do similar to above with predecessor's data instead
		else {
			root->data = PredecessorNode(root);
			root->left = DeleteFromTree(root->left, root->data);
		}
	}
	return root;

}


int main(int argc, char **argv)
{
    int * a;
    int n;
    int x;
    printf("How many elements should be in the Binary Tree? \n");
    scanf("%d", &n);

    srand(time(NULL));
    a = genrandarr(n);
    /*
    This piece of code was to check if the Binary tree was forming correctly 
    When using random values, I was getting degenerate trees and some trees that looked like complete nonsense
    To check if code is indeed correct, you can comment out the random array
    and use this predefined tester array instead:
    
    int a[] = {4, 2, 1, 3, 8, 6, 13}; // Array to be used to generate BST
	int n = 7;
    */

    TNode* root = NULL;
    root = genTree(root, a, n);

    printf("    The Binary Search Tree     \n");
    
    PrintTree2D(root, 0);
    
    printf("The inorder traversal of the Binary Tree is: \n");
    PrintInOrder(root);
    printf("\n");

    printf("Enter the value of the node to be deleted: \n");
    scanf("%d", &x);

    root = DeleteFromTree(root, x);
    printf("The inorder traversal of the Binary Tree after deletion is: \n");
    PrintInOrder(root);

    printf("\n    The Binary Search Tree     \n");
    PrintTree2D(root, 0);
    //printf("The Preorder traversal of the Binary Tree is: \n");
    //PreOrder(root);

    FreetheTree(root);
    free(a);
    return 0;
}