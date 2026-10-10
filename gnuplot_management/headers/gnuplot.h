#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <stdio.h>

void plot_algo(FILE *gp, const char *name, const char *file);
void plot_compare(FILE *gp, const char *file, const char *title);
void plot();

#endif