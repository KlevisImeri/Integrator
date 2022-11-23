#ifndef nodelib
#define nodelib

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cursorlib.h"
#include "charlib.h"

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
int number_of_nodes_in_expression(char *expression, size_t size_expression);
void print_Node(Node node);
void print_Node_array(Node *array, size_t size);
void create_Node(char *adress, Node *nodes, double *variable);
double eval_Nodes(Node *Nodes, size_t number_of_nodes);

#endif