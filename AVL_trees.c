#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

// Unlike with BST's, AVL trees are self balancing trees and require a height parameter as well
struct Node
{
    int data; // value stored in a node
    struct Node* left; // Left child
    struct Node* right; // Right child
    int height;

    // For an AVL tree, height difference between the left and right child is at most 1
    // Height of a node = 1 + the height of the taller child
    // Height must always change during insertion and deletion, dependent on the child(ren).

};

typedef struct Node TNode;

// Before we start creating nodes and the trees themselves,
// We create some helper functions such as findmax and a height function
// We do not need a swap function as AVL trees use the rotate function that we shall create later

// finding the max between x and y
int FindMax(int x, int y) { return (x > y)? x : y; }

// Finding the height of a node
// To find the height of a node so that we can decide whether the tree is balanced or not and what all to change
// Learnt use of the ? operator through class lectures and online code
int FindHeight(TNode* root)
{
    if (root == NULL) return 0;
    else return (root->height);
}

// Now the code to create a node, similar to the BST code
TNode* MakeANode(int x)
{
    TNode* newNode = (TNode*)malloc(sizeof(TNode));
    newNode->data = x;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // Height of a new node is 1
    return newNode;
}

// Before starting the rotate functions, we need a function to find the Balance of the tree
int AVLBalance(TNode* root)
{
    if (root == NULL) return 0;
    else return (FindHeight(root->left) - FindHeight(root->right));
}

/*
    Now we can create functions for the four cases of rotation:
    - Rotate left
    - Rotate right
    - Rotate left then right (leftright)
    - Rotate right then left (rightleft)

    These are based on the cases of how the tree is unbalanced:
    - Left Left Case -> where Both the child and the grandchild are on the left side
    - Left Right Case -> where the child is on the left and the grandchild is on the right
    - Right Right Case -> where Both the child and the grandchild are on the right side
    - Right Left Case -> where the child is on the right and the grandchild is on the left
*/

// Rotate left
// Input node is the node to be rotated
TNode* RotateLeft(TNode* root)
{
    TNode* newRoot = root->right;
    TNode* temp = newRoot->left; // temp is the left child of the new root and originally has value of 
                                 // left child of the right child of the inputed root

    //edge case of the root of sub-tree being null
    if (newRoot == NULL) return root;

    // Performing rotation
    newRoot->left = root; // Now left child is the parent node
    root->right = temp;   // And the original right child is the new left child

    // Update heights
    root->height = FindMax(FindHeight(root->left), FindHeight(root->right)) + 1;
    newRoot->height = FindMax(FindHeight(newRoot->left), FindHeight(newRoot->right)) + 1;

    // Return new root
    return newRoot;
}

// Rotate right
// Input node is the node to be rotated
TNode* RotateRight(TNode* root)
{
    TNode* newRoot = root->left;
    TNode* temp = newRoot->right; // temp is the right child of the new root and originally has value of 
                                 // right child of the left child of the inputed root

    //edge case of the root of sub-tree being null
    if (newRoot == NULL) return root;

    // Performing rotation
    newRoot->right = root; // Now right child is the parent node
    root->left = temp;   // And the original left child is the new right child

    // Update heights
    root->height = FindMax(FindHeight(root->left), FindHeight(root->right)) + 1;
    newRoot->height = FindMax(FindHeight(newRoot->left), FindHeight(newRoot->right)) + 1;

    // Return new root
    return newRoot;
}

// Rotate left then right
// Input node is the node to be rotated
TNode* RotateLeftRight(TNode* root)
{
    root->left = RotateLeft(root->left);
    return RotateRight(root);
}

// And finally
// Rotate right then left
// Input node is the node to be rotated
TNode* RotateRightLeft(TNode* root)
{
    root->right = RotateRight(root->right);
    return RotateLeft(root);
}

// Now that we have the code for rotations, We can create the code for insertion and balancing of nodes into the tree
// Insertion is similar to the BST code at first and then we worry about balancing

// Code for balancing an AVL tree for both insertion and deletion

TNode* BalanceForInsert(TNode* root, int DiffInHeight, int val) {

    /*
    If the height difference is less than -1 and the input value is greater than the right child's value, 
    we have a double right heavy tree/subtree.
    So simply rotate left to balance.
    */
    if (DiffInHeight < -1 && val > root->right->data) return RotateLeft(root);

    /*
    If the height difference is greater than 1 and the input value is smaller than the right child's value,
    we have a double left heavy tree/subtree and balance by rotating right.
    */
    if (DiffInHeight > 1 && val < root->left->data) return RotateRight(root);

    /*
    If the height difference is less than -1 and the input value is smaller than the right child's value,
    we have a tree/subtree that is first right then left heavy and balance it by rotating right then left.
    */
    if (DiffInHeight < -1 && val < root->right->data) return RotateRightLeft(root);
    
    /*
    Lastly, if the height difference is greater than 1 and the input value is greater than the left child's value,
    we have a tree/subtree that is first left then right heavy and balance it by rotating left then right.
    */
    if (DiffInHeight > 1 && val > root->left->data) return RotateLeftRight(root);

    // If none of the above conditions are met, then the tree/subtree is already balanced.
    return root;
}

// Same logic as previous but now we check for the height difference and balance the tree accordingly
// instead of comparing the input values (As there won't be any input values in the deletion function)
// Also, We compare the AVLBalance with 0 to find out if and how the tree is unbalanced.
TNode* BalanceForDelete(TNode* root, int DiffInHeight)
{
    // Double right heavy tree/subtree
    if (DiffInHeight < -1 && AVLBalance(root->right) <= 0) return RotateLeft(root);

    // Double left heavy tree/subtree
    if (DiffInHeight > 1 && AVLBalance(root->left) >= 0) return RotateRight(root);

    // First right then left heavy tree/subtree
    if (DiffInHeight < -1 && AVLBalance(root->right) > 0) return RotateRightLeft(root);
    
    // First left then right heavy tree/subtree
    if (DiffInHeight > 1 && AVLBalance(root->left) < 0) return RotateLeftRight(root);

    // If none of the above conditions are met, then the tree/subtree is already balanced.
    return root;
}

