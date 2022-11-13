#ifndef parserlib
#define parserlib

#include "nodelib.h"
#include "cursorlib.h"

void print_block(char *block);
void block_parser(char *block, Node *nodes, double *x);
void parser(char *block, Node *nodes, double *x);

#endif