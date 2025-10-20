#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// * compile with -lpthread
//
// int pthread_join(pthread_t thread, void **retval);
// int pthread_create(pthread_t *restrict thread, 
//  			const pthread_attr_t *restrict attr, 
//  			typeof(void *(void *)) *start_routine,
//  			void *restrict arg);


// Thread functions are of type void*
void* func(void* x) {
	int xi = (int)x;
	while (xi < 107) {
		xi++;
		printf(" thread func - x = %d\n", xi);
	}
	return (void*)(xi);
}

int main(int argc, char** argv) {
	pthread_t th;
	pthread_create(&th, NULL, func, (void*)100);

	printf("on thread\n");
	void* ret_from_thread;
	int ri;
	pthread_join(th, &ret_from_thread);
	ri = (int)ret_from_thread;

	printf("on main after thread returned %d\n", ri);
	return 0;
}
