#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
  

struct Nodetype
{ 
    int data; 
    struct Nodetype *next; 
};

// Just making code easier to understand
typedef struct Nodetype Node;

// Initialising the top of the stack
Node *Top = NULL;

// Now we write a test to check if our stack is empty or not

int IsStackEmpty(Node *Top)
{
    if (Top == NULL) return 0;
    else return 1;
}

// Then the code to create the stack
// We will use a linked list to create the stack
// We will also know that stacks work on the principle of LIFO (Last In First Out)

void push(Node **Top, int x)
{
    // First we create a temporary node to use to add to the stack
    Node *temp = malloc(sizeof(Node));
    temp -> data = x;
    temp -> next = (*Top);
    // Initializes the top of the stack by setting the new node as the top of the stack
    (*Top) = temp;
}

// function to remove or 'pop' the top node or last node in
int pop(Node **Top)
{
    // First we create a temporary node to use to remove from the stack
    Node *temp = malloc(sizeof(Node));
    int a;

    if ((*Top) == NULL)
    {
        printf("The Stack is empty now");
    }
    else
    // There are values in the stack and we have to remove the top node
    {
        temp = (*Top);
        // Setting the next value of the Stack as the new top so we do not lose the entire linked list
        (*Top) = (*Top) -> next;
        a = temp -> data;
        free(temp);
    }
    return a;
}

// Function to display the stack
void Display(Node *Top)
{
    Node *temp = Top;
    while (temp != NULL)
    {
        printf("-%d", temp->data);
        temp = temp -> next;
    }
    printf("\n");
}

void FreeTheStack(Node* Top)
{
    Node* prevNode;
    while(Top)
    {
        prevNode = Top;
        Top = Top->next;
        free(prevNode);
    }
}


int main(int argc, char** argv)
{
    Node* Stack = NULL;
    int x;
    int opt = 0;

    printf("\n Below is the program to create a stack and implement some basic function calls on it: \n\n");
    while(opt != 5)
    {
        printf("\nMenu\n");
        printf("1: Push an item into the Stack\n");
        printf("2: Pop an item from the Stack\n");
        printf("3: Display the stack\n");
        printf("4: Empty the stack\n");
        printf("5: Exit the program\n");
        scanf("%d", &opt);
        switch(opt)
        {
            case 1: printf("Enter the value to push onto the Stack: ");
                    scanf("%d", &x);
                    push(&Stack, x);
                    break;

            case 2: if(IsStackEmpty(Stack) != 0)
                    {
                        pop(&Stack);
                        printf("\nThe top value has been popped\n");
                    }
                    else printf("\nThe stack is empty already\n");
                    break;

            case 3: if(IsStackEmpty(Stack) != 0)
                    {
                        printf("\nThe stack is: ");
                        Display(Stack);
                    }
                    else printf("\nThe stack is empty\n");
                    break;

            case 4: // Assuming the stack is not empty, we simply empty it using the pop function
                    if(IsStackEmpty(Stack) != 0)
                    {
                        // While loop while popping the stack
                        while(IsStackEmpty(Stack) != 0)
                        {
                            pop(&Stack);
                        }
                        printf("\nThe stack has been emptied.\n");
                    }
                    // Else the stack is already empty.
                    else printf("\nThe stack is already empty.\n");
                    break;
                    
            case 5: printf("Program terminated\n");
                    break;
            
            default: printf("\nInvalid option\n");
                    break;
        }
    }
    FreeTheStack(Stack);
}