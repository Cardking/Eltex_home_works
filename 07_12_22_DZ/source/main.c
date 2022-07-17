#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>


#define N 5
#define BUYER_N 3
#define ARGC 5
//#define TEST

enum arg_type {shops_c = 0, muts_c, lef_c, tnum_c, tnum_mut_c};

void *buyer_func(void *argv);
void *loader_func(void *argv);


int main()
{
	int i; // Iterators.
	int shops[N]; // Stores balance.
	int loader_end_flag = 0, tnum = 1;
	pthread_t tids[BUYER_N], loader_tid; // Thread ids.
	pthread_attr_t attr;
	pthread_mutex_t muts[N]; // Mutexes.
	pthread_mutex_t tnum_mut = PTHREAD_MUTEX_INITIALIZER;
	void *argv[ARGC]; // Args pointer.
	
	// Attributes setting.
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	// Shops start balance, mutexes initialization.
	srand(time(NULL));
	for(i = 0; i < N; i++){
		shops[i] = 490 + rand()%21;
		#ifdef TEST
			shops[i] = 20000;
		#endif
		pthread_mutex_init(&muts[i], NULL);
	}
	// Mutexes check.
	for(i = 0; i < N; i++){
		if(pthread_mutex_lock(&muts[i]) == EINVAL){
			perror("ERROR");
			exit(errno);
		}
		pthread_mutex_unlock(&muts[i]);
	}
	if(pthread_mutex_lock(&tnum_mut) == EINVAL){
		perror("ERROR");
		exit(errno);
	}
	pthread_mutex_unlock(&tnum_mut);

	argv[shops_c] = shops;
	argv[muts_c] = muts;
	argv[lef_c] = &loader_end_flag;
	argv[tnum_c] = &tnum;
	argv[tnum_mut_c] = &tnum_mut;

	// Buyers thread create.
	for(i = 0; i < BUYER_N; i++){
		if(pthread_create(&tids[i], &attr, buyer_func, argv)){
			perror("ERROR");
			exit(errno);
		}
	}
	
	// Loader thread create.
	if(pthread_create(&loader_tid, &attr, loader_func, argv)){
		perror("ERROR");
		exit(errno);
	}
	
	for(i = 0; i < BUYER_N; i++){
		pthread_join(tids[i], NULL);
	}
	loader_end_flag = 1;
	pthread_join(loader_tid, NULL);
	
	for(i = 0; i < N; i++){
		printf("Shop-%d: %d\n", i+1, shops[i]);
	}
	
	// Clean up.
	for(i = 0; i < N; i++){
		pthread_mutex_destroy(&muts[i]);
	}
	pthread_mutex_destroy(&tnum_mut);
	pthread_attr_destroy(&attr);
	
	return 0;
}

//================END_MAIN================//

void *buyer_func(void *argv){
	if(argv == NULL){
		exit(404);
	}
	
	unsigned int i, j;
	int need = 5000;
	int *shops = ((void**) argv)[shops_c];
	pthread_mutex_t *muts = ((void**) argv)[muts_c];
	int tnum;
	
	// Thread number assignment.
	pthread_mutex_lock(((void**) argv)[tnum_mut_c]);
	tnum = *(int*)((void**) argv)[tnum_c];
	(*(int*)((void**) argv)[tnum_c])++;
	pthread_mutex_unlock(((void**) argv)[tnum_mut_c]);
	
	// Shoping.
	for(i = 0; need > 0; ++i){
		j = i % N;
		if(pthread_mutex_trylock(&muts[j]) == EBUSY){
			continue;
		}
		if(shops[j] != 0){
			if((need - shops[j]) < 0){
				printf("| B%d | Need: %d | Shop[%d]: %d - %d -> %d\n",\
				 tnum, need, j+1, shops[j], need, shops[j]-need);
				shops[j] -= need;
				need = 0;
			} else {
				printf("| B%d | Need: %d | Shop[%d]: %d - %d -> %d\n",\
				 tnum, need, j+1, shops[j], shops[j], 0);
				need -= shops[j];
				shops[j] = 0;
			}
		}
		
		pthread_mutex_unlock(&muts[j]);
		//sleep(2);
		usleep(100);
	}
	
	pthread_exit(NULL);
}

void *loader_func(void *argv){
	if(argv == NULL){
		exit(404);
	}
	
	unsigned int i, j;
	int *shops = ((void**) argv)[shops_c];
	pthread_mutex_t *muts = ((void**) argv)[muts_c];
	int *end_flag = ((void**) argv)[lef_c];
	
	for(i = 0; *end_flag == 0; ++i){
		j = i % N;
		if(pthread_mutex_trylock(&muts[j]) == EBUSY){
			continue;
		}
		shops[j] += 500;
		printf("| L  | Shop[%d]: %d + 500 -> %d\n", j+1, shops[j] - 500,\
		 shops[j]);
		pthread_mutex_unlock(&muts[j]);
		//sleep(1);
		usleep(50);
	}
	
	pthread_exit(NULL);
}









