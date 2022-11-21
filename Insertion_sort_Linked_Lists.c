#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// We are including time.h to use the time function to generate random numbers

// Simply updating code from array_linked_lists.c and Selection_sort_Linked_Lists.c
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

// Now lets us write the insertion sort algorithm for the linked list
void InsertionSort(Node* head)
{
    Node *i = head;
    Node *j, *key;
    int temp;
    while (i->next != NULL)
    {
        j = i->next; // Pointer to the next node
        key = i; // Key or 'comp' (from insertion_sort_arrays.c)
        while (j != NULL) // Going through the Linked list
        {
            // if data at j is less than data at key
            if (j->data < key->data)
            {
                // Swap data to create the ordered list till this point
                temp = j->data;
                j->data = key->data;
                key->data = temp;
            }
            // Going to the next node
            j = j->next;
        }
        i = i->next;
    }
}


// Main code
int main(int argc, char **argv) {
	int * a;
    int n;

    // Taking the input from the user
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);

	Node* list;
    // We are using the time function to generate random numbers
	srand(time(NULL));

	a = genrandarr(n);
	list = genLinkedfromArr(a,n);

    printf("Your array is: \n");
	printArray(a,n);
    PrintingTheList(list);

    printf("Your sorted array is: \n");
    InsertionSort(list);
    PrintingTheList(list);

	free(a);
	freeLinkedList(list);

	return 0;
}