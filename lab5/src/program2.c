#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex;
int result = 1;

void *factorial(void *arg) {
    int k = *((int *) arg);
    int mod = *((int *) arg + 1);
    int local_result = 1;

    for (int i = 1; i <= k; i++) {
        local_result = (local_result * i) % mod;
    }

    pthread_mutex_lock(&mutex);
    result = (result * local_result) % mod;
    pthread_mutex_unlock(&mutex);

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    int k = 0;
    int pnum = 0;
    int mod = 0;

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0) {
            k = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "--pnum") == 0) {
            pnum = atoi(argv[i+1]);
        } else if (strcmp(argv[i], "--mod") == 0) {
            mod = atoi(argv[i+1]);
        }
    }

    // Initialize mutex
    pthread_mutex_init(&mutex, NULL);

    // Create threads
    pthread_t threads[pnum];
    int args[pnum * 2];
    int step = k / pnum;

    for (int i = 0; i < pnum; i++) {
        args[i * 2] = (i == pnum - 1) ? k - i * step : step;
        args[i * 2 + 1] = mod;
        pthread_create(&threads[i], NULL, factorial, &args[i * 2]);
    }

    // Wait for threads to finish
    for (int i = 0; i < pnum; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print result
    printf("%d! mod %d = %d\n", k, mod, result);

    // Destroy mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}