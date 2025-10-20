#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

/* Race condition:
 * threads are interleaved
 * threads read/write same memory address, 
 * 		causing inconsistencies
 * */

int accum = 0;

void* square(void* x) {
    int xi = (int)x;
    accum += xi * xi;
    return NULL;
}

int main(int argc, char** argv) {
    int i;
    pthread_t ths[20];
    for (i = 0; i < 20; i++) {
        pthread_create(&ths[i], NULL, square, (void*)(i + 1));
    }

    for (i = 0; i < 20; i++) {
        void* res;
        pthread_join(ths[i], &res);
    }

	// On running
	// for i in {1..4000}; do ./a.out; done
	// This will be printed several times
	if (accum != 2870) {
		printf("accum = %d\n", accum);
	}
    return 0;
}
