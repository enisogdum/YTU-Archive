#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char courseName[50];
    char courseCode[10];
    int credit;
    int midtermGrade;
    int finalGrade;
    float average;
} Course;

typedef struct {
    char name[50];
    int studentNo;
    Course *courses;
    int courseCount;
    float overallAverage;
} Student;

void initStudent(Student *stu, char *name, int no);
void addCourse(Student *stu, char *name, char *code, int credit);
void deleteCourse(Student *stu, char *code);
void freeSystem(Student *stu);
void enterGrades(Student *stu, char *code, int midterm, int final);
void calculateOverallAverage(Student *stu);
void updateCourse(Student *stu, char *code, char *newName, int newCredit);
int searchCourse(Student *stu, char *code);
void findHighestGradeCourse(Student stu);
void listFailedCourses(Student stu);
void printReportCard(Student stu);
void creditLoadReport(Student stu);
void sortCoursesAlphabetically(Student *stu);
void updateStudentInfo(Student *stu, char *newName, int newNo);
void copyCourses(Student *target, Student source);

void listStudents(Student *students, int studentCount)
{
    int i = 0;

    if (studentCount == 0) {
        printf("There are no students in the system.\n");
    } else {
        printf("\n--- STUDENTS ---\n");
        while (i < studentCount) {
            printf("%d) %s - %d\n", i + 1, students[i].name, students[i].studentNo);
            i++;
        }
    }
}

int main(void)
{
    Student *students = NULL;
    Student *temporaryStudents;
    char *inputName = malloc(50 * sizeof(char));
    char *inputCode = malloc(10 * sizeof(char));
    int studentCount = 0;
    int activeStudent = -1;
    int choice = -1;
    int no;
    int credit;
    int midterm;
    int final;
    int newNo;
    int sourceIndex;
    int targetIndex;
    int foundIndex;

    if (inputName == NULL || inputCode == NULL) {
        printf("Memory allocation failed.\n");
        free(inputName);
        free(inputCode);
        return 1;
    }

    while (choice != 0) {
        printf("\n--- UNIVERSITY REGISTRATION SYSTEM ---\n");
        printf("1- Add student\n");
        printf("2- Select student\n");
        printf("3- List students\n");
        printf("4- Add course to selected student\n");
        printf("5- Delete course\n");
        printf("6- Enter grades\n");
        printf("7- Calculate overall average\n");
        printf("8- Update course\n");
        printf("9- Search course\n");
        printf("10- Highest-grade course\n");
        printf("11- Failed courses\n");
        printf("12- Report card\n");
        printf("13- Credit-load report\n");
        printf("14- Sort courses alphabetically\n");
        printf("15- Update selected student information\n");
        printf("16- Copy courses between students\n");
        printf("0- Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter student name: ");
            scanf("%49s", inputName);
            printf("Enter student number: ");
            scanf("%d", &no);

            temporaryStudents = realloc(students, (studentCount + 1) * sizeof(Student));
            if (temporaryStudents == NULL) {
                printf("Memory allocation failed. Student was not added.\n");
            } else {
                students = temporaryStudents;
                initStudent(&students[studentCount], inputName, no);
                studentCount++;
                activeStudent = studentCount - 1;
                printf("Student added and selected.\n");
            }
        } else if (choice == 2) {
            listStudents(students, studentCount);
            if (studentCount > 0) {
                printf("Enter student number in the list: ");
                scanf("%d", &activeStudent);
                activeStudent--;
                if (activeStudent < 0 || activeStudent >= studentCount) {
                    printf("Invalid student selection.\n");
                    activeStudent = -1;
                }
            }
        } else if (choice == 3) {
            listStudents(students, studentCount);
        } else if (choice >= 4 && choice <= 15) {
            if (activeStudent < 0 || activeStudent >= studentCount) {
                printf("Select a student first.\n");
            } else if (choice == 4) {
                printf("Enter course name: ");
                scanf("%49s", inputName);
                printf("Enter course code: ");
                scanf("%9s", inputCode);
                printf("Enter credit: ");
                scanf("%d", &credit);
                addCourse(&students[activeStudent], inputName, inputCode, credit);
            } else if (choice == 5) {
                printf("Enter course code: ");
                scanf("%9s", inputCode);
                deleteCourse(&students[activeStudent], inputCode);
            } else if (choice == 6) {
                printf("Enter course code: ");
                scanf("%9s", inputCode);
                printf("Enter midterm grade: ");
                scanf("%d", &midterm);
                printf("Enter final grade: ");
                scanf("%d", &final);
                enterGrades(&students[activeStudent], inputCode, midterm, final);
            } else if (choice == 7) {
                calculateOverallAverage(&students[activeStudent]);
                printf("Overall average: %.2f\n", students[activeStudent].overallAverage);
            } else if (choice == 8) {
                printf("Enter course code: ");
                scanf("%9s", inputCode);
                printf("Enter new course name: ");
                scanf("%49s", inputName);
                printf("Enter new credit: ");
                scanf("%d", &credit);
                updateCourse(&students[activeStudent], inputCode, inputName, credit);
            } else if (choice == 9) {
                printf("Enter course code: ");
                scanf("%9s", inputCode);
                foundIndex = searchCourse(&students[activeStudent], inputCode);
                if (foundIndex == -1) {
                    printf("Course could not be found.\n");
                } else {
                    printf("Course found at index %d.\n", foundIndex);
                }
            } else if (choice == 10) {
                findHighestGradeCourse(students[activeStudent]);
            } else if (choice == 11) {
                listFailedCourses(students[activeStudent]);
            } else if (choice == 12) {
                printReportCard(students[activeStudent]);
            } else if (choice == 13) {
                creditLoadReport(students[activeStudent]);
            } else if (choice == 14) {
                sortCoursesAlphabetically(&students[activeStudent]);
            } else if (choice == 15) {
                printf("Enter new student name: ");
                scanf("%49s", inputName);
                printf("Enter new student number: ");
                scanf("%d", &newNo);
                updateStudentInfo(&students[activeStudent], inputName, newNo);
            }
        } else if (choice == 16) {
            listStudents(students, studentCount);
            if (studentCount > 0) {
                printf("Enter target student number in the list: ");
                scanf("%d", &targetIndex);
                printf("Enter source student number in the list: ");
                scanf("%d", &sourceIndex);
                targetIndex--;
                sourceIndex--;
                if (targetIndex >= 0 && targetIndex < studentCount &&
                    sourceIndex >= 0 && sourceIndex < studentCount &&
                    targetIndex != sourceIndex) {
                    copyCourses(&students[targetIndex], students[sourceIndex]);
                } else {
                    printf("Selections are invalid or refer to the same student.\n");
                }
            }
        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }
    }

    while (studentCount > 0) {
        studentCount--;
        freeSystem(&students[studentCount]);
    }
    free(students);
    free(inputName);
    free(inputCode);
    return 0;
}

