#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

// Code to create a queue using a linked list
// Defining a struct node to be used for queues

struct node
{
    int data;
    struct node* next;
};
typedef struct node Node;

struct queue{
    Node* head;
    Node* tail;
};
// A queue has both a head node and a tail node

typedef struct queue Queue;

// First we define a function to initialise a queue and return a pointer to it.
Queue* MakeQueue(Queue* q)
{
    q->head = NULL;
    q->tail = NULL;
    return q;
}

// Now the function to add values to the queue (AddToQueue)
void AddToQueue(Queue* q, int value)
{
    // First we create space for the new node to be added to the queue
    Node* temp = malloc(sizeof(Node));
    // Now we set the value of the new node to the value passed to the function
    temp->data = value;
    // Now we set the next pointer of the new node to NULL as it is going to be the new tail
    temp->next = NULL;

    // If the queue is not empty, we have to make the current tail point to the new tail

    if (q->tail) { q->tail->next = temp; }
    q->tail = temp;

    // else we have to make the head point to the new tail as well
    if(q->head == NULL) {q->head = temp;} 
}

/**
 * ! Function to remove items from the queue
 * @param q is the passed q we have to dequeue.
 * * There is no @param val here since we are removing a node and returning the value at that node (return type int).
 * ? Need to figure out a way to store negative integers and still throw an error if the queue is empty
*/

// Now the function to remove values from the queue
int RemoveFromQueue(Queue* q)
{
    int value; // Used to store the value that has been removed.
    // If the queue is empty then obviously we cannot remove any values
    // So, we return -1 to indicate a failure.
    if(q->head == NULL) {return -1;}
    
    // Now we have to remove the head node from the queue
    // First we store the value at the head node in a variable
    value = q->head->data;
    // Now we 'remove' the head.

    // head now points to the next node in the queue
    q->head = q->head->next;
    // If this is now an empty queue after removing the head then we have to reset the head and tail to NULL;
    if(q->head == NULL) {q->tail = NULL;}

    return value; //returning the value that was removed from the queue
}

// Now we write a test to check if our queue is empty or not
int IsQueueEmpty(Queue* q)
{
    if (q->head == NULL && q->tail == NULL)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// Now we write a the helper functions

// Let us now generate a random array for the linked list
// Code from array_linked_list.c
int * genrandarr(int n)
{
    int * arr = malloc(n * sizeof(int));
    if(arr)
    {
        for (int i = 0; i < n; i++)
            {
                arr[i] = rand() % 1000;
            }
    }
    return arr;
}


// And to generate a queue from an array
Queue* genQueuefromArr(int* a, int n){
    Queue* q = malloc(sizeof(Queue));
    q = MakeQueue(q);
    if(n > 0)
    {
        for (int i = 0; i < n; i++)
        {
            AddToQueue(q, a[i]);
        }
    }
    return q;
}

// And to print an array (code from array_linked_list.c)
void printArray(int * a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf(i?" [%d]":"[%d]", a[i]);
    }
    printf("\n");
}

/**
 * ! Function to print a queue
 * @param q is the queue that is to be printed (we have to dequeue to print)
*/

// Now to print a queue
void PrintingtheQueue(Queue* q)
{
    int value;
    Queue* temp = q;
    while(temp->head)
    {
        value = RemoveFromQueue(temp);
        printf("-%d-", value);
    }
}

int main(int argc, char** argv)
{
    int n;
    srand(time(NULL));
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    int *a = genrandarr(n);
    // Printing the array to show the values
    printf("\nYour generated array is: ");
    printArray(a, n);

    // Now we generate a queue from the array
    Queue* q = genQueuefromArr(a, n);
    // dequeueing values by printing to test
    printf("\nYour generated queue (by removing the values from the queue) is: ");
    PrintingtheQueue(q);
    free(q);
    return 0;
}