#include <stdio.h>
#include <string.h>
#include <math.h>
#include "cursorlib.h"
#include "CnvCharNum.h"

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

//prints Node
void print_Node(Node node){
	printf("{type:%c, value:%d, x:%f, y:%f, *px:%f, *py:%f, result:%f, index:%d}\n", node.type, node.value, node.x, node.y, *(node.px), *(node.py), node.result, node.index);
}

//takes the pointer to the rist letter of the fucntion
//and return the value of the fucntion.
//every fucntion has a value which is determined by the 
//index position in the function array.
//end input puts the cursor at the end of the fucntion
int what_function(char *cursor, int *end){

	//array of all fucntinos
	char functions[5][10] = {"sin", "cos", "abs", "log", "exp"};
	int size = 5;

	//getiing the string of our funtionc and soting it in a string
	char func[10]; 
	int i;
	for(i = 0; cursor[i] != 0; i++){
		func[i] = cursor[i];
		//clearing the array
		cursor[i] = 0;
	}
	func[i] = 0;
	printf("function: %s\n", func);
	//setting how far ways the end is form the cursor
	*end = i;

	//checking if it maches with any of our fucntions in the array
	//of fucntions
	for(i = 0; i < size; i++){
		printf("String compare: %d\n", strcmp(func, functions[i]));
		if(!strcmp(func, functions[i])){
			return i;
		}
	}
	return 11;

}

//create Node
//Ouputs at a specific location specified in the inputs
void create_Node(char *adress, Node *output, int index, double *variable){
	
	//seeting the type value and index of node
	output[index].type = *adress;
	output[index].value = *adress;
	output[index].index = index;

	//declaring a cursor witch will be needed to dertermine 
	//the reight and the left values from the operator
	char *cursor;

	//preperaton
	cursor = adress;
	//if the node is a function witch means the value at the
	//adress is a small letter
	if(*cursor >= 'a' && *cursor <= 'z'){
		int end;
		printf("lalal\n");
		int i = what_function(cursor, &end);
		printf("the fucnitnvalue: %d\n", i);
		output[index].type = 'f';
		output[index].value = i;

		//moving the cursor till the end of string of fucntion
		//+1 so it strats form the 0 not letter.
		cursor += end + 1;
		while(*cursor == 0){
			cursor++;
		}
		//seting the px and py values of the function
		if(*cursor == 'x'){
			output[index].px = variable;
			output[index].py = variable;
			cursor[1] = 0;
		}else{
			output[index].px = &output[*cursor-1].result;
			output[index].py = &output[*cursor-1].result;
			*cursor = 0;
		}
	
		//clearing the indexing of the previos node in the array
		*cursor = 0;

		//bacause it is a fucnton we dont't want he first char near
		//the binary operator to be the index but there should be 
		//a '\0' in between therefore secound char of fucntion should 
		//be the index
		adress++;

		*adress = index+1;
		print_Node(output[index]);

		return;
	}

	//preperation
	cursor = adress;
	char left_char = cursor[-1];
	//cheking what is in the left side and 
	//putting it in the x or *px of the NODE
	if(left_char == 0){
		cursor-=2;
		while(*cursor == 0){
			cursor--;
		}
		output[index].px = &output[*cursor-1].result;
		*cursor = 0;
	}else if(left_char == 'x'){
		output[index].px = variable;
		cursor[-1] = 0;
	}else if(left_char >= '0' && left_char <= '9'){
		output[index].x = convert_to_num(cursor-1, LEFT);
		output[index].px = &output[index].x;
	}else{
		output[index].x = 0;
		output[index].px = &output[index].x;
	}

	
	//reseting and preperation
	cursor = adress;
	char right_char = cursor[1];
	//cheking what is in the Right side and 
	//putting it in the y or *py of the NODE
	if(right_char == 0){
		cursor+=2;
		while(*cursor == 0){
			cursor++;
		}
		output[index].py = &output[*cursor-1].result;
		*cursor = 0;
	}else if(right_char == 'x'){
		output[index].py = variable;
		cursor[1] = 0;
	}else if(right_char >= '0' && right_char <= '9'){
		output[index].y = convert_to_num(cursor+1, RIGHT);
		output[index].py = &output[index].y;
	}
	
	//making the value at the operater equal to the index in 
	//array of nodes (operations[])
	*adress = index+1;

	print_Node(output[index]);
}

//evaluate Node
double eval_Node(Node *node, size_t size){
	while(size>0){
		switch (node->type){
		case 'f':
			switch(node->value){
				case 0:
					node->result = sin(node->px[0]);
					// printf("Result: %f index: %d\n", node->result, node->index);
					break;
				case 1:
					node->result = cos(node->px[0]);
					break;
				case 2:
					node->result = fabs(node->px[0]);
					break;
				case 3:
					node->result = log(node->px[0]);
					break;
				case 4:
					node->result = exp(node->px[0]);
					break;
				default:
					printf("This kind of fucntion doesnt exits.\n");	
			}
			break;
		case '^':
			node->result = pow(node->px[0], node->py[0]);
			// printf("Result: %f index: %d\n", node->result, node->index);
			break;
		case '*':
			node->result = node->px[0] * node->py[0];
			break;
		case '/':
			node->result = node->px[0] / node->py[0];
			break;
		case '+':
			node->result = node->px[0] + node->py[0];
			// printf("Result: %f\n", node->result);
			break;
		case '-':
			node->result = node->px[0] - node->py[0];
			break;
		}
		
		node++;
		size--;
	}
	node--;
	return node->result;
}

//prints an array of nodes
void print_Node_array(Node *array, int index){
	for(int i = 0; i<index; i++){
		print_Node(array[i]);
	}
}
