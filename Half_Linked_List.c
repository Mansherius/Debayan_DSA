#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// We are including time.h to use the time function to generate random numbers

//We are copying the code from the previous file array_linked_lists.c to use 

/*=======================================================================================*/
// First we define the structure of the node
struct nodeType
{
    int data;
    struct nodeType* next;
};

typedef struct nodeType Node;

// Let us now generate a random array for the linked list
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

// To generate a Linked list from the above array
Node* genLinkedfromArr(int * a, int n) {
	int i;
    // Initialising the head and temp nodes
	Node* head = NULL;
	Node* temp = NULL;

	if(n>0)
    {
		head = malloc( sizeof(Node) );
		head->data = a[0];
		head->next = NULL;
		temp = head;
	}


	for(i=1; i<n; i++)
    {
		temp->next = malloc( sizeof(Node) );
		temp = temp->next;
		temp->data = a[i];
		temp->next = NULL;
	}

	return head;
}

// Freeing the space malloc'd for the linked list
void freeLinkedList(Node* head) {
	Node* prev;
	while(head) {
		prev = head;
		head = head->next;
		free(prev);
	}
}

// To print out the array
void printArray(int * a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// To print out the linked list
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

/*=======================================================================================*/

/*
Problem Statement:
To print out the first half of a linked list without knowing the length of the linked list

To do this, we can employ the following method:
1. We will use two pointers, one will move twice as fast as the other
2. When the faster pointer reaches the end of the linked list,
the slower pointer will be at the middle of the linked list
3. We will then print out the linked list from the head to the slower pointer
*/

// To print out the first half of the linked list
void printFirstHalf(Node* head) {
    Node *slow = head;
    Node *fast = head;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }

    Node *temp = head;
    int i = 0;
    while(temp != slow){
        printf(i?" -> %d":"%d", temp->data);
        temp = temp->next;
        i++;
    }
    printf("\n");
}


// Main code
int main(int argc, char **argv) {
	int * a;
    int n;
    printf("Enter length of linked list: ");
    scanf("%d", &n);
	Node* list;
    // We are using the time function to generate random numbers
	srand(time(NULL));

	a = genrandarr(n);
	list = genLinkedfromArr(a,n);

	printArray(a,n);
    PrintingTheList(list);
    printFirstHalf(list);
	free(a);
	freeLinkedList(list);

	return 0;
}