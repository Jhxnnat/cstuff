#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define GOAL 999999999

void* threadfunc(void* arg) {
	int count = 0;
	while (count < GOAL) count++;
	return NULL;
}

void normalfunc() {
	int count = 0;
	while (count < GOAL) count++;
}

int main(void) {
	int value = 0;
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, threadfunc, NULL);
	threadfunc(NULL);
	pthread_join(new_thread, NULL);
	return 0;
}
