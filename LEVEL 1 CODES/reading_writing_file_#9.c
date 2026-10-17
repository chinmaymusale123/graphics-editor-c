/*Probable mistakes:
- The logic of read function is correct do not change--> its the easiest one
- do check\n after writing all that %s %d%f...very imp for formatting.
- do not pass n in the function call of print, pass count.
- for checking of n at the start n<=  0 is enough no need to make it more complex.
*/
#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function declarations
void inputStudents(Student students[], int n);
void writeToTextFile(Student students[], int n, const char *filename);
int readFromTextFile(Student students[], const char *filename);
void printStudents(Student students[], int n);

// Main
int main() {
    int n;

    printf("Enter the size:\n");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    Student students[n];   // ✅ Only ONE array

    // 1. Input
    inputStudents(students, n);

    // 2. Write to ASCII file
    writeToTextFile(students, n, "students.txt");

    // 3. Read from ASCII file (overwrite same array)
    int count = readFromTextFile(students, "students.txt");

    // 4. Print read data
    printf("\n--- Students read from ASCII file ---\n");
    printStudents(students, count);

    return 0;
}

// Read input
void inputStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details of student %d:\n", i + 1);

        printf("ID: ");
        scanf("%d", &students[i].id);

        printf("Name: ");
        scanf("%s", students[i].name);

        printf("Marks: ");
        scanf("%f", &students[i].marks);
    }
}

// Write to text file
void writeToTextFile(Student students[], int n, const char *filename) {
    FILE *fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d %s %.2f\n",
                students[i].id,
                students[i].name,
                students[i].marks);
    }

    fclose(fp);
}

// Read from text file
int readFromTextFile(Student students[], const char *filename) { 
    FILE *fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 0;
    }

    int i = 0;

    while (fscanf(fp, "%d %s %f",
                  &students[i].id,
                  students[i].name,
                  &students[i].marks) == 3) {
        i++;
    }

    fclose(fp);
    return i;
}

// Print students
void printStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d %s %.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks);
    }
}