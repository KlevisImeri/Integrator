#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cursorlib.h"
#include "charlib.h"

/*
	Usage:
	It is a node in a binary tree. The pointers px and py are 
	connected to the results of the other nodes. Every node is 
	stored in the array of nodes. x and y are used to store 
	numbers. px and py can point to then. px and py values at
	the addresses get evaluated when called the eval_Nods() function.

*/
typedef struct Node{
	char type; //is it + or - or...
	int value; //every funciton has an int valu assign to it
	double x;  //the left num
	double y; //the right num
	double *px; //point to the left result or num
	double *py; //point to the right result or num
	double result;
	int index;
} Node;

/*
	Parameters: array of epression and its size
	Output: the nubmer of nodes in the expression
*/
size_t number_of_nodes_in_expression(char *expression, size_t size_expression){
	//Preparaion
	size_t number_of_nodes = 0;
	//Iterating
	for(int i=0; i<size_expression; i++){
		//If a binary operation exits
		if(is_binary_operator(expression[i])){
			//printf("1");
			number_of_nodes++;
		}
		
		//If we have the form <num>x or plane x
		if( expression[i] =='x'){
			if(is_num(expression[i-1]) || (expression[i-1] == '(' && expression[i+1] == ')')){
				//printf("2");
				number_of_nodes++; 
			}
		}
				
		//If fucntion exits
		if(is_small_letter(expression[i], 'x')){
			//printf("3");
			number_of_nodes++;
			while(is_small_letter(expression[i], '\0')){
				i++;
			}
			i--;
		}
	}
	
	//printf("Number of nodes: %ld\n", number_of_nodes);
	return number_of_nodes;
}

/*
    Parameter: node
    Return: void
    Prints the node in format.
*/
void print_Node(Node node){
	printf("{\n"		
		   "  type:%c, value:%d\n"		
		   "  x:%g, y:%g\n"	
		   "  *px:%g, *py:%g\n"	
		   "  result:%g, index:%d\n"
		   "}\n\n", 
		   node.type, node.value, node.x, node.y, *(node.px), *(node.py), node.result, node.index);
}

/*
	Parameters: array of nodes, size of array
	Return: none
	Prints in the console the array of nodes.
*/
void print_Node_array(Node *array, size_t size){
	for(int i = 0; i<size; i++){
		print_Node(array[i]);
	}
}

