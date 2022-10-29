#include <stdio.h>
#include <math.h>

typedef enum Direction{
	RIGHT,
	LEFT,
	AT,
	BETWEEN
} Direction;

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


typedef struct UnaryNode{
	char type; 
	double x;
	double *px;
	double result;
	int index;
} UnaryNode;

//printing Binary node
void print_Node(Node node){
	printf("{type:%c, x:%f, y:%f, *px:%f, *py:%f, result:%f, index:%d}\n", node.type, node.x, node.y, *(node.px), *(node.py), node.result, node.index);
}

//chechking if a character is a number
int is_num(char adress){
	if(adress >= '0' && adress <= '9'){
		return 1;
	}
	return 0;
}

//Convert char to 1digit int;
int char_to_int(char c){
	return c-'0';
}

//Creates an integer written as an array of char. 
//It evaluates from right ot left form the given starting point or '.' for decimal
int string_to_int(char *start){
	int num = 0;
	*start = 0;
	start--;

	for(int i=0; is_num(*start); i++, start--){
		num += char_to_int(*start) * pow(10, i);
		*start = 0;
	}

	return num;
}

//Evaualtes the decimal point numbers form '.' to the right.
//Number is given as an array of char.
double string_to_decimal(char *start){
	double num = 0.0;
	*start = 0;
	start++;

	for(int i=1; is_num(*start); i++, start++){
		num += char_to_int(*start) * pow(10, -i);
		*start = 0;
	}

	return num;
}

//converting a char to double
//Takes in the adress of the first or last dig depending on direction
double convert_to_num(char *adress, Direction DIR){
	int num;
	double decimal;

	switch(DIR){
		case RIGHT:
			while(is_num(*adress)){
				adress++;
			}
			num = string_to_int(adress);
			decimal = string_to_decimal(adress);
			break;
		case LEFT:
			while(is_num(*adress)){
				adress--;
			}
			num = string_to_int(adress);
			decimal = string_to_decimal(adress);
			break;
		default:
			printf("Error!\nThere is no such direction!\n");	
	}

	return num+decimal;
}


//Transversing in the memory to right or left from the 
//given starting adress. Cheacks if the given character exists.
//Gives back the adress of that char.
//If char doesn't exist till the given condition then it ouputs NULL.
char *cursor(char *cursor, char condition, char c, Direction DIR){
	switch(DIR){
		case RIGHT:
			cursor++;
			while(*cursor != condition){
				if(*cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case LEFT:
			cursor--;
			while(*cursor != condition){
				if(*cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor--;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case BETWEEN:
			cursor--;
			while(*cursor != ')'){
				if(*cursor >= condition && *cursor <= condition){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor--;
			}
			printf("Cursor at: %c\n", *cursor);
			break;

		case AT:
			cursor++;
			while(*cursor != ')'){
				if(*cursor == condition || *cursor == c){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
			}
			printf("Cursor at: %c\n", *cursor);
			break;
		default:
			printf("Error!\nThere is no such direction!\n");
			break;
	}	
	return cursor;
}

//create Node
//Ouputs at a specific location specified in the inputs
void create_Node(char *adress, Node *output, int index, double *variable){
		char *adress_0 = adress;
		output[index].type = *adress;
		output[index].index = index;
		*adress = index+1;
		switch(adress[-1]){
			case 0:
				adress-=2;
				while(*adress == 0){
					adress--;
				}
				output[index].px = &output[*adress-1].result;
				*adress = 0;
				break;
			case 'x':
				output[index].px = variable;
				adress[-1] = 0;
				break;
			default:
				output[index].x = convert_to_num(adress-1, LEFT);
				output[index].px = &output[index].x;
				break;
		}
		//reseting
		adress = adress_0;
		switch(adress[1]){
			case 0:
				adress+=2;
				while(*adress == 0){
					adress++;
				}
				output[index].py = &output[*adress-1].result;
				*adress = 0;
				break;
			case 'x':
				output[index].py = variable;
				adress[1] = 0;
				break;
			default:
				output[index].y = convert_to_num(adress+1, RIGHT);
				output[index].py = &output[index].y;
				break;
		}
		print_Node(output[index]);
}

//evaluate Node
double eval_Node(Node *node, size_t size){
	while(size>0){
		switch (node->type){
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

//Prints array in array format
void print_array(char *array, size_t size){
	printf("{");
	for(int i=0; i<size-1; i++){
		printf("%c, ", array[i]);
	}
	printf("%c}\n", array[size-1]);
}

//searches for nodes and creates them according with
//the order of operations and the hiearchy.
void node_parser(char *array, size_t size, char *adress_0, Node *output, int *index, double *x){
	char *adress;
	int terminate;

	terminate = 1;
	while(terminate == 1){
		print_array(array, size);
		adress = cursor(adress_0, 'a', 'z', BETWEEN);
		
		if(*adress == '^'){
			create_Node(adress, output, *index, x);
			*index += 1;
		}else{
			terminate = 0;
		}
	}

	terminate = 1;
	while(terminate == 1){
		print_array(array, size);
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
		print_array(array, size);
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
		print_array(array, size);
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
	print_array(array, size);
	printf("Done------------------------------------\n");
}

//Find the openening of bloack and calls the node_parser 
//to create the nodes.
void parser(char *array, size_t size, Node *output, int *index, double *x){
	//printing before starting
	printf("1:  ");
	print_array(array, size);

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

//prints an array of nodes
void print_Node_array(Node *array, int index){
	for(int i = 0; i<index; i++){
		print_Node(array[i]);
	}
}

int main(){
	// char array[40] = "((x+2.0^4.0*x/1.0)+1.0+(4.0+x))";
	char array[40] = "(sin(x))";

	double x = 2;
	Node operations[20];

	//printf("The adress value: %c , %p\n", *adress, adress);
	// adress = cursor(array, 20, '+', RIGHT);
	int index = 0;
	parser(array, 40, operations, &index, &x);

	printf("Evaluating-----------------------\n");
	double result = eval_Node(operations, index);
	printf("Done------------------------------\n");	
	printf("Printing-----------------------\n");
	print_Node_array(operations, index);
	printf("Done------------------------------\n");	

	printf("The result: %f\n", result);

	print_array(array, 40);

	return 0;
}

	
