#include <stdio.h>
#include <pthread.h>

// Shared variable
int counter = 0;
pthread_mutex_t lock;

void* increment_counter(void* arg) {
    // Lock the mutex before accessing the shared variable
    pthread_mutex_lock(&lock);
    
    int i;
    for (i = 0; i < 1000000; i++) {
        counter++;
    }
    
    // Unlock the mutex after accessing the shared variable
    pthread_mutex_unlock(&lock);

    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);

    // Create two threads
    pthread_create(&thread1, NULL, increment_counter, NULL);
    pthread_create(&thread2, NULL, increment_counter, NULL);

    // Join the first thread to wait for its completion
    pthread_join(thread1, NULL);

    // Detach the second thread so it runs independently
    pthread_detach(thread2);

    // Lock the mutex before accessing the shared variable in main
    pthread_mutex_lock(&lock);
    printf("Final counter value: %d\n", counter);
    pthread_mutex_unlock(&lock);

    // Destroy the mutex
    pthread_mutex_destroy(&lock);

    return 0;
}
