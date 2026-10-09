#include "../headers/algorithms.h"

void bubble(int tab[], int n)
{
    int temp;
    int swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < n - 1 - i; j++)
        {
            if (tab[j] > tab[j + 1])
            {
                temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;

                swapped = 1;
            }
        }

        if (swapped == 0)
        {
            break;
        }
    }
}