#ifndef parserlib
#define parserlib

#include "nodelib.h"
#include "cursorlib.h"

void print_block(char *block);
int parser(char *block, Node *nodes, double *x, int index_nodes);
int block_parser(char *block, Node *nodes, double *x, int index_nodes);

#endif