#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define NUM_THREADS 2
#define MAX_COUNT 17

// shared data
int count;
pthread_mutex_t count_lock;
pthread_cond_t count_cond;

void *
thr_func_1(void *arg)
{
	pthread_mutex_lock(&count_lock);
		printf("putting thread to sleep, waiting on signal\n");
		while (count < MAX_COUNT)
			pthread_cond_wait(&count_cond, &count_lock);
		printf("thread awoken. value of `count` is %d\n", count);
	pthread_mutex_unlock(&count_lock);

	pthread_exit(NULL);
}

// this thread signals a waiting thread
void *
thr_func_2(void *arg){

	pthread_mutex_lock(&count_lock);
		while (count < MAX_COUNT) {
			printf("`count` variable value: %d\n", count);
			count++;
		}
		printf("condition met lock released by signaling thread\n");
	pthread_mutex_unlock(&count_lock);

	pthread_cond_signal(&count_cond);

	return NULL;
}


int
main(int argc, char **argv)
{
	int i, rc;
	pthread_t thr[NUM_THREADS];

	pthread_mutex_init(&count_lock, NULL);
	pthread_cond_init(&count_cond, NULL);

	pthread_create(&thr[0], NULL, thr_func_1, NULL);
	pthread_create(&thr[1], NULL, thr_func_2, NULL);

	// block until all threads complete
	for (i = 0; i < NUM_THREADS; ++i)
		pthread_join(thr[i], NULL);

	return (EXIT_SUCCESS);
}
