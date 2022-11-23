#include "nodelib.h"
#include "cursorlib.h"

extern int index_nodes;

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
	printf("{,(, ");
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
	-block(wihtout smaller blocks into it).(Refer to the recursin we did in the parser!)
	-the array of nodes. It puts the created nodes into the array.
	-the nodes depend on the value x form outside.
	Return: void
	One of the most important fucntions.
	Searches for nodes and creates them according with
	the order of operations and the hiearchy.
*/
void block_parser(char *block, Node *nodes, double *x){
	print_block(block);
	/* Notes:
		Usage of while loop, cursor and the order of while's 
		taks care of the hierarchy of the operations.
	*/

	//preparing
	char *cursor_;
	int terminate;

	//Checking for functions in the block
	terminate = 1;
	cursor_ = block;
	while(terminate == 1){
		cursor_ = cursor(cursor_, 'a', 'z', BETWEEN);
		if(*cursor_ == ')'){
			terminate = 0;
		}else{
			printf("1");
			print_block(block);
			create_Node(cursor_, nodes, x);
			index_nodes += 1;
		}
	}

	//checking for '^'
	terminate = 1;
	cursor_ = block;
	while(terminate == 1){
		cursor_ = cursor(cursor_, ')', '^', RIGHT);
		if(*cursor_ == '^'){
			printf("2");
			print_block(block);
			create_Node(cursor_, nodes, x);
			index_nodes += 1;
		}else{
			terminate = 0;
		}
	}
	
	//Checking for '*', '/','<num>x'
	terminate = 1;
	cursor_ = block;
	while(terminate == 1){ 
		cursor_ = cursor(cursor_, '*', '/', ATX);
		if(*cursor_== '*' || *cursor_ == '/' || is_variable_multiplicaton(cursor_)){
			printf("3");
			print_block(block);
			create_Node(cursor_, nodes, x);
			index_nodes += 1;
		}else{
			terminate = 0;
		}
	}

	//Checking for '+','-'
	terminate = 1;
	cursor_ = block;
	while(terminate == 1){
		printf("4");
		cursor_ = cursor(cursor_, '+', '-', AT);
		if(*cursor_ == '+' || *cursor_ == '-'){
			print_block(block);
			create_Node(cursor_, nodes, x);
			index_nodes += 1;
		}else{
			terminate = 0;
		}
	}
	
	//Removing block( '(' and ')' );
	cursor_ = cursor(block, ')', ')', RIGHT);
	*block = 0;
	*cursor_ = 0;
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

void parser(char *block, Node *nodes, double *x){
	// //printing before starting
	// printf("1:  ");
	// print_block(block);

	//finding a new block
	char *newBlock_start;
	newBlock_start = cursor(block, '(', ')', RIGHT);

	//Until it finds a new block it creates a new parser fo that block
	while(*newBlock_start == '('){
		//Recurisve paarsing
		parser(newBlock_start, nodes, x);
		//To keep ti loopin to the next '('
		newBlock_start = cursor(block, '(', ')', RIGHT);
	}

	block_parser(block, nodes, x);
}	