#include "../headers/algorithms.h"

void selection(int tab[], int n)
{
    int min;
    int temp;

    for (int i = 0; i < n - 1; i++)
    {
        min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (tab[j] < tab[min])
            {
                min = j;
            }
        }

        temp = tab[i];
        tab[i] = tab[min];
        tab[min] = temp;
    }
}