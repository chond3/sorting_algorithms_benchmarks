#include <stdio.h>
#include "..\headers\gnuplot.h"

void plot()
{
    // GNUPLOT

    FILE *gp = popen("gnuplot", "w");
    if (gp == NULL)
    {
        fprintf(stderr, "Error opening GNUplot\n");
        return 1;
    }

    fprintf(gp, "set terminal pngcairo size 1600,1000 enhanced font 'Arial,16'\n");
    fprintf(gp, "set grid\n");
    fprintf(gp, "set xlabel 'List Size'\n");
    fprintf(gp, "set ylabel 'Execution Time (seconds)'\n");
    fprintf(gp, "set key outside right top\n");

    // fprintf(gp, "set logscale y\n"); 

    plot_algo(gp, "Bubble", "bubble");
    plot_algo(gp, "Selection", "selection");
    plot_algo(gp, "Insertion", "insertion");
    plot_algo(gp, "Merge", "merge");
    plot_algo(gp, "Quick", "quick");
    plot_algo(gp, "Heap", "heap");
    plot_algo(gp, "Shell", "shell");
    plot_algo(gp, "Radix", "radix");

    plot_compare(gp, "random", "Random Input (duplicates allowed) - Algorithm Comparison");
    plot_compare(gp, "unique_random", "Random Input (unique values) - Algorithm Comparison");

    fprintf(gp, "set output\n");
    pclose(gp);

}