void initStudent(Student *stu, char *name, int no)
{
    strcpy(stu->name, name);
    stu->studentNo = no;
    stu->courses = NULL;
    stu->courseCount = 0;
    stu->overallAverage = 0.0f;
}

void addCourse(Student *stu, char *name, char *code, int credit)
{
    Course *temporaryCourses;
    Course *newCourse;

    temporaryCourses = realloc(stu->courses, (stu->courseCount + 1) * sizeof(Course));
    if (temporaryCourses == NULL) {
        printf("Memory allocation failed. Course was not added.\n");
    } else {
        stu->courses = temporaryCourses;
        newCourse = &stu->courses[stu->courseCount];
        strcpy(newCourse->courseName, name);
        strcpy(newCourse->courseCode, code);
        newCourse->credit = credit;
        newCourse->midtermGrade = 0;
        newCourse->finalGrade = 0;
        newCourse->average = 0.0f;
        stu->courseCount++;
        calculateOverallAverage(stu);
        printf("Course added.\n");
    }
}

void deleteCourse(Student *stu, char *code)
{
    int index = searchCourse(stu, code);
    int i;
    Course *temporaryCourses;

    if (index == -1) {
        printf("Course could not be found.\n");
    } else {
        i = index;
        while (i < stu->courseCount - 1) {
            stu->courses[i] = stu->courses[i + 1];
            i++;
        }
        stu->courseCount--;
        if (stu->courseCount == 0) {
            free(stu->courses);
            stu->courses = NULL;
        } else {
            temporaryCourses = realloc(stu->courses, stu->courseCount * sizeof(Course));
            if (temporaryCourses == NULL) {
                printf("Memory could not be reduced, but the course was deleted.\n");
            } else {
                stu->courses = temporaryCourses;
            }
        }
        calculateOverallAverage(stu);
        printf("Course deleted.\n");
    }
}

void freeSystem(Student *stu)
{
    free(stu->courses);
    stu->courses = NULL;
    stu->courseCount = 0;
    stu->overallAverage = 0.0f;
}

void enterGrades(Student *stu, char *code, int midterm, int final)
{
    int index = searchCourse(stu, code);

    if (index == -1) {
        printf("Course could not be found.\n");
    } else {
        stu->courses[index].midtermGrade = midterm;
        stu->courses[index].finalGrade = final;
        stu->courses[index].average = midterm * 0.40f + final * 0.60f;
        calculateOverallAverage(stu);
        printf("Grades updated.\n");
    }
}