// Finally, we can write the code for creation of the tree now that we have all the required helped and comparison functions    

// Code to Insert a node into an AVL Tree
TNode* InsertInTree(TNode* root, int val)
{
    // Normal BST insertion (from binary search tree code)
    if (root == NULL) return(MakeANode(val));
    if (val < root->data) root->left  = InsertInTree(root->left, val);
    else if (val > root->data) root->right = InsertInTree(root->right, val);
    else return root;

    // Now we balance the tree with the help of the functions we created above
    
    // If the value entered was not equal to the value at the root, then we update the height of the root
    root->height = 1 + FindMax(FindHeight(root->left), FindHeight(root->right));

    // Checking if any balancing is required by outputting Height difference
    int DiffInHeight = AVLBalance(root);

    // we return the balanced tree
    return BalanceForInsert(root, DiffInHeight, val);
}

// Similarly, the code for deletion from the tree
// However, we need to check for the case where the node to be deleted is a leaf node , i.e., check for successors

// We can use the code for finding the successor from the BST code
int SuccesorNode(TNode* root)
{
	// Looking for the successor of the root node
	// First we move to the right side to get a node with a larger value
	root = root->right;
	// Now, loop until we reach end of the left branch to get the successor
	while (root->left) root = root->left;
	return root->data; // So we just return the value at the current node which will be the value of the successor
}

// Code for deletion from an AVL tree
TNode* DeleteFromAVL(TNode* root, int x)
{
	// If the root is NULL then simply return it (nothing to delete)
	if (root == NULL) return root;

	// If the element-to-be-deleted is smaller than the current value, we start deletion from the left branch
    // And if it is greater, than we start deletion from the right branch
    if (x < root->data) root->left = DeleteFromAVL(root->left, x);
    else if (x > root->data) root->right = DeleteFromAVL(root->right, x);

	// Alternatively, we are either at the required element, or that element is the root of the tree
	else {
        // We either have 1 or no children of the root
		if( (root->left == NULL) || (root->right == NULL) )
        {
            // We store the non-NULL child in a temporary node
            // NULL if both are NULL
            TNode* temp = root->right ? root->right : root->left;
            // If the temporary node is NULL, then we have no children
            if (temp == NULL)
            {
                // simply delete by setting to NULL
                root = NULL;
            }
            // Else we have only 1 child, so we copy the data of the child to the root
            else *root = *temp; // could also use data instead of *root
            // Now we free the memory of the temp node which will be the original root
            free(temp);
        }
        // or we have both children
        else
        {
            // We find the successor of the root
            int temp = SuccesorNode(root);
            // We copy the successor value to the root
            root->data = temp;
            // then delet the successor from the right branch
            root->right = DeleteFromAVL(root->right, temp);
        }
	}
	
    // I had removed this line of code and then the entire delete function stopped working
    // Do not really understand why yet
    if (root == NULL) return root;

    // Similar to the insert function, Now we check if the tree is balanced or not and balance it accordingly

    // If the value entered was not equal to the value at the root then we update the height of the root
    root->height = 1 + FindMax(FindHeight(root->left), FindHeight(root->right));

    int DiffInHeight = AVLBalance(root);
    return BalanceForDelete(root, DiffInHeight);
}

// And the code from BST to make a 2D model:
void PrintTree2D(TNode* root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increasing the distance between levels to form that req. negative space
    space += 10;
 
    // Processing the right child first
    PrintTree2D(root->right, space);

    // Printing the current node with required spaces
    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");
    printf("%d\n", root->data);
 
    // Now we process the left child recursively
    PrintTree2D(root->left, space);
}


// Driver code
// Went online to https://www.studytonight.com/c/programs/misc/menu-driven-program to understand how to make a menu driven program

int main(int argc, char** aargv)
{
    TNode* root = NULL;
    int n, val, choice, flag = 0; // Flag for do-while loop

    printf("AVL tree program for Data Structures! \n\n\n");

    do {
        printf("Enter the number of nodes your AVL tree must have: ");
        scanf("%d", &n);

        if (n < 1) {
            printf("Invalid input - Retry!");
            flag = 1;
        }
        else {
            flag = 0;
            for(int i = 0; i < n; i++) {
                printf("Enter value %d: ", i+1);
                scanf("%d", &val);
                root = InsertInTree(root, val);
            }
        }
    } while (flag == 1);

    printf("\n\nYour specified AVL tree is:\n");
    PrintTree2D(root, 0);

    do {
        printf("\n\n1. Inserting a value\n2. Removing/Deleting a value\n3. Show your tree\n4. Empty the tree (remove all elements)\n5. Exit\n\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: printf("Enter the value you want to insert: ");
                    scanf("%d", &val);
                    root = InsertInTree(root, val);
                    break;

            case 2: printf("Enter the value you want to remove: ");
                    scanf("%d", &val);
                    root = DeleteFromAVL(root, val);
                    break;

            case 3: printf("\n\nYour AVL Tree is: \n");
                    PrintTree2D(root, 0);
                    break;
            
            case 4: root = NULL;
                    printf("\n\nThe tree has been emptied. Insert new values to create a new tree.\n");
                    break;

            case 5: printf("Program terminated.\n");
                    break;

            default:    printf("Invalid input - Retry!");
                        break;
        }
    }while(choice != 5);

    free(root);
    
    return 0;
}

