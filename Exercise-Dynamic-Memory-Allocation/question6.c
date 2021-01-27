#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

struct Student
{
    int student_id;
    float *quizzes;
};

struct Student *AllocateStudents(int N, int Q)
{
    struct Student *studentArray = (struct Student *)malloc(sizeof(struct Student) * N);
    for (int i = 0; i < N; i++)
    {
        studentArray[i].quizzes = malloc(sizeof(float) * Q);
        for (int j = 0; j < Q; j++)
        {
            printf("Please enter grade %d for Student %d: ", j + 1, i + 1);
            scanf("%f", &studentArray[i].quizzes[j]);
        }
    }
    return studentArray;
}

void free_up_memory(struct Student *studentArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(studentArray[i].quizzes);
    }
    free(studentArray);
}

int main(void)
{
    atexit(report_mem_leak);

    struct Student *students = AllocateStudents(5, 2);

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            printf("Student %d Quiz %d: %f\n", i + 1, j + 1, students[i].quizzes[j]);
        }
    }

    free_up_memory(students, 5);

    return 0;
}