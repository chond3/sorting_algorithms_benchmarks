#include "../headers/algorithms.h"

// swap fuction

void swap(int *a, int *b){
 int temp = *a;
 *a = *b;
 *b = temp;}

 // pivot median

 int medianOfThree(int tab[], int gauche, int droite)
{
    int milieu = gauche + (droite - gauche) / 2;

    if (tab[gauche] > tab[milieu])
        swap(&tab[gauche], &tab[milieu]);

    if (tab[gauche] > tab[droite])
        swap(&tab[gauche], &tab[droite]);

    if (tab[milieu] > tab[droite])
        swap(&tab[milieu], &tab[droite]);

    return milieu;
}

// hoare partition

int partitionHoare(int tab[], int gauche, int droite)
{
    int indicePivot = medianOfThree(tab, gauche, droite);
    int pivot = tab[indicePivot];

    int i = gauche - 1;
    int j = droite + 1;

    while (1)
    {
        do
        {
            i++;
        } while (tab[i] < pivot);

        do
        {
            j--;
        } while (tab[j] > pivot);

        if (i >= j)
            return j;

        swap(&tab[i], &tab[j]);
    }
}

// quick implementation

void quickSort(int tab[], int gauche, int droite)
{
    if (gauche < droite)
    {
        int p = partitionHoare(tab, gauche, droite);

        quickSort(tab, gauche, p);
        quickSort(tab, p + 1, droite);
    }
}

void quick(int arr[], int n)
{
    quickSort(arr, 0, n - 1);
}