#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// TODO: how to pass arguments

void normalfunc(int* value) {
	for(int i=0; i<3; ++i){
		sleep(2);
		(*value)++;
		printf("[%d] Normal function\n", i);
	}
}

void* threadfunc(void* arg) {
	int *ipt = (int *)arg;
	for(int i=0; i<7; ++i){
		sleep(1);
		printf("[%d] > Thread function - value: %d\n", i, *ipt);
	}
	return NULL;
}

int main(void) {
	int value = 0;
	pthread_t new_thread;

	pthread_create(&new_thread, NULL, threadfunc, &value);
	normalfunc(&value);

	pthread_join(new_thread, NULL);
	return 0;
}
