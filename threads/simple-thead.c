#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void normalfunc() {
	int count = 0;
	while (count < 999999999) count++;
	printf("normal count: %d\n", count);
}

void* threadfunc(void* arg) {
	int count = 0;
	while (count < 999999999) count++;
	printf("thead count: %d\n", count);
	return NULL;
}

int main(void) {
	pthread_t new_thread;
	pthread_create(&new_thread, NULL, threadfunc, NULL);
	normalfunc();
	pthread_join(new_thread, NULL);
	return 0;
}
