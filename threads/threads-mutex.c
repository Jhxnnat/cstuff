#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define GOAL 999999999
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* threadfunc(void* arg) {
	while (count < GOAL) {
		pthread_mutex_lock(&lock);
		count++;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}

void normalfunc() {
	while (count < GOAL) count++;
}

int main(void) {
	int value = 0;
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, threadfunc, NULL);
	threadfunc(NULL);
	pthread_join(new_thread, NULL);
	printf("Count: %d\n", count);
	return 0;
}
