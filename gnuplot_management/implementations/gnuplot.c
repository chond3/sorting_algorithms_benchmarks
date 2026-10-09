#include "../headers/gnuplot.h"

int plot_algorithm(FILE *gnuplot,
				   const char *plot_title,
				   const char *data_file,
				   const char *image_file,
				   int rows_per_size,
				   int time_column,
				   const char *series_names[],
				   int series_count)
{
	if (gnuplot == NULL || plot_title == NULL || data_file == NULL ||
		image_file == NULL || series_names == NULL || rows_per_size <= 0 ||
		time_column <= 0 || series_count <= 0 || series_count > rows_per_size)
	{
		return -1;
	}

	if (fprintf(gnuplot, "set title '%s'\n", plot_title) < 0 ||
		fprintf(gnuplot, "set output '%s'\n", image_file) < 0 ||
		fprintf(gnuplot, "plot ") < 0)
	{
		return -1;
	}

	for (int series = 0; series < series_count; series++)
	{
		if (series_names[series] == NULL ||
			fprintf(gnuplot,
					"'%s' every %d::%d using 1:%d "
					"with linespoints linewidth 3 pointtype 7 "
					"pointsize 1.3 title '%s'%s",
					data_file, rows_per_size, series, time_column,
					series_names[series], series == series_count - 1 ? "\n" : ", ") < 0)
		{
			return -1;
		}
	}

	return 0;
}
