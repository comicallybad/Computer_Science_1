#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "leak_detector_c.h"

int myX;
int myY;

typedef struct coords
{
    int x;
    int y;
} coords;

void ReadData(coords **monsterCoords, coords **searchCoords, int *n, int *s, int *t);
int compareTo(coords *ptrPt1, coords *ptrPt2);
void insertionSort(coords arr[], int n); //Best case is: O(n), Avg: O(n^2), Worst : O(n^2)
void merge(coords arr[], int l, int m, int r);
void mergeSort(coords arr[], int l, int r, int t); //Best case is: O(nlogn), Avg: O(nlogn), Worst : O(nlogn)
void free_memory(coords arr[], coords arr2[]);
void sort(coords arr[], int n, int t);
void search(coords arr[], coords search[], int n, int s, FILE *ofp);
int binarySearch(coords arr[], int l, int r, coords search);

int main(void)
{
    atexit(report_mem_leak);
    FILE *ofp = fopen("out.txt", "w");

    coords *monsterCoords, *searchCoords;
    int n, s, t;

    ReadData(&monsterCoords, &searchCoords, &n, &s, &t);

    mergeSort(monsterCoords, 0, n - 1, t);
    // insertionSort(monsterCoords, n);

    for (int i = 0; i < n; i++)
    {
        printf("%d %d\n", monsterCoords[i].x, monsterCoords[i].y);
        fprintf(ofp, "%d %d\n", monsterCoords[i].x, monsterCoords[i].y);
    }

    search(monsterCoords, searchCoords, n, s, ofp);

    free_memory(monsterCoords, searchCoords);

    return 0;
}

void ReadData(coords **monsterCoords, coords **searchCoords, int *n, int *s, int *t)
{
    FILE *ifp = fopen("in.txt", "r");

    fscanf(ifp, "%d %d %d %d %d", &myX, &myY, n, s, t);

    *monsterCoords = malloc(sizeof(coords) * (*n));
    *searchCoords = malloc(sizeof(coords) * (*s));

    for (int i = 0; i < (*n); i++)
        fscanf(ifp, "%d %d", &(*monsterCoords)[i].x, &(*monsterCoords)[i].y);

    for (int i = 0; i < (*s); i++)
        fscanf(ifp, "%d %d", &(*searchCoords)[i].x, &(*searchCoords)[i].y);

    fclose(ifp);
}

void free_memory(coords arr[], coords arr2[])
{
    free(arr);
    free(arr2);
}

void sort(coords arr[], int n, int t)
{
}

void search(coords arr[], coords search[], int n, int s, FILE *ofp)
{
    for (int i = 0; i < s; i++)
    {
        int location = binarySearch(arr, 0, n - 1, search[i]);
        if (location < 0)
        {
            printf("%d %d not found\n", search[i].x, search[i].y);
            fprintf(ofp, "%d %d not found\n", search[i].x, search[i].y);
        }
        else
        {
            printf("%d %d found at rank %d\n", search[i].x, search[i].y, location + 1);
            fprintf(ofp, "%d %d found at rank %d\n", search[i].x, search[i].y, location + 1);
        }
    }
}

int compareTo(coords *ptrPt1, coords *ptrPt2)
{
    int distanceOne = sqrt(pow((ptrPt1->x - myX), 2) + pow((ptrPt1->y - myY), 2));
    int distanceTwo = sqrt(pow((ptrPt2->x - myX), 2) + pow((ptrPt2->y - myY), 2));

    if (distanceOne < distanceTwo)
        return -1;
    if (distanceOne == distanceTwo)
    {
        if (ptrPt1->x < ptrPt2->x)
            return -1;
        if (ptrPt1->x > ptrPt2->x)
            return 1;
        if (ptrPt1->x == ptrPt2->x)
        {
            if (ptrPt1->y < ptrPt2->y)
                return -1;
            if (ptrPt1->y > ptrPt2->y)
                return 1;
        }
        if (ptrPt1->x == ptrPt2->x && ptrPt1->y == ptrPt2->y)
            return 0;
    }
    if (distanceOne > distanceTwo)
        return 1;
}

void insertionSort(coords arr[], int n)
{
    coords item;
    int j;
    for (int i = 1; i < n; i++)
    {
        item = arr[i];
        /* Move elements of arr[0..i-1], that are
     greater than key, to one position ahead
     of their current position */
        for (j = i - 1; j >= 0; j--)
        {
            if (compareTo(&arr[j], &item) == 1)
                arr[j + 1] = arr[j];
            else
                break;
        }
        arr[j + 1] = item;
    }
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(coords arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    coords *L = (coords *)malloc(n1 * sizeof(coords));
    coords *R = (coords *)malloc(n2 * sizeof(coords));

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (compareTo(&L[i], &R[j]) == -1 || compareTo(&L[i], &R[j]) == 0)
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    free(L);
    free(R);
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(coords arr[], int l, int r, int t)
{
    if (l < t)
    {
        // get the mid point
        int m = (l + r) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m, t);
        mergeSort(arr, m + 1, r, t);

        merge(arr, l, m, r);
    }
}

// A recursive binary search function. It returns
// location of x in given array arr[l..r] is present,
// otherwise -1
int binarySearch(coords arr[], int l, int r, coords search)
{
    if (r >= l)
    {
        int mid = l + (r - l) / 2;

        // If the element is present at the middle
        // itself
        if (compareTo(&arr[mid], &search) == 0)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (compareTo(&arr[mid], &search) == 1)
            return binarySearch(arr, l, mid - 1, search);

        // Else the element can only be present
        // in right subarray
        return binarySearch(arr, mid + 1, r, search);
    }

    // We reach here when element is not
    // present in array
    return -1;
}
