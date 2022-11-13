#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// We are including time.h to use the time function to generate random numbers

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

// Main code
int main(int argc, char **argv) {
	int * a;
	int n = 10;
	Node* list;
    // We are using the time function to generate random numbers
	srand(time(NULL));

	a = genrandarr(n);
	list = genLinkedfromArr(a,n);

	printArray(a,n);
    PrintingTheList(list);
	free(a);
	freeLinkedList(list);

	return 0;
}