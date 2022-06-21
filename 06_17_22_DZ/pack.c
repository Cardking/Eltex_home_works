#include <stdio.h>

// Struct with padding
struct test{
	char a;
	int b;
};
// Struct with packing
#pragma pack(push, 1)
struct test_packed {
	char a;
	int b;
};
#pragma pack(pop)

int main()
{
	int i; // Iterators
	struct test* str1;
	struct test_packed* str2;
	char mass[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};
	str1 = (struct test*) mass;
	str2 = (struct test_packed*) mass;
	
	printf("%ld\n", sizeof(struct test));
	printf("%ld\n\n", sizeof(struct test_packed));
	
	printf("Test out\n\t");
	for(i = 0; i < 2; ++i){ // Output struct array with padding
		printf("%c", str1[i].a);
		printf("%d", str1[i].b);
	}
	printf("\nTest packed out:\n\t");
	for(i = 0; i < 2; ++i){ // Output struct array with packing
		printf("%c", str2[i].a);
		printf("%d", str2[i].b);
	}
	printf("\n\n");
	
	return 0;
}













