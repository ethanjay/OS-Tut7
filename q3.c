#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_STUDENTS 5
#define STR_LEN 50

typedef struct{
    int grade;
    int student_id;
    char name[STR_LEN];
} student; 
pthread_mutex_t lock;

void *bellcurve(void *arg);

int main(){
    pthread_t bellcurve_th[NUM_STUDENTS];
    student students[NUM_STUDENTS];

    printf("\nEnter the information for 5 students.\n\n");
    for (int i = 0; i < NUM_STUDENTS; i++){
        printf("Enter the student ID for student #%d: ", i + 1);
        scanf("%d", &students[i].student_id);
        printf("Enter the name for student #%d: ", i + 1);
        scanf("%s", students[i].name);
        printf("Enter the grade for student #%d: ", i + 1);
        scanf("%d", &students[i].grade);
    }
    getchar();
    printf("\n");

    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\nError creating mutex lock.\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < NUM_STUDENTS; i++){
        if (pthread_create(&bellcurve_th[i], NULL, bellcurve, &students[i]) != 0){
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
    pthread_mutex_lock(&lock);
    double bellcurved_grade = 0;
    student *student_val = (student*) arg;
    bellcurved_grade = student_val->grade * 1.5;
    printf("Student name: %s\n", student_val->name);
    printf("Student ID: %d\n", student_val->student_id);
    printf("Initial grade: %d, Bellcurved grade: %.2f\n\n", student_val->grade, bellcurved_grade);
    pthread_mutex_unlock(&lock);
    return NULL;
}
