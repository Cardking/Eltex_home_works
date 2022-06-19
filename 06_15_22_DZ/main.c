#include <stdio.h>

#define REG 0xDDCCBBAA // Register value.
#define R_SIZE sizeof(int) // Integer size.
#define BIG_ENDIAN_TEST 0 // Big-endian test for little-endian processors.

enum endian {big = 0, little = 1};

int main()
{
	unsigned char choice; // Byte order.
	unsigned int reg = 1; // Register variable.
	unsigned char *ptr = (unsigned char*)&reg; // Char pointer
	int i; // Iterators
	
	if (*ptr == 1){ // Byte order setting.
		choice = little;
	} else {
		choice = big;
	}
	reg = REG;
	
	if(BIG_ENDIAN_TEST && (choice == little)){
		unsigned char temp;
		for(i = 0; i < R_SIZE/2; ++i){ // Byte values reverse.
			temp = ptr[i];
			ptr[i] = ptr[R_SIZE-1-i];
			ptr[R_SIZE-1-i] = temp;
		}
		choice = big;
	}
	
	printf("\n");
	if(choice == little){
		printf("Little-endian\n");
		for(i = 0; i < R_SIZE; ++i){ // Output byte values in order.
			printf("\t 0x%08X \n", ptr[i]);
		}
		ptr[2] = 0xEE; // Change third byte.
		printf("\t 0x%08X \n", reg); // Output register value.
	} else {
		printf("Big-endian\n");
		for(i = 0; i < R_SIZE; ++i){ // Output byte values in order.
			printf("\t 0x%08X \n", ptr[R_SIZE-1-i]);
		}
		ptr[R_SIZE-1-2] = 0xEE; // Change third byte.
		printf("\t 0x%08X \n", reg); // Output register value.
	}
	printf("\n");
	
	return 0;
}













