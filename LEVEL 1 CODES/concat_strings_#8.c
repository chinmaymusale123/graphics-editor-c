#include <stdio.h>

// Function Prototypes
void input(char *str);
void concatenate_strings(char *str1, char *str2);
void display(char *str);

int main() {
    char str1[100], str2[100];

    printf("Enter the first string:\n");
    input(str1);

    printf("Enter the second string:\n");
    input(str2);

    concatenate_strings(str1, str2);

    display(str1);

    return 0;
}


void input(char *str) {
    scanf("%s", str);
}

void concatenate_strings(char *str1, char *str2) {
    int i = 0, j = 0;

    // Move i to end of str1
    while (str1[i] != '\0') {
        i++;
    }

    // Copy str2 into str1
    while (str2[j] != '\0') {
        str1[i] = str2[j];/*so basically we are just putting all str2 letter into str1 we no longer will 
                            have str2 with us.*/
        i++;
        j++;
    }

    str1[i] = '\0';  // Null terminate the final string
}

void display(char *str) {
    int i = 0;

    // imp: match expected format.
    printf("Concatenated Result: ");

    while (str[i] != '\0') {
        printf("%c", str[i]);
        i++;
    }

    printf("\n"); // this \n is imp if you are writing it the while loop way else, if you are just printing the string
                    // str then \n has to be inside the print concatenated result string.
}