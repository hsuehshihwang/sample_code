#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define __file__ strrchr(__FILE__, '/')?strrchr(__FILE__, '/')+1:__FILE__
#define dbg(fmt, ...) do{\
	fprintf(stdout, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 
#define dbge(fmt, ...) do{\
	fprintf(stderr, "%s(%d)@%s: " fmt "\n", __FUNCTION__, __LINE__, __file__, ## __VA_ARGS__); \
	fflush(stdout); \
}while(0); 

#define REPEAT_5(C) C C C C C
#define REPEAT_10(C) REPEAT_5(C) REPEAT_5(C)
#define REPEAT_20(C) REPEAT_10(C) REPEAT_10(C)
#define REPEAT_40(C) REPEAT_20(C) REPEAT_20(C)
#define REPEAT_80(C) REPEAT_40(C) REPEAT_40(C)

#define REPEAT(C,n) REPEAT_##n(C)

#define FUNC_BAR REPEAT("=",20)

#define FUNC_TITLE \
    do { \
        printf("%.*s %s %.*s\n", (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2), FUNC_BAR, __FUNCTION__, (int)(strlen(FUNC_BAR)-strlen(__FUNCTION__)/2-strlen(__FUNCTION__)%2), FUNC_BAR); \
		fflush(stdout); \
    } while(0); 

// Function to be executed by the thread
void *thread_function(void *arg) {
    int *id = (int *)arg;
    printf("Thread %d: Starting\n", *id);

    // Simulate some work
    sleep(2);

    printf("Thread %d: Finishing\n", *id);
    return NULL;
}

int main(int argc, char *argv[]){
	dbge(); 
    pthread_t thread1, thread2;      // Thread identifiers
    pthread_attr_t attr;            // Thread attribute
    int id1 = 1, id2 = 2;           // Thread arguments

    // Initialize thread attributes
    pthread_attr_init(&attr);

    // Set the thread to joinable (default, but explicit for demonstration)
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Create two threads
    if (pthread_create(&thread1, &attr, thread_function, &id1) != 0) {
        perror("Failed to create thread 1");
        return 1;
    }

    if (pthread_create(&thread2, &attr, thread_function, &id2) != 0) {
        perror("Failed to create thread 2");
        return 1;
    }

    // Destroy the attribute object since it's no longer needed
    pthread_attr_destroy(&attr);

    // Wait for the threads to finish
    if (pthread_join(thread1, NULL) != 0) {
        perror("Failed to join thread 1");
        return 1;
    }

    if (pthread_join(thread2, NULL) != 0) {
        perror("Failed to join thread 2");
        return 1;
    }

    printf("Both threads have completed.\n");

    exit(EXIT_SUCCESS);
}

