#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STUDENTS 5

void *bellcurve(void *arg);

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
    for (int i = 0; i < NUM_STUDENTS; i++){
        if (pthread_create(&bellcurve_th[i], NULL, bellcurve, &grades[i]) != 0){
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
    printf("\n");
    return EXIT_SUCCESS;
}

void *bellcurve(void *arg){
    int *grade_val = (int*) arg;
    printf("Initial grade: %d, Bellcurved grade: %.2f\n", *grade_val, 1.5 * (*grade_val));
    return NULL;
}
