#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STUDENTS 10

pthread_mutex_t lock;
int sum = 0;
void *sum_grades(void *arg);

int main(){
    pthread_t bellcurve_th[NUM_STUDENTS];
    int grades[NUM_STUDENTS] = {0};
    printf("\nEnter the grades for 5 students.\n\n");
    for (int i = 0; i < NUM_STUDENTS; i++){
        printf("Enter the grade for student #%d: ", i + 1);
        scanf("%d", &grades[i]);
    }
    getchar();
    printf("\n");
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\nError creating mutex lock.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < NUM_STUDENTS; i++){
        if (pthread_create(&bellcurve_th[i], NULL, sum_grades, &grades[i]) != 0){
            printf("\nError creating thread.\n");
            return EXIT_FAILURE;
        }
    }
    
    for (int i = 0; i < NUM_STUDENTS; i++){
        if (pthread_join(bellcurve_th[i], NULL) != 0){
            printf("\nError joining thread.\n");
            return EXIT_FAILURE;
        }
    }
    printf("The sum of all %d grades is: %d.\n\n", NUM_STUDENTS, sum);
    return EXIT_SUCCESS;
}

void *sum_grades(void *arg){
    pthread_mutex_lock(&lock);
    int *grade_val = (int*) arg;
    sum += *grade_val;
    printf("Adding grades!\n");
    pthread_mutex_unlock(&lock);
    return NULL;
}
