#include <stdio.h>

typedef struct {
    int id;
    char name[50];
    float marks;
} Student;

// Function declarations
void inputStudents(Student students[], int n);
void writeToBinaryFile(Student students[], int n, const char *filename);
int readFromBinaryFile(Student students[], const char *filename);
void printStudents(Student students[], int n);

// Main
int main() {
    int n;

    printf("Enter the size:\n");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input\n");
        return 1;
    }

    Student students[n];
    Student bin_read[n];

    // 1. Input
    inputStudents(students, n);

    // 2. Write to binary file
    writeToBinaryFile(students, n, "students.dat");
    
    // 3. Read from binary file
    int count = readFromBinaryFile(bin_read, "students.dat");
   
    // 4. Print read data
    printf("\n--- Students read from Binary file ---\n");
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

// Write to binary file
void writeToBinaryFile(Student students[], int n, const char *filename) {
    FILE *fp = fopen(filename, "wb");

    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return;
    }

    fwrite(students, sizeof(Student), n, fp); // don't change the order of these arguments,
    

    fclose(fp);
}

// Read from binary file
int readFromBinaryFile(Student students[], const char *filename) {
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 0;
    }

    int count = fread(students, sizeof(Student), 100, fp);// what is this 100 here for?

    fclose(fp);
    return count;
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