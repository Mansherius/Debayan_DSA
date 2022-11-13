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
void swap(int *x, int *y)
{
	int temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

// We also require to find the minimum element in the array
int FindMinElement(int * a, int i, int n)
{
    int min = i;
    for (int j = i+1; j < n; j++)
    {
        if (a[j] < a[min])
        {
            min = j;
        }
    }
    return min;
}

// Now let us write the insertion sort algorithm
void selection_sort(int * a, int n)
{
	int i, mini;

	for(i=0; i<n; i++)
    {
		mini = FindMinElement(a, i, n);
		swap( &a[mini], &a[i] ); // swap the values present at the addresses
	}
}

int main()
{
    int n;
    srand(time(NULL));
    printf("Enter the size of the array: ");
    scanf("%d", &n);
    int * a = genrandarr(n);
    printf("The array is: ");
    printarr(a, n);
    selection_sort(a, n);
    printf("The sorted array is: ");
    printarr(a, n);
    free(a);
    return 0;
}