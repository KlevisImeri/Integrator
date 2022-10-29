#ifndef CnvCharNum
#define CnvCharNum

#include <stdio.h>
#include <math.h>
#include "cursorlib.h"

int is_num(char adress);
int char_to_int(char c);
int string_to_int(char *start);
double string_to_decimal(char *start);
double convert_to_num(char *adress, Direction DIR);

#endif