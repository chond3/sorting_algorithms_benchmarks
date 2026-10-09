#ifndef GNUPLOT_H
#define GNUPLOT_H

#include <stdio.h>

int plot_algorithm(FILE *gnuplot,
				   const char *plot_title,
				   const char *data_file,
				   const char *image_file,
				   int rows_per_size,
				   int time_column,
				   const char *series_names[],
				   int series_count);

#endif
