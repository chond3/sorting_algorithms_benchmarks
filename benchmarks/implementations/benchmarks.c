#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "..\headers\benchmarks.h"

#include "../../algorithms\headers\algorithms.h"
#include "../../list_management/headers/list.h"

void benchmarks(int arr[], int list_size, int list_type, char algorithm_name[], FILE *file, FILE *random_file, FILE *unique_random_file)
{
    if (arr == NULL || algorithm_name == NULL || file == NULL || random_file == NULL || unique_random_file == NULL || list_size <= 0)
    {
        fprintf(stderr, "Error: invalid benchmark input or output pointer\n");
        return;
    }

    double time_taken;
    LARGE_INTEGER frequency, start, end;
    if (!QueryPerformanceFrequency(&frequency))
    {
        fprintf(stderr, "Error: could not read performance counter frequency\n");
        return;
    }

    int *copy_array = malloc(list_size * sizeof(int));
    if (copy_array == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed for %s (%d elements)\n", algorithm_name, list_size);
        return;
    }

    copy_list(copy_array, arr, list_size);

    int algo = -1 ;
    if (strcmp(algorithm_name, "Bubble") == 0)
    {
        algo = 0;
    }
    else if (strcmp(algorithm_name, "Selection") == 0)
    {
        algo = 1;
    }
    else if (strcmp(algorithm_name, "Insertion") == 0)
    {
        algo = 2;
    }
    else if (strcmp(algorithm_name, "Merge") == 0)
    {
        algo = 3;
    }
    else if (strcmp(algorithm_name, "Quick") == 0)
    {
        algo = 4;
    }
    else if (strcmp(algorithm_name, "Heap") == 0)
    {
        algo = 5;
    }
    else if (strcmp(algorithm_name, "Shell") == 0)
    {
        algo = 6;
    }
    else if (strcmp(algorithm_name, "Radix") == 0)
    {
        algo = 7;
    }

    if (algo == -1)
    {
        fprintf(stderr, "Error: unknown sorting algorithm '%s'\n", algorithm_name);
        free(copy_array);
        return;
    }

    switch (algo)
    {
    case 0:

        QueryPerformanceCounter(&start);
        bubble(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 1:

        QueryPerformanceCounter(&start);
        selection(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 2:

        QueryPerformanceCounter(&start);
        insertion(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 3:

        QueryPerformanceCounter(&start);
        merge(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 4:

        QueryPerformanceCounter(&start);
        quick(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 5:

        QueryPerformanceCounter(&start);
        heap(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 6:

        QueryPerformanceCounter(&start);
        shell(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    case 7:

        QueryPerformanceCounter(&start);
        radix(copy_array, list_size);
        QueryPerformanceCounter(&end);
        break;

    default:

        break;
    }

    for (int i = 1; i < list_size; i++)
    {
        if (copy_array[i - 1] > copy_array[i])
        {
            fprintf(stderr, "Error: %s did not sort the list of %d elements\n", algorithm_name, list_size);
            free(copy_array);
            return;
        }
    }

    time_taken = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;

    fprintf(file, "%d\t%s\t%.9f\n",
            list_size,
            list_type == 0 ? "sorted" : list_type == 1 ? "random"
                                    : list_type == 2   ? "unique_random"
                                                       : "reverse",
            time_taken);

    if (list_type == 1)
    {
        fprintf(random_file, "%d\t%s\trandom\t%.9f\n",
                list_size, algorithm_name, time_taken);
    }
    else if (list_type == 2)
    {
        fprintf(unique_random_file, "%d\t%s\tunique_random\t%.9f\n",
                list_size, algorithm_name, time_taken);
    }

    printf("%s\t\t%d\t%s\t%.9f\n=============================================================\n",
           algorithm_name,
           list_size,
           list_type == 0 ? "sorted" : list_type == 1 ? "random"
                                   : list_type == 2   ? "unique_random"
                                                      : "reverse",
           time_taken);

    free(copy_array);
}