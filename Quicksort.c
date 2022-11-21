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
    Quicksort_arrays for both arrays and linked lists

    For arrays:
    1. We will use the first element as the pivot
    2. We create functions to partition the array and quicksort the array
    3. And we also take the first index of the array as the WALL
    4. Now we partition the array and swap the elements
    5. We then recursively call the quicksort function on the left and right partitions
*/

// Partition function for arrays
int Partition_arrays(int * a, int start, int stop)
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

// Quicksort_arrays function for arrays
// Taking an array L and sort everything between start and stop
void Quicksort_arrays(int * L, int start, int stop)
{
    if (start < stop)
    {
        int pivot = Partition_arrays(L, start, stop);
        Quicksort_arrays(L, start, pivot - 1);
        Quicksort_arrays(L, pivot + 1, stop);
    }
}

/*
    Obviously we cannot use the same partition function for linked lists nor can we use the swap function as it is
    So we will have to make some changes to the partition function
    We will also need to find last node of the linked list

    For linked lists:

*/

// Finding last node of linked list
Node* last_node(Node* head)
{
    Node* temp = head;
    while (temp != NULL && temp->next != NULL) {
        temp = temp->next;
    }
    return temp;
}

// Partition function for linked lists
Node* Partition_linked(Node* first, Node* last)
{
    // Get first node of given linked list which will actually be the head of the linked list
    Node* pivot = first;
    Node* front = first;
    int temp = 0;

    //The pivot is the first node of the linked list and the loop runs till the last node of the linked list
    while (front != NULL && front != last)
    {
        // If data in front is greater than the data in the end
        if (front->data < last->data)
        {
            pivot = first;
 
            // Swapping the data of the nodes
            temp = first->data;
            first->data = front->data;
            front->data = temp;

            first = first->next;
        }
        front = front->next;
    }
    // Same as the swap function for wall and start from the array partition function
    temp = first->data;
    first->data = last->data;
    last->data = temp;

    return pivot;
}
 
// Performing quick sort in  the given linked list
void Quicksort_linked(Node* first, Node* last)
{
    // End condition for recursion
    if (first == last)
    {
        return;
    }
    Node* pivot = Partition_linked(first, last);
 
    if (pivot != NULL && pivot->next != NULL)
    {
        // Recursively calling the quicksort function on the left partition
        Quicksort_linked(pivot->next, last);
    }
 
    if (pivot != NULL && first != pivot)
    {
        Quicksort_linked(first, pivot);
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
    Quicksort_arrays(a, 0, n-1);
    printArray(a,n);

    printf("The sorted linked list is: \n");
    Quicksort_linked(list, last_node(list));
    PrintingTheList(list);

	free(a);
	freeLinkedList(list);

	return 0;
}


/*
    Some things to keep in mind:
    We can also simply Take a linked list and convert to an array
    Then Quicksort the array and generate a linked list from the array

    However, this is not the most efficient way to do it
*/