#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include ".\benchmarks\headers\benchmarks.h"
#include ".\list_management\headers\list.h"
#include ".\gnuplot_management\headers\gnuplot.h"

int main()
{
    // srand((unsigned int)time(NULL));

    FILE *bubble_file = fopen("./results/bubble_file.txt", "w");

    if (bubble_file == NULL)
    {
        printf("Error opening bubble_file\n");
        return 1;
    }

    FILE *selection_file = fopen("./results/selection_file.txt", "w");

    if (selection_file == NULL)
    {
        printf("Error opening selection_file\n");
        return 1;
    }

    FILE *insertion_file = fopen("./results/insertion_file.txt", "w");

    if (insertion_file == NULL)
    {
        printf("Error opening insertion_file\n");
        return 1;
    }

    FILE *merge_file = fopen("./results/merge_file.txt", "w");

    if (merge_file == NULL)
    {
        printf("Error opening merge_file\n");
        return 1;
    }

    FILE *quick_file = fopen("./results/quick_file.txt", "w");

    if (quick_file == NULL)
    {
        printf("Error opening quick_file\n");
        return 1;
    }

    FILE *heap_file = fopen("./results/heap_file.txt", "w");

    if (heap_file == NULL)
    {
        printf("Error opening heap_file\n");
        return 1;
    }

    FILE *shell_file = fopen("./results/shell_file.txt", "w");

    if (shell_file == NULL)
    {
        printf("Error opening shell_file\n");
        return 1;
    }

    FILE *radix_file = fopen("./results/radix_file.txt", "w");

    if (radix_file == NULL)
    {
        printf("Error opening radix_file\n");
        return 1;
    }

    FILE *random_file = fopen("./results/random_file.txt", "w");

    if (random_file == NULL)
    {
        printf("Error opening random_file\n");
        return 1;
    }

    FILE *unique_random_file = fopen("./results/unique_random_file.txt", "w");

    if (unique_random_file == NULL)
    {
        printf("Error opening unique_random_file\n");
        return 1;
    }

    for (int list_size = 10000; list_size <= 100000; list_size += 10000)
    {

        for (int list_type = 0; list_type <= 3; list_type++)
        {
            int *arr = generate_list(list_size, list_type);
            if (arr == NULL)
            {
                fprintf(stderr, "generate_list failed\n");
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

    //====================GNUPLOT====================

    static const char *algorithm_files[] = {
        "bubble", "selection", "insertion", "merge",
        "quick", "heap", "shell", "radix"};
    static const char *algorithm_names[] = {
        "Bubble", "Selection", "Insertion", "Merge",
        "Quick", "Heap", "Shell", "Radix"};
    static const char *input_types[] = {
        "Sorted", "Random", "Unique Random", "Reverse"};
    static const char *comparison_files[] = {"random", "unique_random"};
    static const char *comparison_titles[] = {
        "Random Input - Algorithm Comparison",
        "Unique Random Input - Algorithm Comparison"};
    FILE *gnuplot = popen("gnuplot", "w");

    if (gnuplot == NULL)
    {
        fprintf(stderr, "Error opening GNUplot\n");
        return 1;
    }

    fprintf(gnuplot, "set terminal pngcairo size 1600,1000 enhanced font 'Arial,16'\n");
    fprintf(gnuplot, "set grid\n");
    fprintf(gnuplot, "set border linewidth 1.5\n");
    fprintf(gnuplot, "set tics nomirror\n");
    fprintf(gnuplot, "set pointsize 1.3\n");
    fprintf(gnuplot, "set xlabel 'List Size'\n");
    fprintf(gnuplot, "set ylabel 'Execution Time (seconds)'\n");
    fprintf(gnuplot, "set key outside right top\n");

    for (int algorithm = 0; algorithm < 8; algorithm++)
    {
        char data_file[128];
        char image_file[128];
        char chart_title[128];

        snprintf(data_file, sizeof(data_file), "./results/%s_file.txt", algorithm_files[algorithm]);
        snprintf(image_file, sizeof(image_file), "./results/images/%s.png", algorithm_files[algorithm]);
        snprintf(chart_title, sizeof(chart_title), "%s Sort - Performance", algorithm_names[algorithm]);

        if (plot_algorithm(gnuplot, chart_title, data_file, image_file,
                           4, 3, input_types, 4) != 0)
        {
            pclose(gnuplot);
            fprintf(stderr, "Error creating graph for %s sort\n", algorithm_names[algorithm]);
            return 1;
        }
    }

    for (int comparison = 0; comparison < 2; comparison++)
    {
        char data_file[128];
        char image_file[128];

        snprintf(data_file, sizeof(data_file), "./results/%s_file.txt", comparison_files[comparison]);
        snprintf(image_file, sizeof(image_file), "./results/images/%s.png", comparison_files[comparison]);

        if (plot_algorithm(gnuplot, comparison_titles[comparison], data_file, image_file,
                           8, 4, algorithm_names, 8) != 0)
        {
            pclose(gnuplot);
            fprintf(stderr, "Error creating graph for %s comparison\n", comparison_files[comparison]);
            return 1;
        }
    }

    fprintf(gnuplot, "set output\n");

    if (pclose(gnuplot) != 0)
    {
        fprintf(stderr, "GNUplot failed to generate the graphs\n");
        return 1;
    }

    return 0;
}
