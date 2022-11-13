#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cursorlib.h"
#include "CnvCharNum.h"

extern int index_nodes;

typedef struct Node{
	char type; //is it + or - or...
	int value; //every funciton has an int valu assign to it
	double x; //the previos num
	double y; //the previos num
	double *px; //point to the previous result
	double *py; //point to the previous result
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
	int i;
	for(i=0; i<size_expression; i++){
		//If a binary operation exits
		switch(expression[i]){
			case '^': number_of_nodes++; break;
			case '*': number_of_nodes++; break;
			case '/': number_of_nodes++; break;
			case '+': number_of_nodes++; break;
			case '-': number_of_nodes++; break;
			case 'x': 
				if(is_num(expression[i-1]) || (expression[i-1] == '(' && expression[i+1] == ')')) 
					number_of_nodes++; 
				break;
			default: break;
		}
		//If fucntion exits
		if(expression[i] >= 'a' && expression[i] <= 'z' && expression[i] != 'x'){
			number_of_nodes++;
			while(expression[i] >= 'a' && expression[i] <= 'z'){
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
	printf("{type:%c, value:%d, x:%f, y:%f, *px:%f, *py:%f, result:%f, index:%d}\n", node.type, node.value, node.x, node.y, *(node.px), *(node.py), node.result, node.index);
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
	Takes the pointer to the first letter of the function
	and returns the value of the fucntion.
	Every fucntion has a value which is determined by the 
	index position in the function array.
	End input puts the cursor at the end of the fucntion
*/
char *what_function(char *cursor, int *type){

	//array of all fucntinos
	char functions[5][10] = {"sin", "cos", "abs", "log", "exp"};
	int size = 5;

	//getiing the string of our funtion and soting it in a string
	char func[10]; 
	int i;
	for(i = 0; cursor[i] != 0; i++){
		func[i] = cursor[i];
		//clearing the array
		cursor[i] = 0;
	}
	func[i] = 0;
	//printf("function: %s\n", func);

	//checking if it maches with any of our fucntions in the array
	//of fucntions
	for(i = 0; i < size; i++){
		//printf("String compare: %d\n", strcmp(func, functions[i]));
		if(!strcmp(func, functions[i])){
			*type = i;
			return cursor;
		}
	}
	return NULL;

}

/*
	Parameters:
	-The adress of the operator or the beggining of the fucntion
	-The array of nodes and the size of of this array
	-varible
	Return: none
	It creates a new node and puts it in the node array
*/
void create_Node(char *adress, Node *nodes, double *variable){

/*---------------------------------------------------------------------------*/
	/* SETTING THE TYPE VALUE AND INDEX*/
	//Setting the type, value and index
	nodes[index_nodes].type = *adress;
	nodes[index_nodes].value = *adress;
	nodes[index_nodes].index = index_nodes;

	//declaring a cursor witch will be needed to dertermine 
	//the reight and the left values from the operator
	char *cursor = adress;

	//We chech if it si <num> exp: 3x
	//if is is than we have '*'
	if(*cursor == 'x'){
		nodes[index_nodes].type = '*';
		nodes[index_nodes].value = '*';
		/* Puts  it at the number exp 3x at 3 
									  ↑      */
		cursor--;
	}
	//If the node is a function then the value at the adress is a small letter
	//We also change the type and the value of the binary node
	if(*cursor >= 'a' && *cursor <= 'z' && *cursor != 'x'){
		int i;
		cursor = what_function(cursor, &i);
		// printf("the fucntionvalue: %d\n", i);
		nodes[index_nodes].type = 'f';
		//The value i represent the index of the function in the array of functions
		//Read what_fucntion() documentation
		nodes[index_nodes].value = i;
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
		nodes[index_nodes].py = variable;
		*cursor = 0;
	}else if(cursor[1] == 0 && cursor[-1] == 0){
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
	}else if(*cursor >= '0' && *cursor <= '9'){
			//it is a number
		nodes[index_nodes].y = convert_to_num(cursor, RIGHT);
		nodes[index_nodes].py = &nodes[index_nodes].y;
	}

/*---------------------------------------------------------------------------*/
	/*	LEFT SIDE OF NODE	*/
	//reseting and preperation
	cursor = adress;
	//For a function we don't care about the lef side
	//Therefore we point it to the the right sise
	if(nodes[index_nodes].type == 'f'){
		nodes[index_nodes].px = nodes[index_nodes].py;
		cursor[1] = index_nodes+1;
		//print_Node(nodes[index_nodes]);
		return;
	} 
	//loping until we hit something
	/*
		...3 0 0 +...
		      ←↑
	*/
	for(cursor--; *cursor == 0; cursor--){}
	//After we hit something we check
	//The order of chechking is important (hierarchy)
	if(*cursor == 'x'){
		//If it is variable
		//printf("1");
		nodes[index_nodes].px = variable;
		*cursor = 0;
	}else if(cursor[1] == '-' || cursor[1] == '+'){
		//If is a unary + and -
		//printf("4");
		nodes[index_nodes].x = 0;
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}else if(*cursor == '('){
		//It is just a plane x of form (x) => 1*x
		nodes[index_nodes].x = 1;
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}else if(cursor[1] == 0 && cursor[-1] == 0){
		//If it is node indentifer
		//printf("2");
		nodes[index_nodes].px = &nodes[*cursor-1].result;
		*cursor = 0;
	}else if( *cursor >= '0' && *cursor <= '9'){
		//If it is a number
		//printf("3");
		nodes[index_nodes].x = convert_to_num(cursor, LEFT);
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}else if(is_num(*cursor)){
		//It is * multiplication of form <num>x
		//printf("5");
		nodes[index_nodes].x = convert_to_num(cursor, LEFT);
		nodes[index_nodes].px = &nodes[index_nodes].x;
	}	
/*---------------------------------------------------------------------------*/	
	/* CREATING NODE IDENTIFIER FOR THIS NODE*/
	
	//making the value at the operater equal to the index in 
	//array of nodes (operations[])
	*adress = index_nodes+1;
	//print_Node(nodes[index_nodes]);
}

//evaluate Node
double eval_Nodes(Node *nodes, size_t number_of_nodes){
	int i;
	for(i=0; i<number_of_nodes; i++){
		switch (nodes[i].type){
		case 'f':
			switch(nodes[i].value){
				case 0:
					nodes[i].result = sin(nodes[i].px[0]);
					//printf("Result: %f index: %d\n", nodes[0].result, nodes[0].index);
					break;
				case 1:
					nodes[i].result = cos(nodes[i].px[0]);
					break;
				case 2:
					nodes[i].result = fabs(nodes[i].px[0]);
					break;
				case 3:
					nodes[i].result = log(nodes[i].px[0]);
					break;
				case 4:
					nodes[i].result = exp(nodes[i].px[0]);
					break;
				default:
					printf("This kind of fucntion doesnt exits.\n");	
			}
			break;
		case '^':
			nodes[i].result = pow(nodes[i].px[0], nodes[i].py[0]);
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


