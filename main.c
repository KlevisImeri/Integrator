#include <stdio.h>
#include <math.h>
#include <string.h>

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
	printf("{type:%c, value:%d, x:%f, y:%f, *px:%f, *py:%f, result:%f, index:%d}\n", node.type, node.value, node.x, node.y, *(node.px), *(node.py), node.result, node.index);
}

//chechking if a character is a number
int is_num(char adress){
	if(adress >= '0' && adress <= '9'){
		return 1;
	}
	return 0;
}

//takes the pointer to the rist letter of the fucntion
//and return the value of the fucntion.
//every fucntion has a value which is determined by the 
//index position in the function array.
//end input puts the cursor at the end of the fucntion
int what_function(char *cursor, int *end){

	//array of all fucntinos
	char functions[4][10] = {"sin", "cos", "abs", "log"};
	int size = 4;

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

//Convert char to 1digit int;
int char_to_int(char c){
	return c-'0';
}

//Creates an integer written as an array of char. 
//It evaluates from right ot left form the given starting point or '.' for decimal
int string_to_int(char *start){
	//to start form a number not th inputed char
	start--;

	//preperation
	int num = 0;
	for(int i=0; is_num(*start); i++, start--){
		num += char_to_int(*start) * pow(10, i);
		*start = 0;
	}

	return num;
}

//Evaualtes the decimal point numbers form '.' to the right.
//Number is given as an array of char.
double string_to_decimal(char *start){
	//put strat to the start of the decimal
	start++;

	//preperation
	double num = 0.0;
	for(int i=1; is_num(*start); i++, start++){
		num += char_to_int(*start) * pow(10, -i);
		*start = 0;
	}

	return num;
}

//converting a char to double
//Takes in the adress of the first or last dig depending on direction
double convert_to_num(char *adress, Direction DIR){
	printf("%c---\n", *adress);
	char *cursor = adress;
	int num = 0;
	double decimal = 0;

	switch(DIR){
		case RIGHT:
			//while finds the '.' int the number
			while(is_num(*cursor)){
				cursor++;
			}
			//find the integer and decimal part of a number from '.'
			if(*cursor =='.'){
				//making the '.' an '\0'
				*cursor = 0;
				num = string_to_int(cursor);
				decimal = string_to_decimal(cursor);
			}else{
				//if there is no '.' it means there is only an integer
				//you start from the end where the courso is right now
				num = string_to_int(cursor);
			}
			
			break;
		case LEFT:
			//while finds the '.' int the number
			while(is_num(*cursor)){
				cursor--;
			}
			//find the integer and decimal part of a number from '.'
			if(*cursor =='.'){
				*cursor = 0;
				num = string_to_int(cursor);
				decimal = string_to_decimal(cursor);
			}else{
				//if there is no '.' it means there is only an integer
				//you strat from the binary operation
				num = string_to_int(adress+1);
				//there is adress+1 because the adress is at the number 
				//and not at the operator
			}
			break;
		default:
			printf("Error!\nThere is no such direction!\n");	
	}

	//add the int and dec parts
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
			cursor++;
			while(*cursor != ')'){
				if(*cursor >= condition && *cursor <= c && *cursor != 'x'){
					printf("Cursor at: %c\n", *cursor);
					return cursor;
				}
				cursor++;
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
	
	//seeting the type value and index of node
	output[index].type = *adress;
	output[index].value = *adress;
	output[index].index = index;

	//declaring a cursor witch will be needed to dertermine 
	//the reight and the left values from the operator
	char *cursor;

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
	}else if(right_char >= 'a' && right_char <= 'z'){
		int end;
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
					break;
				case 1:
					node->result = cos(node->px[0]);
					break;
				case 2:
					node->result = fabs(node->px[0]);
					break;
				case 3:
					node->result = log(node->px[0]);
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
	// char array[40] = "((x+2^4*x/1)+1+(4+x)-x)";
	// char array[40] = "(sin(-x))";
	// char array[40] = "(cos(x+2)+sin(x))";
	char array[40] = {'('};
	double x = 2;
	Node operations[20] = {0};


	int i = 1;
	char c;
	printf("Write your fucntion: ");
	scanf("%c", &c);
	while(c != '\n'){
		array[i] = c;
		i++;
		scanf("%c", &c);
	}
	array[i] = ')';
	print_array(array, 40);

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

	
