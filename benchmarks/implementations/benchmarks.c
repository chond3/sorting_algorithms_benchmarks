#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "..\headers\benchmarks.h"

#include "../../algorithms\headers\algorithms.h"
#include "../../list_management/headers/list.h"

static const char *list_type_key(int list_type)
{
    switch (list_type)
    {
    case 0: return "sorted";
    case 1: return "random_duplicates";
    case 2: return "random_unique";
    case 3: return "reverse";
    default: return "unknown";
    }
}

static const char *list_type_label(int list_type)
{
    switch (list_type)
    {
    case 0: return "Sorted";
    case 1: return "Random (duplicates allowed)";
    case 2: return "Random (unique values)";
    case 3: return "Reverse";
    default: return "Unknown";
    }
}

void benchmarks(int arr[], int list_size, int list_type, char algorithm_name[], FILE *file, FILE *random_file, FILE *unique_random_file)
{
    if (arr == NULL || algorithm_name == NULL || file == NULL || random_file == NULL || unique_random_file == NULL || list_size <= 0)
    {
        fprintf(stderr, "Error: invalid benchmark input or output pointer\n");
        exit(1);
    }

    double time_taken;
    LARGE_INTEGER frequency, start, end;
    if (!QueryPerformanceFrequency(&frequency))
    {
        fprintf(stderr, "Error: could not read performance counter frequency\n");
        exit(1);
    }

    int *copy_array = malloc(list_size * sizeof(int));
    if (copy_array == NULL)
    {
        fprintf(stderr, "Error: memory allocation failed for %s (%d elements)\n", algorithm_name, list_size);
        exit(1);
    }

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
        exit(1);
    }

    int repeat_count = algo >= 3 ? 25 : 1;
    time_taken = 0.0;

    for (int repeat = 0; repeat < repeat_count; repeat++)
    {
        copy_list(copy_array, arr, list_size);
        QueryPerformanceCounter(&start);

        switch (algo)
        {
        case 0: bubble(copy_array, list_size); break;
        case 1: selection(copy_array, list_size); break;
        case 2: insertion(copy_array, list_size); break;
        case 3: merge(copy_array, list_size); break;
        case 4: quick(copy_array, list_size); break;
        case 5: heap(copy_array, list_size); break;
        case 6: shell(copy_array, list_size); break;
        case 7: radix(copy_array, list_size); break;
        }

        QueryPerformanceCounter(&end);

        for (int i = 1; i < list_size; i++)
        {
            if (copy_array[i - 1] > copy_array[i])
            {
                fprintf(stderr, "Error: %s did not sort the list of %d elements (repeat %d)\n", algorithm_name, list_size, repeat + 1);
                free(copy_array);
                exit(1);
            }
        }

        double sample_time = (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
        if (repeat == 0 || sample_time < time_taken)
            time_taken = sample_time;
    }

    fprintf(file, "%d\t%s\t%.9f\n",
            list_size,
            list_type_key(list_type),
            time_taken);

    if (list_type == 1)
    {
        fprintf(random_file, "%d\t%s\trandom_duplicates\t%.9f\n",
                list_size, algorithm_name, time_taken);
    }
    else if (list_type == 2)
    {
        fprintf(unique_random_file, "%d\t%s\trandom_unique\t%.9f\n",
                list_size, algorithm_name, time_taken);
    }

    printf("%s\t\t%d\t%s\t%.9f\n=============================================================\n",
           algorithm_name,
           list_size,
           list_type_label(list_type),
           time_taken);

    free(copy_array);
}