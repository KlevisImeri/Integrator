#ifndef chararray
#define chararray

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_char_array(char *array, size_t size);
void copyarr(char* destination, char* source, size_t size_source);
void *take_expression(size_t *size);
int is_expression_valid(char *expression, size_t size);
char *take_valid_expression(size_t *size);

#endif