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
void PreOrder(struct node* root) {
  if (root == NULL) return;
  printf("%d ->", root->data);
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

// ! Function to free memory allocated to a BST.
void FreetheTree(TNode* root)
{
	free(root);
}

int main(int argc, char **argv)
{
    int * a;
    int n;
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
    
    PrintTree2D(root, 0);
    
    FreetheTree(root);
    free(a);
    return 0;
}