#include <stdio.h>
#include <stdlib.h>
#define COUNT 10

struct node
{
  int data;
  struct node* left; // Left node / Smaller node
  struct node* right; // right node / Larger Node
};

typedef struct node TNode;

// traversing the tree in order as this makes the most sense to me
void PreOrder(struct node* root) {
  if (root == NULL) return;
  printf("%d ->", root->data);
  PreOrder(root->left);
  PreOrder(root->right);
}

// Create a new Node
TNode* MakeANode(value)
{
    TNode* NewNode = malloc(sizeof(TNode));
    NewNode->data = value;
    NewNode->left = NULL;
    NewNode->right = NULL;

    return NewNode;
}

// Inserting data on the left side of the node
TNode* insertLeft(TNode* root, int value)
{
    root->left = MakeANode(value);
    return root->left;
}

// Inserting data on the right side of the node
TNode* insertRight(TNode* root, int value)
{
    root->right = MakeANode(value);
    return root->right;
}


// Code based on snippet from geeksforgeeks to print 2D model
void print2DUtil(TNode* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(TNode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}

// ! Function to free memory allocated to a BST.
void FreetheTree(TNode* root)
{
	free(root);
}

int main()
{
    TNode* root = MakeANode(1);
    insertLeft(root, 2);
    insertRight(root, 3);
    insertLeft(root->left, 4);

    printf("Traversing the tree in Order: \n");
    print2D(root);
    FreetheTree(root);
    
}