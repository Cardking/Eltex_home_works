#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#define N 10

int main()
{
	int a = 5;
	int result = a;
	char *err_str = NULL;
	int (*dl_func_ptr)(int) = NULL;
	
	void *dl_ptr = NULL;
	dl_ptr = dlopen("lib/dl_func.so", RTLD_LAZY);
	if(dl_ptr == NULL){
		err_str = dlerror();
		printf("%s\n", err_str);
		exit(EXIT_FAILURE);
	}
	dl_func_ptr = dlsym(dl_ptr, "dl_func");
	if(dl_func_ptr == NULL){
		err_str = dlerror();
		printf("%s\n", err_str);
		dlclose(dl_ptr);
		exit(EXIT_FAILURE);
	}
	result = dl_func_ptr(a);
	
	printf("%d\n", result);
	
	dlclose(dl_ptr);
	return 0;
}













