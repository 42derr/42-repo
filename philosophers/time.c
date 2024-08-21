#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);

    // Seconds since the Epoch
    long seconds = tv.tv_sec;

    // Microseconds part of the time
    long microseconds = tv.tv_usec;

    // Print the time
    printf("Seconds: %ld\n", seconds);
    printf("Microseconds: %ld\n", microseconds);

    // If you want to print the current time in milliseconds:
    long milliseconds = seconds * 1000 + microseconds / 1000;
    printf("Milliseconds: %ld\n", milliseconds);

    return 0;
}
