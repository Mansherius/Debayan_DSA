#include <stdio.h>
#include <stdlib.h>
/*
We shall use the same code as linked_list_with_user_inputs.c so that we do not need to recreate a list
To reverse a linked list - 
    The first element must now point to null and each element must point to the previous element
    This would mean a list of 1 -> 2-> 3-> 4 -> NULL
    would become 4->3->2->1->NULL
    The way to manage this would first be to take the last element of the list
    last element -> second last element
    And repeat this till we get to the first element
    
    Psuedo code:
    we create pointers prev, current and next
*/



struct nodeType
{
    int data;
    struct nodeType* next;
};

//just to make writing code simpler to understand
typedef struct nodeType Node;

// Function to print all values of a given linked list
void PrintingTheList(Node* head)
{
    Node *temp = head;
    int i = 0;
    while(temp != NULL){
        printf(i?" - %d":"%d", temp->data);
        temp = temp->next;
        i++;
    }
    printf("\n");
}

void CreatingLinkedList(Node** head, int n)
{
    //Initialising variables for user input data through vals
    int vals, i;
    i = 0; //so that we can number each of the nodes and also end the program at the right point
    //at this point: head = NULL;
    //loop runs till the user input length of list (n)
    while(i < n)
    {
        //take user input for the value.
        printf("\n What is the value in node %d : \n", i+1);
        scanf("\n%d", &vals);
        //Now the code to actually add a node
        //first we initialise a temporary node to use
        Node* temp = malloc(sizeof(Node));
        temp -> data = vals; //setting the value of temp to vals
        temp -> next = NULL; //setting the address of the pointer to NULL.
        //this implies that, unless we add another node, this node points to nothing (last node)
        if (*head == NULL) //if the address of the head node is null, (last node) then we set it to the new node
        {
            *head = temp;
        }
        else //this implies a previous node exists, in which case that node must now point to this newly created node
        {
            Node *prev = *head;
            // loop runs till the 2nd last node since lost node will be NULL
            while(prev->next != NULL)
            {
                prev = prev->next;
            }
            //previous node now points to newly created node.
            prev->next = temp;
            prev = temp;
        }
         i++; //incrementing i indicating that node was added
    }
}

//The last thing now required is a function to free the space we malloc'd for the linkedlist
//Freeing a Linked List:
void freeList(Node* head){
    Node* prev;
    while(head) {
        prev = head;
        head = head->next;
        free(prev);
    }
}

int main()
{
    Node *Linkedlist = NULL;
    //Now there are two cases to consider when considering input: positive and negative values for list length
    //Obviously we cannot have a negative length or 0 as length, so the program should restart if that is the case
    int n;
    printf("Enter length of linked list: ");
    scanf("%d", &n);
    if(n <= 0)
    {
        printf("Invalid input.\n"); //Now the loop should restart so we call main()
        main();
    }
    else
    {
        CreatingLinkedList(&Linkedlist, n);  //calling function to create the list using inputs.
        printf("The required Linked List according to your inputs is: "); //printing the Linked List out
        PrintingTheList(Linkedlist);
        freeList(Linkedlist);  //freeing the space taken by the list

    }
    
    return 0;
}