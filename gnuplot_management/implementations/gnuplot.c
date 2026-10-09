#include "../headers/gnuplot.h"

// One graph per algorithm, split by input type.
void plot_algo(FILE *gp, const char *name, const char *file)
{
    fprintf(gp, "set title '%s Sort - Performance'\n", name);
    fprintf(gp, "set output './results/images/%s.png'\n", file);
    fprintf(gp, "plot './results/%s_file.txt' every 4::0 using 1:3 with linespoints lw 3 pt 7 title 'Sorted', "
                "'' every 4::1 using 1:3 with linespoints lw 3 pt 7 title 'Random (duplicates allowed)', "
                "'' every 4::2 using 1:3 with linespoints lw 3 pt 7 title 'Random (unique values)', "
                "'' every 4::3 using 1:3 with linespoints lw 3 pt 7 title 'Reverse'\n", file);
}

// One graph comparing algorithms for a single random input type.
void plot_compare(FILE *gp, const char *file, const char *title)
{
    fprintf(gp, "set title '%s'\n", title);
    fprintf(gp, "set output './results/images/%s.png'\n", file);
    fprintf(gp, "plot './results/%s_file.txt' every 8::0 using 1:4 with linespoints lw 3 pt 7 title 'Bubble', "
                "'' every 8::1 using 1:4 with linespoints lw 3 pt 7 title 'Selection', "
                "'' every 8::2 using 1:4 with linespoints lw 3 pt 7 title 'Insertion', "
                "'' every 8::3 using 1:4 with linespoints lw 3 pt 7 title 'Merge', "
                "'' every 8::4 using 1:4 with linespoints lw 3 pt 7 title 'Quick', "
                "'' every 8::5 using 1:4 with linespoints lw 3 pt 7 title 'Heap', "
                "'' every 8::6 using 1:4 with linespoints lw 3 pt 7 title 'Shell', "
                "'' every 8::7 using 1:4 with linespoints lw 3 pt 7 title 'Radix'\n", file);
}