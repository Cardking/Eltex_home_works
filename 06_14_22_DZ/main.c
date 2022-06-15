#include <stdio.h>

#define N 5

void print_m(int* matrix, unsigned int n, unsigned int m){
	unsigned int i, j;
	for(i = 0; i < m; ++i){
		for(j = 0; j < n; ++j){
			printf("%d\t", matrix[n*i + j]);
		}
		printf("\n");
	}
}

int main()
{
	int i, j, num;
	int mass[N*N];
	
	printf("N: %d \n", N);
	//-------- 1 --------//
	printf("\t//-------- 1 --------//\n\n");
	for(i = 0; i < N*N; ++i){
		mass[i] = i + 1;
	}
	print_m(mass, N, N);
	printf("\n\n");
	
	
	//-------- 2 --------//
	printf("\t//-------- 2 --------//\n\n");
	for(i = 0; i < N; ++i){
		mass[i] = i + 1;
	}
	
	printf("IN: ");
	for(i = 0; i < N; ++i){
		printf("%d  ", mass[i]);
	}
	printf("\n");
	
	printf("OUT: ");
	for(i = 0; i < N; ++i){
		printf("%d  ", mass[N-i-1]);
	}
	printf("\n\n\n");
	
	
	//-------- 3 --------//
	printf("\t//-------- 3 --------//\n\n");
	for(i = 0; i < N; ++i){
		for(j = 0; j < N-i-1; ++j){
			mass[i*N + j] = 0;
		}
		for(; j < N; ++j){
			mass[i*N + j] = 1;
		}
	}
	print_m(mass, N, N);
	printf("\n\n");
	
	
	//-------- 4 --------//
	printf("\t//-------- 4 --------//\n\n");
	for(i = 0, num = 1; i < N/2 + N%2; ++i){
		for(j = i; j < N-i; ++j, ++num){ // left-to-right
			mass[i*N+j] = num;
		}
		for(j = i; j < N-1-i; ++j, ++num){ // top-to-bottom
			mass[(j+1)*N + N-i-1] = num;
		}
		for(j = i; j < N-1-i; ++j, ++num){ // right-to-left
			mass[N*(N-i)-j-2] = num;
		}
		//num += N-2;
		for(j = i; j < N-2*(i+1) +i ; ++j, ++num){ // bottom-to-top
			//fprintf(stderr, "%d\n", N*(N-i-2-j) + i);
			mass[N*(N-2-j) + i] = num;
		}
	}
	print_m(mass, N, N);
	printf("\n\n");
	
	return 0;
}