/*
	Parameters:
    - address        | address of the node
    - nodes        | the array of nodes
    - variable        | the pointer to the variable
    - index_nodes    | keep track of the number of nodes created
 
	Returns:
		- nodes        | the array filled with the new node (pointer)
 
	Usage:
	You give it the position of the node and it:
	1. Creates the node
	2. Deletes it from the expression
	3. Creates the node identifier for that node
	Types of nodes and entering the node:
	- Binary operation: ^,*,/,+,-        | at binary operator
	- Special: <num>x, (x)             | at x
	- Functions: sin, cos, abs, log, exp    | at first letter of function

	For examples see the developer documentation
*/
void create_Node(char *address, Node *nodes, double *variable, int index_nodes){
	//printf("adress: %c\n", *adress);
 /*---------------------------------------------------------------------------*/
	/* SETTING THE TYPE VALUE AND INDEX*/
	//declaring a cursor witch will be needed to dertermine 
	//the reight and the left values from the operator
	char *cursor = address;
	nodes[index_nodes].index = index_nodes;

	if(is_binary_operator(*cursor)){
		nodes[index_nodes].type = *address;
		nodes[index_nodes].value = *address;
	}else if(*cursor == 'x'){
		//We checked if it si <num> exp: 3x
		//if is is than we have '*'
		nodes[index_nodes].type = '*';
		nodes[index_nodes].value = '*';

		/* Puts  it at the number exp 3x at 3 
									  ↑      */
		cursor--;
	}else if(is_small_letter(*cursor, 'x')){
		//If the node is a function then the value at the adress is a small letter
		
		//geting the type of the function 
		int i = what_function(cursor);
		
		// printf("the fucntionvalue: %d\n", i);
		nodes[index_nodes].type = 'f';
		nodes[index_nodes].value = i;
		address++;
		/*  ..+sin... => ...+sin...
	 	   	   ↑		      ↑      */
		//loop and make all zeors for the function
		// sin  => \0\0\0
		while(is_small_letter(*cursor, '\0')){
			*cursor = '\0';
			cursor++;
		}
	}

 /*---------------------------------------------------------------------------*/
	/*	RIGHT SIDE OF NODE	*/
	/*
		+1 so it strats form the 0 not letter.
		..sin 0 0 x...     ....+ 0 0 3...
			  ↑→				 ↑→
	*/
	for(cursor++; *cursor == 0; cursor++){}
	/*
		..sin 0 0 x...	   ....+ 0 0 3...
				  ↑					 ↑
	*/

	
	if(*cursor == 'x'){
		//printf("Right: x\n");

		nodes[index_nodes].py = variable;
		*cursor = 0;
	}else if(cursor[1] == 0 && cursor[-1] == 0){
		//printf("Right: []\n");
		/*
			if it is a node identifier than we can check the close values
					   ↓
			..+ 0 0 0 '9' 0 ....  => 9-1 = 8 is the index of the node in that position
					↑	  ↑
			if they are zero when we know it is a node indentifier and not a number
		*/
		
		//*cursor-1 gives you the index of the node in the array which the node indentifier identifies.
		nodes[index_nodes].py = &nodes[*cursor-1].result;
		*cursor = 0;
	}else if(is_num(*cursor)){
		//it is a number
		//printf("Right: num\n");
		
		nodes[index_nodes].y = convert_to_num(cursor, RIGHT);
		nodes[index_nodes].py = &nodes[index_nodes].y;
	}

 /*---------------------------------------------------------------------------*/
	/*	LEFT SIDE OF NODE	*/
	//reseting and preperation
	cursor = address;

	//loping until we hit something
	for(cursor--; *cursor == 0; cursor--){}
	/*
		...3 0 0 +... => ...3 0 0 +...
		      ←↑		   ←↑
	*/
	
	//After we hit something we check
	//The order of chechking is important (hierarchy)
	if(nodes[index_nodes].type == 'f'){
		//printf("Left: func\n");
		//For a function we don't care about the lef side
		//Therefore we point it whre right side is pointing
		nodes[index_nodes].px = nodes[index_nodes].py;
	}else if(*cursor == 'x'){
		//If it is variable
		//printf("Left: x\n");
	
		nodes[index_nodes].px = variable;
		*cursor = 0;
	}else if((cursor[1] == '-' || cursor[1] == '+') && cursor[0]=='('){
		//If is a unary + and -
		//printf("Left: +/-\n");

		nodes[index_nodes].x = 0;
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}else if(*cursor == '('){
		//It is just a plane x of form "(x)" => 1*x
		//printf("Left: (	");

		nodes[index_nodes].x = 1;
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}else if(cursor[1] == 0 && cursor[-1] == 0){
		//If it is node indentifer
		//printf("Left: []\n");
		
		nodes[index_nodes].px = &nodes[*cursor-1].result;
		*cursor = 0;
	}else if(is_num(*cursor)){
		//It is a number
		//printf("Left: num\n");

		nodes[index_nodes].x = convert_to_num(cursor, LEFT);
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}	
 /*---------------------------------------------------------------------------*/	
	/* CREATING NODE IDENTIFIER FOR THIS NODE*/
	//printf("adress: %c\n", *adress);
	*address = index_nodes+1;
	/*
		..+sin => +0[]0
			↑	  	↑
		5.0/x => 0[]0
		   ↑	  ↑
	*/
	
	
	//print_Node(nodes[index_nodes]);
}

/*
	Parameters:
		- nodes            | the array of nodes
		- number_of_nodes     | the size of the array of nodes    
	
	Returns:
		- double     | the value of evaluating all the nodes. Or the 
	| value the mathematical expression gives.
	Usage:
	Evaluates the array of nodes and finds the result of the expression 
	correlating to the variable. Returns it. Values at py and px are 
	evaluated not x and y.
*/
double eval_Nodes(Node *nodes, size_t number_of_nodes){
	int i;
	for(i=0; i<number_of_nodes; i++){
		switch (nodes[i].type){
		case 'f':
			switch(nodes[i].value){
				case 1:
					nodes[i].result = sin(nodes[i].px[0]);
					//printf("Result: %f index: %d\n", nodes[0].result, nodes[0].index);
					break;
				case 2:
					nodes[i].result = cos(nodes[i].px[0]);
					break;
				case 3:
					nodes[i].result = fabs(nodes[i].px[0]);
					break;
				case 4:
					nodes[i].result = log(nodes[i].px[0]);
					break;
				case 5:
					nodes[i].result = exp(nodes[i].px[0]);
					break;
				//default:
					//printf("This kind of fucntion doesnt exits.\n");	
			}
			break;
		case '^':
			nodes[i].result = pow(fabs(nodes[i].px[0]), nodes[i].py[0]);
			// printf("Result: %f index: %d\n", nodes[i].result, nodes[i].index);
			break;
		case '*':
			nodes[i].result = nodes[i].px[0] * nodes[i].py[0];
			break;
		case '/':
			nodes[i].result = nodes[i].px[0] / nodes[i].py[0];
			break;
		case '+':
			nodes[i].result = nodes[i].px[0] + nodes[i].py[0];
			// printf("Result: %f\n", nodes[i].result);
			break;
		case '-':
			nodes[i].result = nodes[i].px[0] - nodes[i].py[0];
			break;
		}
	}
	//print_Node_array(nodes, number_of_nodes);
	return nodes[i-1].result;
}


