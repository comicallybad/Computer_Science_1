#include <stdio.h>
#define MAXSIZE 500

struct Student
{
    int student_id;
    int g1, g2, g3;
    float avg;
};

struct Student getMaxAverageStudent(struct Student *s, int n)
{
    int max_idx = 0;
    float max = -1;
    for (int i = 0; i < n; i++)
    {
        if (s[i].avg > max)
        {
            max = s[i].avg;
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
        fscanf(infile, "%d", &students[i].student_id);
        fscanf(infile, "%d %d %d", &students[i].g1, &students[i].g2, &students[i].g3);
        students[i].avg = (students[i].g1 + students[i].g2 + students[i].g3) / 3.0;

        printf("%d %d %d %d %0.2f\n", students[i].student_id, students[i].g1, students[i].g2, students[i].g3, students[i].avg);

        fprintf(outfile, "%d %d %d %d %0.2f\n", students[i].student_id, students[i].g1, students[i].g2, students[i].g3, students[i].avg);
    }

    struct Student maxStudent = getMaxAverageStudent(students, n);

    printf("\nMaximum Average is %0.2f and the student is %d\n", maxStudent.avg, maxStudent.student_id);

    fprintf(outfile, "\nMaximum Average is %0.2f and the student is %d", maxStudent.avg, maxStudent.student_id);

    fclose(infile);
    fclose(outfile);

    return 0;
}