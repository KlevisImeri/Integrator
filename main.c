#include <stdio.h>
#include "nodelib.h"
#include "bitmap.h"
#include "parserlib.h"
#include "chararray.h"

//we need to tale start as a pointer because the eval_Node is connected with a pointer the pointer
double interval_integrator(Node *operations, size_t size, double *start, double end, double step){
	double sum = 0;
	double i = *start;

	for(; *start <= end; *start += step){
		sum += eval_Node(operations, size)*step;
	}

	printf("sum:%f\n", sum);
	//resetting start to it's inicial point
	*start = i;
	printf("integrator: %f\n", *start);
	return sum;

}

int main(){
	char array[40] = {0};
	input_char_array(array);
	
	double start;
	double end;
	double step;
	printf("Input lowerbound, upperbound, partition: ");
	scanf("%lf, %lf, %lf", &start, &end, &step);
	printf("%f\n",start);

	

	//creating the nodetree of the expression
	Node operations[20] = {0};
	size_t index  = 0;
	parser(array, 40, operations, &index, &start);
	
	interval_integrator(operations, index, &start, end, step);

	create_bitmap(operations, index, &start, end, step, 1000, 1000, 600, 4);

	return 0;
}

	
