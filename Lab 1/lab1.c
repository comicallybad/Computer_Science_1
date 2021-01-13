#include <stdio.h>
#define MAXSIZE 500

struct Student
{
    int student_ID;
    int g1, g2, g3;
    float average;
};

struct Student getMaxAverageStudent(struct Student *s, int n)
{
    int max_idx = 0;
    float max = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i].average > max)
        {
            max = s[i].average;
            max_idx = i;
        }
    }
    return s[max_idx];
}

int main()
{
    struct Student students[MAXSIZE];

    FILE *infile;
    infile = fopen("students.txt", "r");

    FILE *outfile;
    outfile = fopen("out.txt", "w");

    int n;
    fscanf(infile, "%d", &n);

    for (int i = 0; i < n; i++)
    {
        fscanf(infile, "%d", &students[i].student_ID);
        fscanf(infile, "%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3);
        students[i].average = (students[i].g1 + students[i].g2 + students[i].g3) / 3.0;

        printf("%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);

        fprintf(outfile, "%d %d %d %d %0.2f\n", students[i].student_ID, students[i].g1, students[i].g2, students[i].g3, students[i].average);
    }

    struct Student maxStudent = getMaxAverageStudent(students, n);

    printf("\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);

    fprintf(outfile, "\nMaximum Average is %0.2f and the student is %d\n", maxStudent.average, maxStudent.student_ID);

    fclose(infile);
    fclose(outfile);

    return 0;
}