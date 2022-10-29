#include <stdio.h>

//Prints array in array format
void print_char_array(char *array, size_t size){
	printf("{");
	for(int i=0; i<size-1; i++){
		printf("%c, ", array[i]);
	}
	printf("%c}\n", array[size-1]);
}

void input_char_array(char *array){
	array[0] = '(';
	char c;
	printf("Write your fucntion: ");
	scanf("%c", &c);
	int i = 1;
	while(c != '\n'){
		array[i] = c;
		i++;
		scanf("%c", &c);
	}
	array[i] = ')';
	print_char_array(array, 40);
}