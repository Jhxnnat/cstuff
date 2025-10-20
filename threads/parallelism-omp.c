#include <stdio.h>
#include <stdint.h>
#include <omp.h>

int main() {
    int64_t total = 120000000;
    int count = 0;

    double start_time = omp_get_wtime();
    #pragma omp parallel for reduction(+:count)
    for (int64_t i = 0; i < total; i++) {
        count++;
    }
    double end_time = omp_get_wtime();

    printf("count total: %lld\n", count);
    printf("thread num: %d\n", omp_get_max_threads());
    printf("seconds: %f\n", end_time - start_time);
}
