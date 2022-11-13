#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// First let us generate a random array of size n(user input)

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

// And also the code to print it
void printarr(int * a, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");
}

// We require a swap function to use in the program
void swap(int *x, int *y) {
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// Now let us write the insertion sort algorithm
void insertion_sort(int *a)
{

}