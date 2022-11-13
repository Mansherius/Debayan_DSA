// C program for insertion sort
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

// Code to create a random array of size n
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

/*
    Psuedo code:
    We start with the second element of the array and compare it with the previous element.
    Here the second element is the comp (as in comparison element)
    If the comp is smaller than the previous element, we swap them.
    Now the first two elements are sorted.
    Next we take the third element and compare it with the second element.
    Now the third element is our comp.
    We compare the key with all the elements before it and swap them if they are greater than the comp.
    Similarly, the comp always gets incremented by one.
    We continue this process until the array is sorted.
*/

void InsertionSort(int * a, int n)
{
    int i, j, comp;
    for (i = 1; i < n; i++)
    {
        comp = a[i]; //The value of comp is a[i]
        j = i - 1; // j is the index of the previous element
        while (j >= 0 && a[j] > comp) //starts from first element and compares it with the comp
        {
            a[j + 1] = a[j]; //if the previous element is greater than the comp, we swap them
            j = j - 1; //decrementing j so that we compare to predecessors as well
        }
        a[j + 1] = comp; // This sets the the value of the next element to comp/a[i], thus completing the swap
    }

}

int main(int argc, char** argv)
{
    int * a;
    int n = 10;
    // We are using the time function to generate random numbers
    srand(time(NULL));

    a = genrandarr(n);
    printf("The random array is: ");
    printarr(a, n);
    InsertionSort(a, n);
    printf("The sorted array is: ");
    printarr(a, n);
    free(a);

    return 0;
}