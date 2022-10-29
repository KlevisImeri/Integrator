#ifndef bitmap
#define bitmap

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nodelib.h"

typedef struct rgb_data{
		float r, g, b;
} rgb_data;
void save_bitmap(const char *file_name, int width, int height, int dpi, rgb_data *pixel_data);
void create_bitmap(Node *operations, size_t size, double *start, int width, int height, int dpi, int numberline_length);

#endif