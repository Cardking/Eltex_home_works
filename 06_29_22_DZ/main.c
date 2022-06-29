#include "headers/calc.h"
#include <stdlib.h>
#define N 10
enum options {my_add = 1, my_sub, my_mul, my_div, my_out};

int main()
{
	int ch; // Choice variable.
	int result, first_num, second_num; // Calculation variables.
	char flag; // Loop out flag.
	char buf[N+2]; // Input buffer.
	
	do{
		flag = 1;
		// Menu print:
		printf( "\n-Menu-\n" );
		printf( "%d. Addition;\n", my_add);
		printf( "%d. Subtraction;\n", my_sub);
		printf( "%d. Multiplication;\n", my_mul);
		printf( "%d. Division;\n", my_div);
		printf( "%d. Exit;\n", my_out);
		
		do {
			printf("Enter menu option: ");
			fgets(buf, N, stdin);
			ch = atoi(buf);
		} while(!(ch >= my_add && ch <= my_out));
		if(ch != my_out){
			printf("Enter first number: ");
			fgets(buf, N, stdin);
			first_num = atoi(buf);
			printf("Enter second number: ");
			fgets(buf, N, stdin);
			second_num = atoi(buf);
		}
		//scanf("%d", &ch);
		//getc(stdin); // Output missed \n from stdin buffer.
		switch(ch){
			case my_add:
				result = calc_add(first_num, second_num);
				printf("Addition result: %d",result);
				break;
			case my_sub:
				result = calc_sub(first_num, second_num);
				printf("Subtraction result: %d",result);
				break;
			case my_mul:
				result = calc_mul(first_num, second_num);
				printf("Multiplication result: %d",result);
				break;
			case my_div:
				result = calc_div(first_num, second_num);
				printf("Division result: %d",result);
				break;
			case my_out:
				flag = 0;
				break;
			default:
				break;
		}
	} while(flag);
	printf("\n");
	
	return 0;
}













