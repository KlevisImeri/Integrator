#ifndef charlib
#define charlib

#include <stdio.h>
#include <math.h>
#include "cursorlib.h"


int what_function(char *cursor);
int is_binary_operator(char c);
int is_small_letter(char c, char omit);
int is_letter(char c, char omit);
int is_num(char c);
int char_to_int(char c);
int string_to_int(char *start);
double string_to_decimal(char *start);
double convert_to_num(char *address, Direction DIR);
int is_variable_multiplicaton(char *cursor);

#endif