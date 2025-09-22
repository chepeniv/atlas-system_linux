#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define NUM_THREADS 8

// thread argument struct for thr_func()
typedef struct _thread_data_t
{
	int tid;
	double stuff;
} thread_data_t;

// shared data
double shared_x;
pthread_mutex_t lock_x;

// thread function
void *
thr_func(void *arg)
{
	thread_data_t *data = (thread_data_t *)arg;

	printf("thr_func(): thead id : %d\n", data->tid);

	// mutex workflow
	pthread_mutex_lock(&lock_x);
		// critical section
		shared_x += data->stuff;
		printf("x = %f\n", shared_x);
	pthread_mutex_unlock(&lock_x);

	pthread_exit(NULL);
}

int
main(int argc, char **argv)
{
	int i, rc;
	pthread_t thr[NUM_THREADS];
	thread_data_t thr_data[NUM_THREADS];

	shared_x = 0;
	pthread_mutex_init(&lock_x, NULL);

	// create threads
	for (i = 0; i < NUM_THREADS; ++i)
	{
		thr_data[i].tid = i;
		thr_data[i].stuff = (i + 1) * NUM_THREADS;

		if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i])))
		{
			fprintf(stderr, "error: pthread_create, rc: %d\n", rc);
			return (EXIT_FAILURE);
		}
	}

	// block until all threads complete
	for (i = 0; i < NUM_THREADS; ++i)
		pthread_join(thr[i], NULL);

	return (EXIT_SUCCESS);
}
