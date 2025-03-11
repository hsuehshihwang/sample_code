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

// Shared data
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int thread_finished = 0;

// Worker thread
void *task(void *arg) {
    printf("Thread: Doing some work...\n");
    sleep(2);
    printf("Thread: Finished work.\n");

    // Signal other threads that the task is complete
    pthread_mutex_lock(&lock);
    thread_finished = 1;
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&lock);

    return NULL;
}

// Threads waiting for the worker to finish
void *waiting_thread(void *arg) {
    int id = *(int *)arg;

    pthread_mutex_lock(&lock);
    while (!thread_finished) {
        pthread_cond_wait(&cond, &lock);
    }
    pthread_mutex_unlock(&lock);

    printf("Thread %d: Notified that the worker thread is finished.\n", id);
    return NULL;
}

int main(int argc, char *argv[]){
	dbge(); 
    pthread_t worker_thread, waiter1, waiter2;
    int id1 = 1, id2 = 2;

    // Create the worker thread
    pthread_create(&worker_thread, NULL, task, NULL);

    // Create threads waiting for the worker to finish
    pthread_create(&waiter1, NULL, waiting_thread, &id1);
    pthread_create(&waiter2, NULL, waiting_thread, &id2);

    // Join all threads
    pthread_join(worker_thread, NULL);
    pthread_join(waiter1, NULL);
    pthread_join(waiter2, NULL);

    exit(EXIT_SUCCESS);
}

