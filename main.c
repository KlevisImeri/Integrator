#include <stdio.h>
#include "nodelib.h"
#include "bitmap.h"
#include "parserlib.h"
#include "chararray.h"

double interval_integrator(Node *operations, size_t size, double *start, double end, double step){
	double sum = 0;

	for(; *start <= end; *start += step){
		sum += eval_Node(operations, size)*step;
	}

	printf("sum:%f\n", sum);
	return sum;

}

int main(){
	char array[40] = {0};
	double start = 0;
	double end = 3.14159265359;
	double step = 0.001;

	input_char_array(array);

	//creating the nodetree of the expression
	Node operations[20] = {0};
	size_t index  = 0;
	parser(array, 40, operations, &index, &start);
	
	interval_integrator(operations, index, &start, end, step);

	create_bitmap(operations, index, &start, 1000, 1000, 600, 4);

	return 0;
}

	
