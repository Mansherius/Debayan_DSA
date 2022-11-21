#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// Function to swap two numbers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to generate a random array (taken from previous code)
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

// To print out the array
void printArray(int * a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

/*
    Logic for Heaps (max heap):
    1. The root node is the largest element in the heap
    2. The left child of the root node is the largest element in the left subtree
    3. The right child of the root node is the largest element in the right subtree
    4. The left and right subtrees are also max heaps
    5. A heap is an array (easier to implement and understand) with the following properties:
        a. The root node is at index 0
        b. The left child of the node at index i is at index 2i+1
        c. The right child of the node at index i is at index 2i+2
        d. The parent of the node at index i is at index (i-1)/2
    
    We shall use the above information when coding up heapify below
*/

// Function to heapify the tree where n is the size of the heap
void heapify(int arr[], int N, int i)
{
    // To heapify, means to ensure that the heap property is maintained in every trio of elements (Parent and its two children)
    
    // Find largest among root, left child and right child
    // Initializing largest as root
    // This need not be true, we simply use it as the baseline assumption
    int largest = i;
 
    // left child given by 2*i + 1
    // Right child given by 2*i + 2
    int left = 2 * i + 1;
    int right = 2 * i + 2;
 
    // Comparisons to find the actual largest
    if (left < N && arr[left] > arr[largest])
        largest = left; // Implies left child is larger than root
    // If left child is larger than root

    if (right < N && arr[right] > arr[largest])
        largest = right; // Implies right child is larger than root
    
    // So we swap their positions so that largest is the parent node and continue heapifying as required
    
    // If largest is not root(parent)
    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, N, largest);
    }
}
 
// Heap sort function
void HeapSort(int arr[], int N)
{
    // Build heap (rearrange array)
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);
 
    // One by one extract an element from heap
    for (int i = N - 1; i >= 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i]);
 
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}
 
// Driver's code
int main(int argc, char **argv)
{
    int * a;
    int n;
    printf("This is a program to sort an array using heap sort\n");
    printf("How many elements do you want in the random array?\n");
    scanf("%d", &n);

    srand(time(NULL));
    a = genrandarr(n);
    //int arr[] = { 12, 11, 13, 5, 6, 7 };
    //int N = sizeof(arr) / sizeof(arr[0]);
    printf("The random array is:\n");
    printArray(a, n);
    // Function call
HeapSort(a, n);
    printf("Sorted array is\n");
    printArray(a, n);
}

