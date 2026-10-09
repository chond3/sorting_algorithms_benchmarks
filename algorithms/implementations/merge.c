#include <stdlib.h>
#include <stdio.h>
#include "../headers/algorithms.h"

static void split_and_merge(int arr[], int copy[], int start, int end)
{
    if (start >= end)
        return;

    int center = start + (end - start) / 2;
    split_and_merge(arr, copy, start, center);
    split_and_merge(arr, copy, center + 1, end);

    int index = 0;
    int i = start, ii = center + 1;

    while (i <= center && ii <= end)
        copy[index++] = (arr[i] <= arr[ii]) ? arr[i++] : arr[ii++];

    while (i <= center)
        copy[index++] = arr[i++];

    while (ii <= end)
        copy[index++] = arr[ii++];

    for (int k = 0; k < index; k++)
        arr[start + k] = copy[k];
}

void merge(int arr[], int n)
{
    if (n <= 1)
        return;

    int *copy = malloc(n * sizeof(int));
    if (copy == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed in merge for %d elements\n", n);
        return;
    }

    split_and_merge(arr, copy, 0, n - 1);
    free(copy);
}