void calculateOverallAverage(Student *stu)
{
    int i = 0;
    int totalCredit = 0;
    float weightedTotal = 0.0f;

    while (i < stu->courseCount) {
        weightedTotal += stu->courses[i].average * stu->courses[i].credit;
        totalCredit += stu->courses[i].credit;
        i++;
    }
    if (totalCredit == 0) {
        stu->overallAverage = 0.0f;
    } else {
        stu->overallAverage = weightedTotal / totalCredit;
    }
}

void updateCourse(Student *stu, char *code, char *newName, int newCredit)
{
    int index = searchCourse(stu, code);

    if (index == -1) {
        printf("Course could not be found.\n");
    } else {
        strcpy(stu->courses[index].courseName, newName);
        stu->courses[index].credit = newCredit;
        calculateOverallAverage(stu);
        printf("Course updated.\n");
    }
}

int searchCourse(Student *stu, char *code)
{
    int i = 0;
    int index = -1;

    while (i < stu->courseCount && index == -1) {
        if (strcmp(stu->courses[i].courseCode, code) == 0) {
            index = i;
        }
        i++;
    }
    return index;
}

void findHighestGradeCourse(Student stu)
{
    int i = 1;
    int index = 0;

    if (stu.courseCount == 0) {
        printf("This student has no courses.\n");
    } else {
        while (i < stu.courseCount) {
            if (stu.courses[i].average > stu.courses[index].average) {
                index = i;
            }
            i++;
        }
        printf("Highest-grade course: %s (%s) - %.2f\n",
               stu.courses[index].courseName, stu.courses[index].courseCode,
               stu.courses[index].average);
    }
}

void listFailedCourses(Student stu)
{
    int i = 0;
    int failedCount = 0;

    while (i < stu.courseCount) {
        if (stu.courses[i].average < 50.0f) {
            printf("%s (%s): %.2f - FAILED\n", stu.courses[i].courseName,
                   stu.courses[i].courseCode, stu.courses[i].average);
            failedCount++;
        }
        i++;
    }
    if (failedCount == 0) {
        printf("No failed courses.\n");
    }
}

void printReportCard(Student stu)
{
    int i = 0;

    printf("\nStudent Name: %s\nStudent Number: %d\n", stu.name, stu.studentNo);
    printf("---------------------------------------------------------------\n");
    printf("Name\tCode\tCredit\tMidterm\tFinal\tAverage\n");
    printf("---------------------------------------------------------------\n");
    while (i < stu.courseCount) {
        printf("%s\t%s\t%d\t%d\t%d\t%.2f\n", stu.courses[i].courseName,
               stu.courses[i].courseCode, stu.courses[i].credit,
               stu.courses[i].midtermGrade, stu.courses[i].finalGrade,
               stu.courses[i].average);
        i++;
    }
    printf("Overall Average: %.2f\n", stu.overallAverage);
}

void creditLoadReport(Student stu)
{
    int i = 0;
    int totalCredit = 0;

    while (i < stu.courseCount) {
        totalCredit += stu.courses[i].credit;
        i++;
    }
    printf("%s has a total credit load of %d.\n", stu.name, totalCredit);
}

void sortCoursesAlphabetically(Student *stu)
{
    int i = 0;
    int j;
    Course temporaryCourse;

    while (i < stu->courseCount - 1) {
        j = 0;
        while (j < stu->courseCount - 1 - i) {
            if (strcmp(stu->courses[j].courseName, stu->courses[j + 1].courseName) > 0) {
                temporaryCourse = stu->courses[j];
                stu->courses[j] = stu->courses[j + 1];
                stu->courses[j + 1] = temporaryCourse;
            }
            j++;
        }
        i++;
    }
    printf("Courses sorted alphabetically:\n");
    i = 0;
    while (i < stu->courseCount) {
        printf("%d) %s\n", i + 1, stu->courses[i].courseName);
        i++;
    }
}

void updateStudentInfo(Student *stu, char *newName, int newNo)
{
    strcpy(stu->name, newName);
    stu->studentNo = newNo;
    printf("Student information updated.\n");
}

void copyCourses(Student *target, Student source)
{
    Course *newCourses;
    int i = 0;

    if (source.courseCount == 0) {
        free(target->courses);
        target->courses = NULL;
        target->courseCount = 0;
        target->overallAverage = 0.0f;
        printf("Source student has no courses. Target courses were cleared.\n");
    } else {
        newCourses = malloc(source.courseCount * sizeof(Course));
        if (newCourses == NULL) {
            printf("Memory allocation failed. Courses were not copied.\n");
        } else {
            while (i < source.courseCount) {
                newCourses[i] = source.courses[i];
                i++;
            }
            free(target->courses);
            target->courses = newCourses;
            target->courseCount = source.courseCount;
            calculateOverallAverage(target);
            printf("Courses copied successfully.\n");
        }
    }
}
