#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// We will bring in the swap function from the previous programs as well as gen and print functions
// Function to swap two numbers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

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

/*
    Quicksort for both arrays and linked lists

    For arrays:
    1. We will use the first element as the pivot
    2. We create functions to partition the array and quicksort the array
    3. And we also take the first index of the array as the WALL
    4. Now we partition the array and swap the elements
    5. We then recursively call the quicksort function on the left and right partitions
*/

// Partition function for arrays
int Partition(int * a, int start, int stop)
{
    int pivot = a[start];
    int wall = start;
    for (int scout = start + 1; scout <= stop; scout++)
    {
        if (a[scout] < pivot)
        {
            wall++;
            swap(&a[scout], &a[wall]);
        }
    }
    swap(&a[start], &a[wall]);

    // Now we return the index/ position of the pivot
    return wall;
}

// Quicksort function for arrays
// Taking an array L and sort everything between start and stop
void Quicksort(int * L, int start, int stop)
{
    if (start < stop)
    {
        int pivot = Partition(L, start, stop);
        Quicksort(L, start, pivot - 1);
        Quicksort(L, pivot + 1, stop);
    }
}


// Main code
int main(int argc, char **argv) {
	int * a;
	int n;
    printf("How many elements should the randomly generated array have?: \n");
    scanf("%d", &n);
	Node* list;
    // We are using the time function to generate random numbers
	srand(time(NULL));

	a = genrandarr(n);
	list = genLinkedfromArr(a,n);

    printf("The randomly generated array is: \n");
	printArray(a,n);
    printf("The randomly generated linked list is: \n");
    PrintingTheList(list);

    printf("The sorted array is: \n");
    Quicksort(a, 0, n-1);
    printArray(a,n);
	free(a);
	freeLinkedList(list);

	return 0;
}
