#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *hello_world(void *arg);

void *goodbye(void *arg);

int main(){
    pthread_t hello_thread, goodbye_thread;
    if (pthread_create(&hello_thread, NULL, hello_world, NULL) != 0){
        printf("\nError creating the hello world thread.\n");
        return EXIT_FAILURE;
    }

    if (pthread_create(&goodbye_thread, NULL, goodbye, NULL) != 0){
        printf("\nError creating the goodbye thread.\n");
        return EXIT_FAILURE;
    }

    if (pthread_join(hello_thread, NULL) != 0){
        printf("\nError joining the hello world thread.\n");
        return EXIT_FAILURE;
    }

    if (pthread_join(goodbye_thread, NULL) != 0){
        printf("\nError joining the goodbye thread.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void *hello_world(void *arg){
    int rand_num = rand() % 5;
    sleep(rand_num);
    printf("\nHello World!\n");
    return NULL;
}

void *goodbye(void *arg){
    int rand_num = rand() % 5;
    sleep(rand_num);
    printf("\nGoodbye!\n");
    return NULL;
}