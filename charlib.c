#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "cursorlib.h"

/*
	Takes the pointer to the first letter of the function
	and returns the value of the fucntion.
	Every fucntion has a value which is determined by the 
	index position in the function array.
	End input puts the cursor at the end of the fucntion
*/
int what_function(char *cursor){
	//array of all fucntinos. Max char size is 10.
	char functions[6][10] = {"nofunc" ,"sin", "cos", "abs", "log", "exp"};

	//geting the function string
	char function[10];
	int i;
	//i<9 is checked so we don't overflow (9 because '\0')
	for(i = 0; cursor[i] != 0  && cursor[i] != ')' && i<9; i++){
		function[i] = cursor[i];
	}
	function[i] = '\0';
	//printf("function: %s\n", function);

	//checking if it maches with any of our fucntions in the array of fucntions
	for(int i = 0; i < 6; i++){
		//printf("String compare: %d\n", strcmp(func, functions[i]));
		if(!strcmp(function, functions[i])){
			return i;
			/*The value i represent the index of the function in the array of functions
				sin=1 cos=2 abs=3 ... exp=5
			*/
		}
	}
	return 0;
}

int is_binary_operator(char c){
	switch(c){
		case '^': return 1;
		case '*': return 1;
		case '/': return 1;
		case '+': return 1;
		case '-': return 1;
	}
	return 0;
}

int is_small_letter(char c, char ommit){
	//Checking with ASCII if it is a letter
	//The char shouldn't be the ommited char
	if(c >= 'a' && c <= 'z' && c != ommit){
		return 1;
	}
	return 0;
}

/*
	Parameters: char value
	Returns:
	- 0    | if char isn’t a number character     [‘0’,‘9’]
	- 1    | if char is a number character        [‘0’,‘9’]
	Notes:
	[‘0’,‘9’] - means from ‘0’ to ‘9’ including ‘0’ and ‘9’.
	Usage:
	Takes the value of the char and checks if it is a char that represents a number. 
	In other words it checks if char is one of the char values ‘1’ through ‘9’.
	Example:
	‘7’ -> 1 (true)
	‘p’ -> 0 (false)
	‘3’ -> 1 (true)
*/
int is_num(char c){
	if(c >= '0' && c <= '9'){
		return 1;
	}
	return 0;
}

/*
	Parameters: char
 	Returns: one ditgit integer
	Usage:
	It takes the value of the char and converts it into corresponding int. 
	It converts the characters that represent the numbers from 1 to 9 to integer numbers. 
	Example:
	‘1’(char) -> 1(int) 
	‘8’(char) -> 8(int)
*/
int char_to_int(char c){
	//Using the ASCII talbe
	return c-'0';
}

/*
	Parameters:
	- start     | the pointer to the starting position of the 
				| integer in the expression. One before the 
				| starting digit. 
	Returns:
	- int       | the number that the string represent
	- ‘\0’      | the string that represented the number 
				| becomes all ‘\0’.

	Usage: 
	It takes the starting position of the string that represents the int number. 
	The starting position is one before the first digit starts. 
	I tranverses to the right until it hits a char that is not a number. 
	It returns the int. If we have a decimal number we use this function to find the integer part of that number.
	
	Example: 
	c is the starting char (not the first digit 0):
	{...‘+’,‘2’, ‘3’, ‘2’, ‘1’, ‘0’, ‘c’,...} 
									  ↑
	Traversing to the left:
	{...‘+’,‘2’, ‘3’, ‘2’, ‘1’, ‘0’, ‘c’,...} 	
									 ←↑
	{...‘+’,‘2’, ‘3’, ‘2’, ‘1’, ‘0’, ‘c’,...}  	 	| int = 0*10^0 = 0      
						  	    ←↑ 	
	{...‘+’,‘2’, ‘3’, ‘2’, ‘1’, ‘\0’, ‘c’,...}    	| int = 0 + 1*10^1 = 10
					 	   ←↑ 
				. . .
	{...‘+’,‘2’, ‘\0’, ‘\0’, ‘\0’, ‘\0’, ‘c’,...}   | int = 3210 + 2*10^4
		    ←↑          
	{...‘+’,‘\0’, ‘\0’, ‘\0’, ‘\0’, ‘\0’, ‘c’,...}  | int = 23210
		 ↑ 
	Not a number (in our case the +) it stops.
	It returns the number 23210. If we have a decimal number we use this function to find the integer part of that number. In this case the starting char is the dot. 
	Example:
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘0’, ‘c,...}
					   ↑ 
	‘.’ is the starting char. 
	It will transverse until it hits the ‘-’ and it will return 23.
*/
int string_to_int(char *start){
	/* Preperaion */
	start--; 	//start for frist digit
	int num = 0;
	
	for(int i=0; is_num(start[-i]); i++){
		num += char_to_int(*start) * pow(10, i);
		start[-i] = '\0';		//Make the int string to '\0'
	}

	//printf("num: %d\n", num);
	return num;
}

/*
	Parameters:
	- start     | the pointer to the starting position of the
				| Decimal part in the expression. Usually is the 
				| ‘.’ but can be any char.
	Returns:
	- the “decimal” 	| the numbers after ‘.’ in the decimal 
						| representation
	- ‘\0’           	| the string that represented the number 
						| becomes all ‘\0’.

	
	Usage:
	Usually we take the position of the dot and compute the decimal number to the right until it hits a char that is not a number. It returns the value after the ‘.’. 
	
	Example:
	The dot is the starting position:
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘6’, ‘c,...}
					   ↑ 
	Transverses to the right:
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘6’, ‘c,...}
					   ↑→ 
	Evaluates:
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘6’, ‘c,...}    | dec = 1*10^(-1) = 0.1
						 	↑→
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘6’, ‘c,...}    | dec = 0.1 + 6*10^(-2)
								 ↑→
	It hits a char that is not a number. It stopes:
	{...‘-’,‘2’, ‘3’, ‘.’, ‘1’, ‘6’, ‘c,...}    | dec = 0.16
									  ↑→
	It returns the 0.16 decimal number.
*/
double string_to_decimal(char *start){
	/* Preperation */
	start++; //start from first digit
	double num = 0.0;

	for(int i=0; is_num(start[i]); i++){
		num += char_to_int(*start) * pow(10, -i);
		start[i] = '\0';	//Make the dec string to '\0'
	}

	//printf("num: %f\n", num);
	return num;
}

//converting a char to double
//Takes in the adress of the first or last dig depending on direction
double convert_to_num(char *adress, Direction DIR){
	// printf("%c\n", *adress);
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
	//printf("Number: %f\n", num+decimal);
	return num+decimal;
}

int is_variable_multiplicaton(char *cursor){
 	/*	  
 		We chechk for (<num>x) or (x)
						    ↑	   ↑		 
			             cursor is at x	
	*/
	if((is_num(cursor[-1]) || (cursor[-1] == '(')) && cursor[1] == ')'){
		return 1;
	}
	return 0;
}

