#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

/*
 * Consumer Producer Problem:
 * ...
 * */

int c = 0;
bool done = false;

void* producer(void* unused) {
	int i;
	while(done);
	for (i = 0; i < 500; i++) c++;
	done = true;
	return NULL;
}

void* consumer(void* unused) {
	while (!done);
	while (c > 0) c--;
	return NULL;
}

int main(int argc, char** argv) {
	pthread_t prod, con;

	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&con, NULL, consumer, NULL);

	void* unused;
	pthread_join(prod, &unused);
	pthread_join(con, &unused);

	printf("Net: %d\n", c);
}
