#include <stdio.h>
#include "nodelib.h"
#include "bitmap.h"
#include "parserlib.h"
#include "chararray.h"
#include "menu.h"

int index_nodes = 0;

//we need to tale start as a pointer because the eval_Node is connected with a pointer the pointer
double interval_integrator(Node *nodes, size_t number_of_nodes, double *start, double end, double step){
	double sum = 0;
	double i = *start;

	for(; *start <= end; *start += step){
		// printf("sum:%f\n", sum);
		// printf("%f\n", eval_Nodes(nodes, number_of_nodes));
		sum += eval_Nodes(nodes, number_of_nodes)*step;
	}

	printf("\nThe Riemann Sum:%f\n", sum);
	//resetting start to it's inicial point
	*start = i;
	return sum;

}

int main(){

	//Parameters and menu for the the programm
	//You can change the startup parameters in here
	double step = 0.001, start = -3.14, end = 3.14; 
	start_menu(&step, &start, &end);
	//Start < end always 
	if(start > end){
		double temp = end;
		end = start;
		start = temp;
	}

	//Takind a valid expression form the user
	size_t size_expression;
	char *expression = take_valid_expression(&size_expression);
	

	//Creationg a dynamic array where the nodes will be stored
	size_t number_of_nodes = number_of_nodes_in_expression(expression, size_expression);
	Node *nodes = (Node *)malloc(sizeof(Node)*number_of_nodes);
	if(nodes == NULL) return 1;
	
	//Parsing all the nodes to the nodes array
	parser(expression, nodes, &start);
	//print_char_array(expression, size_expression);
	
	//Findig the integral of the function
	interval_integrator(nodes, number_of_nodes, &start, end, step);


	// printf("--------\n");
	print_Node_array(nodes, number_of_nodes);

	
	create_bitmap(nodes, number_of_nodes, &start, end, step, 2000, 2000, 600, 6);

	free(expression);
	free(nodes);

	return 0;
}

	
