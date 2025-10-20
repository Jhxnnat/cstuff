#include <pthread.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

/* Mutual Exclusion
 * 	some block may have to be executed one thread at a time
 * 	use mutex to encapsulate them
 * 
 * This can be used to avoid race-condition problems
 * */

#define TOTAL_COUNT 12000000000
#define NUM_THREADS 12

int64_t global_count = 0;
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

void* count_thread(void* arg) {
	int64_t _count = 0;
	while(_count < TOTAL_COUNT / NUM_THREADS) {
		_count++;
	}
	pthread_mutex_lock(&count_mutex);
	global_count += _count;
	pthread_mutex_unlock(&count_mutex);
    return NULL;
}

int main() {
    pthread_t threads[NUM_THREADS];
    clock_t start = clock();
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, count_thread, NULL)
    }
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    printf("count: %lld\n", global_count);
    printf("threads num: %d\n", NUM_THREADS);
    printf("seconds: %f\n", seconds);

    pthread_mutex_destroy(&count_mutex);
    return 0;
}
