#include <dlfcn.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define N 10
#define BUF_SIZE 50
//#define TEST
//#define TEST2

int main()
{
	int i, j, k;
	int dl_n = 0;
	
	char *err_str = NULL;
	char buf[2*BUF_SIZE+3];
	FILE *fplugins = NULL;
	
	int (*dl_func_ptr)(int) = NULL;
	void *dl_ptr = NULL;
	const char** op_name = NULL;
	
	//Plugins file open.
	fplugins = fopen("plugins.txt", "r");
	if(fplugins == NULL){
		printf("ERROR: No file, %d\n", errno);
		exit(1);
	}
	
	//Plugin names reading.
	for(i = 0; !(feof(fplugins)); ++i){
		fgets(buf, BUF_SIZE, fplugins);
	}
	dl_n = i;
	char dl_names[dl_n][BUF_SIZE];
	fseek(fplugins, 0, SEEK_SET);
	for(i = 0; !(feof(fplugins)); ++i){
		fgets(buf, BUF_SIZE, fplugins);
		k = 0;
		while(isspace(buf[k])) ++k;
		for(j = 0; buf[k+j] != '\0'; ++j){
			if(isspace(buf[k+j])){
				break;
			}
			dl_names[i][j] = buf[k+j];
		}
		dl_names[i][j] = '\0';
	}
	
	//Empty names cutting off.
	for(i = 0; i < dl_n; ++i){
		if(dl_names[i][0] == '\0'){
			strcpy(dl_names[i], dl_names[dl_n-1]);
			--dl_n;
			--i;
		}
	}
	
	#ifdef TEST2
		printf("dl number: %d\n", dl_n);
	#endif
	//Libraries check.
	char dl_sel_list[dl_n];
	int temp;
	
	for(i = 0; i < dl_n; ++i){
		dl_sel_list[i] = 1;
	}
	//--Lib and simbols existence check.
	for(i = 0; i < dl_n; ++i){
		sprintf(buf, "lib/%s.so", dl_names[i]);
		dl_ptr = dlopen(buf, RTLD_LAZY);
		if(dl_ptr == NULL){
			err_str = dlerror();
			printf("%s\n", err_str);
			dl_sel_list[i] = 0;
			continue;
		} else {
			dl_func_ptr = dlsym(dl_ptr, dl_names[i]);
			if(dl_func_ptr == NULL){
				err_str = dlerror();
				printf("%s\n", err_str);
			}
			op_name = dlsym(dl_ptr, "op_name");
			if(op_name == NULL){
				err_str = dlerror();
				printf("%s\n", err_str);
			}
		}
		dlclose(dl_ptr);
	}
	//--Delete not exist libs.
	for(i = 0; i < dl_n; ++i){
		if(dl_sel_list[i] == 0){
			temp = dl_sel_list[i];
			dl_sel_list[i] = dl_sel_list[dl_n-1];
			dl_sel_list[dl_n-1] = temp;
			strcpy(buf, dl_names[i]);
			strcpy(dl_names[i], dl_names[dl_n-1]);
			strcpy(dl_names[dl_n-1], buf);
			--dl_n;
			
			while(dl_sel_list[dl_n-1] == 0) --dl_n;
			--i;
		}
	}
	
	#ifdef TEST2
		printf("dl number: %d\n", dl_n);
	#endif
	//Libraries selection.
	for(i = 0; i < dl_n; ++i){
		dl_sel_list[i] = 0;
	}
	printf("\nLibs list:\n");
	for(i = 0; i < dl_n; ++i){
		printf("%3d. %s\n", i+1, dl_names[i]);
	}
	printf("Enter numbers separated by spaces, "
	 "negative values - delete.\n");
	printf("Press 'Enter' when finished.\n");
	
	int num;
	int flag = 1;
	do{
		printf("Input: ");
		fgets(buf, BUF_SIZE, stdin);
		i = 0;
		if(buf[0] == '\n'){
			flag = 0;
			break;
		}
		
		while(buf[i] != '\0'){
			num = atoi(buf+i);
			if(num == 0){
				#ifdef TEST
					printf("n_num:%d ", num);
				#endif
				while(buf[i] != '\0'){
					if((buf[i] == '-') || (buf[i] == '+')){
						if(isdigit(buf[i+1])){
							break;
						}
					}
					if(isdigit(buf[i])){
						break;
					}
					++i;
				}
			} else {
				#ifdef TEST
					printf("num:%d ", num);
				#endif
				if(num >= -dl_n && num <= dl_n && num != 0){
					if(num > 0){
						dl_sel_list[num-1] = 1;
					} else {
						dl_sel_list[-num-1] = 0;
					}
				}
				while((isdigit(buf[i]) || buf[i] == '-'\
				 || buf[i] == '+') && buf[i] != '\0') ++i;
				while(isspace(buf[i])) ++i; 
			}
		}
		
		printf("Selected: ");
		for(i = 0; i < dl_n; ++i){
			if(dl_sel_list[i]){
				printf("%d ", i+1);
			}
		}
		printf("\n\n");
	}while(flag);
	
	#ifdef TEST2
		printf("dl number: %d\n", dl_n);
	#endif
	//Not selected dl cutting off.
	for(i = 0; i < dl_n; ++i){
		if(dl_sel_list[i] == 0){
			#ifdef TEST2
				printf("%d -- %d | ", i, dl_n);
			#endif
			temp = dl_sel_list[i];
			dl_sel_list[i] = dl_sel_list[dl_n-1];
			dl_sel_list[dl_n-1] = temp;
			strcpy(buf, dl_names[i]);
			strcpy(dl_names[i], dl_names[dl_n-1]);
			strcpy(dl_names[dl_n-1], buf);
			--dl_n;
			
			while(dl_sel_list[dl_n-1] == 0 && dl_n > 0) --dl_n;
			--i;
			#ifdef TEST2
				printf("%d -- %d\n", i, dl_n);
			#endif
		}
	}
	
	#ifdef TEST2
		printf("dl number: %d\n", dl_n);
	#endif 
	void * dl_ptr_arr[dl_n];
	int (*dl_func_ptr_arr[dl_n])(int, int);
	const char* op_name_arr[dl_n];
	
	for(i = 0; i < dl_n; ++i){
		//Lib opening.
		sprintf(buf, "lib/%s.so", dl_names[i]);
		dl_ptr_arr[i] = dlopen(buf, RTLD_LAZY);
		if(dl_ptr_arr[i] == NULL){
			err_str = dlerror();
			printf("%s\n", err_str);
			exit(EXIT_FAILURE);
		} else {
			// Find function.
			dl_func_ptr_arr[i] = dlsym(dl_ptr_arr[i], dl_names[i]);
			if(dl_func_ptr_arr[i] == NULL){
				err_str = dlerror();
				printf("%s\n", err_str);
			}
			// Find operation name.
			op_name_arr[i] = dlsym(dl_ptr_arr[i], "op_name");
			if(op_name_arr[i] == NULL){
				err_str = dlerror();
				printf("%s\n", err_str);
			}
		}
	}
	
	int ch; // Choice variable.
	int result, first_num, second_num; // Calculation variables.
	
	flag = 1;
	do{
		// Menu print.
		printf( "\n-Menu-\n" );
		for(i = 0; i < dl_n; ++i){
			printf("%3d. %s\n", i+1, op_name_arr[i]);
		}
		printf("%3d. %s\n", 0, "Exit");
		
		// Get params.
		do {
			printf("Enter menu option: ");
			fgets(buf, N, stdin);
			ch = atoi(buf);
		} while(!(ch >= 0 && ch <= dl_n));
		if(ch != 0){
			printf("Enter first number: ");
			fgets(buf, N, stdin);
			first_num = atoi(buf);
			printf("Enter second number: ");
			fgets(buf, N, stdin);
			second_num = atoi(buf);
		} else {
			flag = 0;
			break;
		}
		// Calculation.
		result = dl_func_ptr_arr[ch-1](first_num, second_num);
		printf("%s result: %d\n", op_name_arr[ch-1], result);
	} while(flag);
	printf("\n\n");
	
	//Closing.
	fclose(fplugins);
	for(i = 0; i < dl_n; ++i){
		dlclose(dl_ptr_arr[i]);
	}
	
	return 0;
}













