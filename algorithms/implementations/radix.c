#include <stdlib.h>
#include <stdio.h>
#include "../headers/algorithms.h"

void radix(int arr[], int n)
{
    if (n <= 1)
        return;

    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int *output = malloc(n * sizeof(int));
    if (output == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed in radix for %d elements\n", n);
        return;
    }

    for (long long exp = 1; max / exp > 0; exp *= 10)
    {
        int count[10] = {0};

        for (int i = 0; i < n; i++)
            count[(int)((arr[i] / exp) % 10)]++;

        for (int i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (int i = n - 1; i >= 0; i--)
        {
            int digit = (int)((arr[i] / exp) % 10);
            output[count[digit] - 1] = arr[i];
            count[digit]--;
        }

        for (int i = 0; i < n; i++)
            arr[i] = output[i];
    }

    free(output);
}