#ifndef parserlib
#define parserlib

#include "nodelib.h"
#include "cursorlib.h"
#include "chararray.h"

void node_parser(char *array, size_t size, char *adress_0, Node *output, size_t *index, double *x);
void parser(char *array, size_t size, Node *output, size_t *index, double *x);

#endif