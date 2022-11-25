#include "nodelib.h"
#include "cursorlib.h"


/*
	Definitions:
	-A block is '('...')'.
*/

/*
	Parameters: the block of expression
	Return: void
	It prints in the screen the block of expression.
	More precisely: (...(..(..)..)..)
					↑				↑
	It can do it without the size. It uses the ')'.
*/
void print_block(char *block){
	/*
		We know we have one bracket in the begnning 
	 	therefore we start from 1 number of brackets.
		We increment it if we find '(' and decrement if ')'.
		This can only equal 0 in the end of the expression.
	*/
	printf("{, (, ");
	int number_of_openbracket = 1;
	for(int i=1; number_of_openbracket!=0; i++){
		if(block[i] == '('){
			number_of_openbracket++;
		}
		if(block[i] == ')'){
			number_of_openbracket--;
		}
		printf("%c, ", block[i]);
	}
	printf("}\n");
}


/*	
	Parameters:
    - block         | block of expressions
    - nodes         | the array of nodes
    - x            	| the pointer to the variable
    - index_nodes   | keep track of the number of nodes created
 
	Returns:
		- index_nodes    | the number of nodes created
		- nodes        | the array filled with the nodes (pointer)
	
	Usage:
	You give it the block of expressions and the variable x and the array where to put the nodes. It fills the array with all the nodes in the block of expressions. It searches the nodes using hierarchy.
	It uses the create_node() function to create and put the nodes in 
	the array of nodes.
	Hierarchy:
		- functions
		- ^
		- * / <num>x (x)
		- + -
	Example:
	(x+2/x^2)    | searching for functions
	↑→
	(x+2/x^2)    | did not find functions
			↑
	(x+2/x^2)    | searching for '^'
	↑→     
	(x+2/x^2)    | if found '^'. create_node(↑)
		  ↑
	(x+2/[])    | searching for '^'
		 ↑→    
	(x+2/[])    | did not find '^'
		   ↑
	(x+2/[])    | searching for '*' '/' <num>x (x)
	↑→
	(x+2/[])    | if found '/'. create_node(↑)
		↑
	(x+[])    | did not find '*' '/' <num>x (x)
		↑
	(x+2/[])    | searching for '+' '-'
	↑→
	(x+2/[])    | it found '+'. create_node(↑)
	  ↑
	([])        | remove '(' and ')'
	[]        | returns the number of nodes created = index_nodes + 3
*/
int block_parser(char *block, Node *nodes, double *x, int index_nodes){
	//print_block(block);
	/* Notes:
		Usage of while loop, cursor and the order of while's 
		taks care of the hierarchy of the operations.
	*/

	//preparing
	char *cursor_;

	//Checking for functions in the block
	for(cursor_ = cursor(block, ')', ')', ')', FUNCTION); *cursor_ != ')'; cursor_ = cursor(cursor_, ')', ')', ')', FUNCTION)){
		//printf("Type: func\n");
		//print_block(block);
		create_Node(cursor_, nodes, x, index_nodes);
		index_nodes += 1;
	}	

	//checking for '^'
	for(cursor_ = cursor(block, '^', ')', ')', RIGHT); *cursor_ != ')'; cursor_ = cursor(cursor_, '^', ')', ')', RIGHT)){
		//printf("Type: ^\n");
		//print_block(block);
		create_Node(cursor_, nodes, x, index_nodes);
		index_nodes += 1;
	}
	
	//Checking for '*', '/','<num>x'
	for(cursor_ = cursor(block, '*', '/', 'x', RIGHT); *cursor_ != ')'; cursor_ = cursor(cursor_, '*', '/', 'x', RIGHT)){ 
		//if it is not '<num>x' but plane x just go to the next iteration
		if(*cursor_ == 'x' && !is_variable_multiplicaton(cursor_)) continue;
		// printf("Type: * /\n");
		// print_block(block);
		create_Node(cursor_, nodes, x, index_nodes);
		index_nodes += 1;
	}

	//Checking for '+','-'
	for(cursor_ = cursor(block, '+', '-', ')', RIGHT); *cursor_ != ')'; cursor_ = cursor(cursor_, '+', '-', ')', RIGHT)){
		//printf("Type: + -\n");
		//print_block(block);
		create_Node(cursor_, nodes, x, index_nodes);
		index_nodes += 1;
	}

	//print_block(block);
	//printf("---------------------\n");
	//Removing block( '(' and ')' );
	cursor_ = cursor(block, ')', ')', ')', RIGHT);
	*block = 0;
	*cursor_ = 0;	

	return index_nodes;
}


/*
	Parameters: 
	-block(no matter how it is).
	-the nodes array. It doesn't need it but the blovk_parser does.
	-the varible x which is needed when creatin the nodes.
	We use a recursive function go get through 
	the blocks. 
	When it find a block that doesn't have any blocks into it, 
	it calls the block_parser().
	Visualization:
	p1 - pareser 1
	p2 - parser 2
	'(' - Searching for '('
	✓ - Found the '('
	x - Did not found '('
	bp - calls te fucntion block_parser()
	[] - parsed the nodes by block_parser()
	✓p3 - p3 is finished

			  p1->'('						  p1->✓ 			  	
	(x * (x^(2+2)) - sin(x/2))  =>  (x * (x^(2+2)) - sin(x/2)) => 
	↑→  							     ↑				

	  p2->'('	   p2->✓      p3->'('    p3->x					   ✓p3
	(x^(2+2)) => (x^(2+2)) => (2+2)  => (2+2) => p3bp => (x * (x^[]) - sin(x/2)) => 
	↑→				↑		  ↑→			↑

	p2->'('	   p2->x				   ✓p2					p1->'('
	(x^[]) => (x^[]) => p2bp => (x * [] - sin(x/2)) => (x * [] - sin(x/2)) =>
	↑→			   ↑								   ↑→ 	

		  p1->✓			   p2->'('	  p2->x			        ✓p2
	(x * [] - sin(x/2)) => (x/2)  =>  (x/2) => p2bp = (x * [] - sin [] ) =>
			     ↑		   ↑→			  ↑

		p1->'('					  p1->x
	(x * [] - sin [] ) =>  (x * [] - sin [] ) => p1pb => [] => expression parsed
	↑→										↑
*/ 

int parser(char *block, Node *nodes, double *x, int index_nodes){
	// printf("1:  ");
	// print_block(block);

	//finding a new block
	char *newBlock_start;
	newBlock_start = cursor(block, '(', ')', ')', RIGHT);

	//Until it finds a new block it creates a new parser fo that block
	while(*newBlock_start == '('){
		//Recurisve paarsing
		index_nodes = parser(newBlock_start, nodes, x, index_nodes);
		// printf("%d", index_nodes);
		//To keep ti loopin to the next '('
		newBlock_start = cursor(block, '(', ')', ')', RIGHT);
	}

	return block_parser(block, nodes, x, index_nodes);
}	