#include <stdio.h>

// Function prototypes
void readString(char *str, int size);
void removeNewline(char *str);
int compareStrings(char *str1, char *str2); // to be implemented
void displayResult(int result);

int main() {

    char str1[100], str2[100];
    int result;
    
    printf("Enter first string: ");
    readString(str1,100);
    
    printf("Enter second string: ");
    readString(str2,100);
    
    // Pre-processing
    removeNewline(str1);
    removeNewline(str2);

    // Processing
    result=compareStrings(str1,str2);

    // Output
    displayResult(result);

    return 0;
}

// Reads input
void readString(char *str, int size) {
    scanf("%s",str);
}

// Removes newline
void removeNewline(char *str) {
    int i=0;
    
    while(str[i]!='\0')
    {
        if(str[i]=='\n')
        {
            str[i]='\0';
            break;
        }
        i++;
    }
}


int compareStrings(char *str1, char *str2) {
    int i=0;
    
   while(str1[i]!='\0' || str2[i] !='\0') // make sure there is no equal to condition. else it will cause problem
    {
        if(str1[i]>str2[i])
            return 1;
        else if(str1[i]<str2[i])
            return -1;
        
        i++;
    }
    return 0; // this will return 0 only if both the strings are equal.
}

// Displays result
void displayResult(int result) {
        if(result==0)
        printf("Both strings are equal.\n");
        
        else if(result==1)
        printf("First string is lexicographically greater.\n");
        
        else
        printf("Second string is lexicographically greater.\n");
   
}