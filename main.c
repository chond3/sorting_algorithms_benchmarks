#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include ".\benchmarks\headers\benchmarks.h"
#include ".\list_management\headers\list.h"
#include ".\gnuplot_management\headers\gnuplot.h"

int main()
{
    // srand((unsigned int)time(NULL));
    srand(42);
    
    FILE *bubble_file = fopen("./results/bubble_file.txt", "w");

    if (bubble_file == NULL)
    {
        fprintf(stderr, "Error opening bubble_file\n");
        return 1;
    }

    FILE *selection_file = fopen("./results/selection_file.txt", "w");

    if (selection_file == NULL)
    {
        fprintf(stderr, "Error opening selection_file\n");
        return 1;
    }

    FILE *insertion_file = fopen("./results/insertion_file.txt", "w");

    if (insertion_file == NULL)
    {
        fprintf(stderr, "Error opening insertion_file\n");
        return 1;
    }

    FILE *merge_file = fopen("./results/merge_file.txt", "w");

    if (merge_file == NULL)
    {
        fprintf(stderr, "Error opening merge_file\n");
        return 1;
    }

    FILE *quick_file = fopen("./results/quick_file.txt", "w");

    if (quick_file == NULL)
    {
        fprintf(stderr, "Error opening quick_file\n");
        return 1;
    }

    FILE *heap_file = fopen("./results/heap_file.txt", "w");

    if (heap_file == NULL)
    {
        fprintf(stderr, "Error opening heap_file\n");
        return 1;
    }

    FILE *shell_file = fopen("./results/shell_file.txt", "w");

    if (shell_file == NULL)
    {
        fprintf(stderr, "Error opening shell_file\n");
        return 1;
    }

    FILE *radix_file = fopen("./results/radix_file.txt", "w");

    if (radix_file == NULL)
    {
        fprintf(stderr, "Error opening radix_file\n");
        return 1;
    }

    FILE *random_file = fopen("./results/random_file.txt", "w");

    if (random_file == NULL)
    {
        fprintf(stderr, "Error opening random_file\n");
        return 1;
    }

    FILE *unique_random_file = fopen("./results/unique_random_file.txt", "w");

    if (unique_random_file == NULL)
    {
        fprintf(stderr, "Error opening unique_random_file\n");
        return 1;
    }

    for (int list_size =25000; list_size <= 600000; list_size += 25000)
    {

        for (int list_type = 0; list_type <= 3; list_type++)
        {
            int *arr = generate_list(list_size, list_type);
            if (arr == NULL)
            {
                fprintf(stderr, "Error: failed to generate list (size=%d, type=%d)\n", list_size, list_type);
                return 1;
            }

            benchmarks(arr, list_size, list_type, "Bubble", bubble_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Selection", selection_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Insertion", insertion_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Merge", merge_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Quick", quick_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Heap", heap_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Shell", shell_file, random_file, unique_random_file);
            benchmarks(arr, list_size, list_type, "Radix", radix_file, random_file, unique_random_file);

            free(arr);
        }
    }

    fclose(bubble_file);
    fclose(selection_file);
    fclose(insertion_file);
    fclose(merge_file);
    fclose(quick_file);
    fclose(heap_file);
    fclose(shell_file);
    fclose(radix_file);
    fclose(random_file);
    fclose(unique_random_file);

    // GNUPLOT

    plot();

    return 0;
}