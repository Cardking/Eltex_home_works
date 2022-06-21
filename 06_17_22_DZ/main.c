#include "headers/katalog.h"

enum options {add, find, del, show, out};

int main()
{
	int ch;
	char flag;
	struct katalog ktlog;
	ktlog_init(&ktlog);
	do{
		flag = 1;
		printf( "\nMenu\n" );
	    printf( "%d. Add;\n", add);
	    printf( "%d. Find;\n", find);
	    printf( "%d. Delete;\n", del);
	    printf( "%d. Show;\n", show);
	    printf( "%d. Exit;\n", out);
	   
		printf("Enter menu option: ");
		scanf("%d", &ch);
		getc(stdin);
		switch(ch){
			case add:
				ktlog_add(&ktlog);
				break;
			case find:
				ktlog_find(&ktlog);
				break;
			case del:
				ktlog_delete(&ktlog);
				break;
			case show:
				ktlog_show(&ktlog);
				break;
			case out:
				flag = 0;
				break;
			default:
				break;
		}
		
		
	} while(flag);
	
	return 0;
}













