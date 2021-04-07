#include <stdio.h>
#include <stdlib.h>

int isHeap_recursive(int arr[], int i, int n)
{
    //if i is outside of the array range, it means this part is a heap
    if (i >= n || n <= 0)
        return 1;

    //if there is a left child, compare with it
    if (i * 2 + 1 < n)
        if (arr[i * 2 + 1] < arr[i])
            return 0;

    //if there is a right, compare with it
    if (i * 2 + 2 < n)
        if (arr[i * 2 + 2] < arr[i])
            return 0;

    //recursively go the the left and right child and return the final result based on && operation .
    return (isHeap_recursive(arr, i * 2 + 1, n) && isHeap_recursive(arr, i * 2 + 2, n));
}

// Returns 1 if arr[i..n-1] represents a
// max-heap
int isHeap_iter(int arr[], int n)
{
    // Start from root and go till the last internal
    // node
    for (int i = 0; i <= (n - 2) / 2; i++)
    {
        // If left child is smaller, return false
        if (arr[i * 2 + 1] < arr[i] && i * 2 + 1 < n)
            return 0;

        // If right child is smaller, return false
        if (arr[i * 2 + 2] < arr[i] && i * 2 + 2 < n)
            return 0;
    }
    return 1;
}

// Driver program
int main()
{
    int n, *arr;
    printf("How many entries? ");
    scanf("%d", &n);
    arr = malloc(n * sizeof(int));

    printf("Enter %d entries: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    //int arr[6] = {12, 13, 14, 15, 110, 115}; //it is heap
    //int arr[6] = {12, 110, 14, 15, 13, 115}; // not min heap

    isHeap_recursive(arr, 0, n) ? printf("Recursive says Yes!\n") : printf("Recursive says No!\n");
    isHeap_iter(arr, n) ? printf("Iterative says Yes!\n") : printf("Iterative says No!\n");
    //same as the following
    /*if(isHeap(arr, 0, 6)
       printf("Yes")
    else
        printf("No");*/
    free(arr);

    return 0;
}
