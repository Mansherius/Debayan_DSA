// Code to chunk reverse a user inputted Linked List in C
#include <stdio.h>
#include <stdlib.h>

// Let the code for generating a linked list be below and then we can use it to chunk reverse it
struct nodeType
{
    int data;
    struct nodeType* next;
};

//just to make writing code simpler to understand
typedef struct nodeType Node;

// Function to print all values of a given linked list
void PrintingTheList(Node* head) {
    Node *temp = head;
    int i = 0;
    while(temp != NULL){
        printf(i?" -> %d":"%d", temp->data);
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
        temp -> data = vals; //setting the value of temp to data
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

//Now we can use the above Linked List to chunk reverse it.
// The above linked list is stored at &Linkedlist

Node* chunkrev(Node **head, int k)
{
    /*
    psuedo code:
    1. reverse the first k elements of the linked list
    2. add the reversed linked list to the new linked list
    3. repeat steps 2 and 3 until you reach the last node

    In more detail:
    First go about reversing the list like we did for reversing a linked list with one change -
    Now we also add a counter to measure if we cross the chunk size.
    When we reach the chunk size, then instead of the program reversing, it should simply jump to the 
    next Node. Then we repeat the chunk reverse again.
    we create pointers prev, current and next
    Now we traverse the list and start pointing the nodes to the previous node instead of the next node.
    The last node must now become the head
    First the prev will point to null and current points to next
    Then we create temp that points to next and make current point to prev
    prev becomes current
    current becomes next
    and temp gets replaced to restart this till we reach a value of  i>=k
    Then we jump to the next node without change and repeat the process till we get to current = NULL
    */
    if (!*(head))
    {
        return NULL;
    }

    Node *prev, *curr, *temp;
    prev = NULL;
    curr = (*head);
    int i = 0;
    while(curr != NULL && i < k)
    {
        temp = curr -> next;
        curr -> next = prev;
        prev = curr;
        curr = temp;
        i++;
    }
    // Now to check if the next chunk exists
    if(temp != NULL)
    {
        // This implies that the next chunk exists, so we must now point the head to the next chunk
        // Now we must call the function again to reverse the next chunk
        (*head) -> next = chunkrev(&temp, k);
    }
    // Now we must point the head to the previous node
    return prev;
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
    Node *ReversedLinklist = NULL;
    //Now there are two cases to consider when considering input: positive and negative values for list length
    //Obviously we cannot have a negative length or 0 as length, so the program should restart if that is the case
    int n;
    int k;
    printf("Enter length of linked list: ");
    scanf("%d", &n);
    printf("Enter the chunk to reverse by: ");
    scanf("%d", &k);
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
        printf("The chunk reversed Linked List is: ");
        ReversedLinklist = chunkrev(&Linkedlist, k);
        PrintingTheList(ReversedLinklist);
        freeList(Linkedlist);  //freeing the space taken by the list
    }
    
    return 0;
}