#include "../headers/algorithms.h"


// heapify

void heapify(int tab[], int n, int i)
{
    int largest = i;
    int gauche = 2 * i + 1;
    int droite = 2 * i + 2;

    if (gauche < n && tab[gauche] > tab[largest])
        largest = gauche;

    if (droite < n && tab[droite] > tab[largest])
        largest = droite;

    if (largest != i)
    {
        int temp = tab[i];
        tab[i] = tab[largest];
        tab[largest] = temp;

        heapify(tab, n, largest);
    }
}

// heap sort


void heap(int tab[], int n)
{
    // Construction du max-heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(tab, n, i);

    // Extraction successive du maximum
    for (int i = n - 1; i > 0; i--)
    {
        int temp = tab[0];
        tab[0] = tab[i];
        tab[i] = temp;

        heapify(tab, i, 0);
    }
}


