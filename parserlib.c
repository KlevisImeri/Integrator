#include "nodelib.h"
#include "cursorlib.h"
#include "chararray.h"
//searches for nodes and creates them according with
//the order of operations and the hiearchy.
void node_parser(char *array, size_t size, char *adress_0, Node *output, size_t *index, double *x){
	char *adress;
	int terminate;

	terminate = 1;
	while(terminate == 1){
		print_char_array(array, size);
		adress = cursor(adress_0, 'a', 'z', BETWEEN);
		printf("adress: %c\n",*adress);
		if(*adress == ')'){
			terminate = 0;
		}else{
			create_Node(adress, output, *index, x);
			*index += 1;
		}
	}

	terminate = 1;
	while(terminate == 1){
		print_char_array(array, size);
		adress = cursor(adress_0, ')', '^', RIGHT);
		if(*adress == '^'){
			create_Node(adress, output, *index, x);
			*index += 1;
		}else{
			terminate = 0;
		}
	}
	

	terminate = 1;
	while(terminate == 1){
		print_char_array(array, size);
		adress = cursor(adress_0, '*', '/', AT);
		if(*adress == '*' || *adress == '/'){
			create_Node(adress, output, *index, x);
			*index += 1;
		}else{
			terminate = 0;
		}
	}

	
	terminate = 1;
	while(terminate == 1){	
		print_char_array(array, size);
		adress = cursor(adress_0, '+', '-', AT);
		if(*adress == '+' || *adress == '-'){
			create_Node(adress, output, *index, x);
			*index += 1;
		}else{
			terminate = 0;
		}
	}
	
	printf("Removing Block '( ')'------------------\n");
	adress = cursor(adress_0, ')', ')', RIGHT);
	*adress_0 = 0;
	*adress = 0;
	printf("6:  ");
	print_char_array(array, size);
	printf("Done------------------------------------\n");
}

//Find the openening of bloack and calls the node_parser 
//to create the nodes.
void parser(char *array, size_t size, Node *output, size_t *index, double *x){
	//printing before starting
	printf("1:  ");
	print_char_array(array, size);

	char *adress_0;
	adress_0 = cursor(array, ')', '(', RIGHT);
	
	while(*adress_0 == '('){
		printf("Recursive Parsing-------------------------\n");
		parser(adress_0, size, output, index, x);
		printf("Done--------------------------------------\n");
		adress_0 = cursor(array, ')', '(', RIGHT);
	}

	printf("Parsing Nodes-------------------------------\n");
	node_parser(array, size, array, output, index, x);
	printf("Done--------------------------------------\n");
}	