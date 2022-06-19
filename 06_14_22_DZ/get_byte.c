#include <stdio.h>

#define REG 0xDDCCBBAA  // Register value

int main()
{
	int i;
	for(i = 0; i < 4; ++i){ // Output each byte.
		printf("0x%08X\n", (REG >> 8*i)& 0xFF);
	}
	printf("0x%08X\n\n",(REG & ~(0xFF << 8*2)) | (0xEE << 8*2)); // Ñhange third byte and output register.
	
	return 0;
}
