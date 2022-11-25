#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "charlib.h"
#include "nodelib.h"

/*
	Parameter: array and the size
	Return: None
	It prints the array in the console. The format:
    { elm1, elm2,...., elmN }
*/
void print_char_array(char *array, size_t size){
	printf("{");
	for(int i=0; i<size-1; i++){
		printf("%c, ", array[i]);
	}
	printf("%c}\n", array[size-1]);
}

/*
	Parameter: destination array, source array, size of source
	Return: None
	It copies the source array into the destination array.
	The destination array should be bigger.
*/
void copyarr(char* destination, char* source, size_t size_source){
	for(int i=0; i<size_source; i++){
		destination[i] = source[i];
	}
}

/*	
	Parameter: Pointer the the size
	Return: 
	-Dynamically allocated char array.
	-NULL if the array coudn't allocate.
	-Size of this array into the size pointer.
	Asks the user to input the mathematical expression 
	and dynamically allocates the char array for the 
	expression. Returns the pointer to the array.
	The format of the array created: {'(' expression ')'}.
*/
char *take_expression(size_t *size){
	/*preperation*/
	system("clear");
	size[0] = 1;
	char c;

	/*Creating the array*/
	char *expression = (char *)malloc(sizeof(char)*size[0]);
	if(expression == NULL) return NULL;
	expression[0] = '(';

	/*Asking the user*/
	printf("Enter the function: ");

	/*Inputing the expression into the array*/
	while(scanf("%c", &c) == 1 && c != '\n'){
		//Removing the spaces
		if(c == ' '){
			continue;
		} 
		/*Extending the array.*/
		/*+2: 1 for newchar and 1 for ')'*/
		char *newArr = (char *)malloc(sizeof(char)*(size[0]+2));
		if(newArr == NULL){
			printf("Error: The array couldn't dynamically allocate!");
			return NULL;
		}
		/*Coping the previous array to the newone*/
		copyarr(newArr, expression, size[0]);
		/*Putiong the newchar in */
		newArr[*size] = c;
		/*Freeing the previos array */
		free(expression);
		/*Making it point tho the new one*/
		expression = newArr;
		/*The size increased by one*/
		size[0]++;
	}
	/*Putting and ')' at the and for the format*/
	expression[size[0]] = ')';

	/*compesatig for +2*/
	size[0]++;
	/*printf("Size of expression: %ld\n", size[0]);*/
	/*print_char_array(expression, size[0]);*/

	return expression;
}

/*
	It checks if the user has eneterd valid parameters
*/
int is_expression_valid(char *expression, size_t size){

	/*cheking if it is empty size>2*/
	if(!(size>2)){
		printf("ERROR! You wrote nothing!\n");
		return 0;	
	}
	
	/*Using one loop to chechk the conditions (more efficient)*/
	/*Preperation*/
	int number_of_openbracket = 0;
	int number_of_closebracket = 0;
	for(int i = 0; i<size; i++){
		//printf("i is at :%c\n", expression[i]);
		//Chechking if the number of closing and opening brackets is the same
		//If they are not than expression not valid
		if(expression[i] == '('){
			number_of_openbracket++;
		}else if(expression[i] == ')'){
			number_of_closebracket++;
		}
		//printf("( %d ) %d\n", number_of_openbracket, number_of_closebracket);

		//Chechking if operations are one after the other
		//Example: 3*+4 (this is not valid expression)
		if(is_binary_operator(expression[i]) && is_binary_operator(expression[i+1])){
			printf("ERROR! You have two binary operations one after the other!\n");
			return 0;
		}

		//Chechking if user inputed a valid is fucntion (small letter)
		if(is_letter(expression[i], 'x')){
			//what_fucntion returns 0 for invalid functions
			//printf("%c", *(expression+i));
			//printf("%d\n", what_function(expression+i));
			if(!what_function(expression+i)){
				printf("ERROR! You may have spelling mistakes or inputted a which is not a function\n");
				return 0;
			}
			//to go to the end of the function.
			while(is_small_letter(expression[i],'(')){
				//printf("inside the while\n");
				i++;
			}
			i--; //to not get i++ from the for loop
		}
		//(1) => (1.0) becuase it is a node identifier
		if(expression[i-2] == '('&& is_num(expression[i-1]) && expression[i] == ')'){
			printf("Error! You can't have a (%c). Make it (%c.0)!\n", expression[i-1], expression[i-1]);
			return 0;
		}
		//3x => (3x)
		if(expression[i-3] != '(' && is_num(expression[i-2]) && expression[i-1] == 'x' && expression[i] != ')'){
			printf("Error! You entered %cx without parantheses! Try (%cx)\n", expression[i-2], expression[i-2]);
			return 0;
		}
	}

	if(number_of_openbracket != number_of_closebracket){
		printf("ERROR! You didn't close a bracket!\n");
		return 0;
	}

	if(!number_of_nodes_in_expression(expression, size)){
		printf("Error! There are no nodes. If you entered jus a plan number try <num> => +<num>\n");
		return 0;
	}

	return 1;
}	

/*		
	Parameters:
    - size    |is the pointer to the size of the array
 
	Returns:
	- expression    | imputed by the user as a dynamically allocated 
					| char array
	- size        	| of the char array (pointer)
 
	Usage:
	Uses the take_expression() function to take expression form the user and 
	then uses the is_expression_valid() function to check if the user imputed 
	a valid input. If not it loops until the user enters a valid expression. 
	When the user enters a valid input it returns the dynamically allocated 
	array of the expression.
*/
char *take_valid_expression(size_t *size){
	//preperation
	char *expression = take_expression(size);
	int valid = is_expression_valid(expression, *size);

	//Check validity if not, clear and repeat
	while(valid == 0){
		//free the expression 
		free(expression);

		printf("Press Enter to continue...");
		//Waiting for the enter
		char c;
		while(scanf("%c", &c) == 1 && c != '\n'){}

		//take expression from user
		expression = take_expression(size);
		//Check for bad memory allocation
		if(expression == NULL){
			printf("ERROR! The memory cound't be allocted!\n"
				   "Check if you have enough memory in your device.");
			return NULL;
		}

		//validitate
		valid = is_expression_valid(expression, *size);
		//print_char_array(expression, *size);
	}

	return expression;
}