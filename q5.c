#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STUDENTS 10
#define _XOPEN_SOURCE 600

pthread_mutex_t lock;
int sum = 0;
double bellcurved_sum = 0.0;
int grades[NUM_STUDENTS] = {0};

void *save_bellcurve(void *arg);
void *read_grades(void *arg);

int main(){
    pthread_t bellcurve_th[NUM_STUDENTS], read_thread;
    
    if (pthread_create(&read_thread, NULL,read_grades, NULL) != 0){
        printf("\nError creating thread.\n");
        return EXIT_FAILURE;
    }
    if (pthread_join(read_thread, NULL) != 0){
            printf("\nError joining thread.\n");
            return EXIT_FAILURE;
    }
    printf("\n");
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\nError creating mutex lock.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < NUM_STUDENTS; i++){
        if (pthread_create(&bellcurve_th[i], NULL, save_bellcurve, &grades[i]) != 0){
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
    printf("Total grade before bellcurve: %d.\n", sum);
    printf("Student average before bellcurve: %.2f.\n", (float)sum / NUM_STUDENTS);
    printf("Total grade after bellcurve: %.2f.\n", bellcurved_sum);
    printf("Student average after bellcurve: %.2f.\n", bellcurved_sum / NUM_STUDENTS);
    printf("\n");
    return EXIT_SUCCESS;
}

void *save_bellcurve(void *arg){
    pthread_mutex_lock(&lock);
    FILE *fp;
    if ((fp = fopen("grades.txt", "a")) == NULL){
        printf("Error reading file.\n\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fp, "\n");
    int *grade_val = (int*) arg;
    double bellcurved_grade = 1.5 * (*grade_val);
    fprintf(fp, "%.2f ", bellcurved_grade);
    sum += *grade_val;
    bellcurved_sum += bellcurved_grade;
    fclose(fp);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *read_grades(void *arg){
    FILE *fp;
    printf("\nReading grades from the grades.txt file.\n");
    if ((fp = fopen("grades.txt", "r+")) == NULL){
        printf("Error reading file.\n\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < NUM_STUDENTS; i++){
        fscanf(fp, "%d", &grades[i]);
    }
    fclose(fp);
    return NULL;
}