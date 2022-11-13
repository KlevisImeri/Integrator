#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
	Parameter: array and the size
	Return: None
	Prints array in array format in the console
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
	Array format: {'(' expression ')'}
*/
char *take_expression(size_t *size){
	//preperation
	size[0] = 1;
	char c;
	//clering scanf from any unwated '\n'
	while(scanf("%c", &c) == 1 && c != '\n'){};

	//Creating the array
	char *expressionArr = (char *)malloc(sizeof(char)*size[0]);
	//if(expressionArr == 0) return NULL;
	expressionArr[0] = '(';

	//Asking the user
	printf("Enter the function: ");

	//Inputing the expression into the array
	while(scanf("%c", &c) == 1 && c != '\n'){
		//Removing the spaces
		if(c == ' '){
			continue;
		} 
		//Extending the array. 
		//+2: 1 for newchar and 1 for ')'
		char *newArr = (char *)malloc(sizeof(char)*(size[0]+2));
		if(newArr == 0){
			printf("Error: The array couldn't dynamically allocate!");
			return NULL;
		}
		//Coping the previous array to the newone
		copyarr(newArr, expressionArr, size[0]);
		//Putiong the newchar in 
		newArr[*size] = c;
		//Freeing the previos array 
		free(expressionArr);
		//Making it point tho the new one
		expressionArr = newArr;
		//The size increased by one
		size[0]++;
	}
	//Putting and ')' at the and for the format
	expressionArr[size[0]] = ')';

	//compesatig for +2
	size[0]++;
	//print_char_array(expressionArr, size[0]);
	//printf("Size of expression: %ld\n", size[0]);
	return expressionArr;
}
