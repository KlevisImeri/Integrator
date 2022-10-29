#ifndef nodelib
#define nodelib

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cursorlib.h"
#include "CnvCharNum.h"

typedef struct Node{
	char type; 
	int value; 
	double x; 
	double y; 
	double *px; 
	double *py; 
	double result;
	int index;
} Node;
void print_Node(Node node);
int what_function(char *cursor, int *end);
void create_Node(char *adress, Node *output, int index, double *variable);
double eval_Node(Node *node, size_t size);
void print_Node_array(Node *array, int index);

#endif