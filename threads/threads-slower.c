#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

/* Threads count being slower
 * reasons: 
 * 		memory sharing
 *
 * */

#define VALUE 9999999

void normalfunc(int* value) {
	for(int i=0; i<VALUE; ++i){
		(*value)++;
	}
	printf("Normal function - value: %d\n", *value);
}

void* threadfunc(void* arg) {
	int *ipt = (int *)arg;
	for(int i=0; i<VALUE; ++i){
		(*ipt)++;
	}
	printf("Thread function - value: %d\n", *ipt);
	return NULL;
}

void thread_case() {
	int value = 0;
	int thread_num = 12;
	pthread_t threads[thread_num];
	for (int i=0; i<thread_num; ++i) {
		pthread_create(&threads[i], NULL, threadfunc, &value);
	}
	for (int i=0; i<thread_num; ++i) {
		pthread_join(threads[i], NULL);
	}
}

void no_thread_case() {
	int value = 0;
	normalfunc(&value);
	normalfunc(&value);
}

int main(void) {
	printf(" == no_thread_case ==\n");
	clock_t start = clock();
	no_thread_case();
	clock_t end = clock();
	float seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf(" == sec: %f", seconds);

	// different result; slower
	printf("\n\n == thread_case ==\n");
	start = clock();
	thread_case();
	end = clock();
	seconds = (float)(end - start) / CLOCKS_PER_SEC;
	printf(" == sec: %f", seconds);
}
