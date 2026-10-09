#include <stdlib.h>
#include "../headers/list.h"

// rand() on Windows only gives 15 bits; combine two calls to get 30 bits
static int rand30(void)
{
    return ((rand() & 0x7FFF) << 15) | (rand() & 0x7FFF);
}

int *generate_list(int size, int type)
{
    if (size <= 0)
        return NULL;

    int *arr = malloc(sizeof(int) * size);
    if (arr == NULL)
        return NULL;

    switch (type)
    {
    case 0: // Sorted
        for (int i = 0; i < size; i++)
            arr[i] = i;
        break;

    case 1: // Random
        for (int i = 0; i < size; i++)
            arr[i] = rand30() % 1000000;
        break;

    case 2: // Unique Random
        for (int i = 0; i < size; i++)
            arr[i] = i;

        for (int i = size - 1; i > 0; i--)
        {
            int j = rand30() % (i + 1);
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        break;

    case 3: // Reverse
        for (int i = 0; i < size; i++)
            arr[i] = size - 1 - i;
        break;

    default:
        free(arr);
        return NULL;
    }

    return arr;
}