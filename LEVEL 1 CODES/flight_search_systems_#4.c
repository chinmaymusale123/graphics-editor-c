#include <stdio.h>
#include <string.h>

/* Structure Definition */
typedef struct
{
    int flight_number;
    char destination[50];
    int available_seats;
} Flight;

/* Function Prototypes */
void input_flights(int n, Flight flights[n]);
int search_flights(int n, Flight flights[n], char destination[], int result[]);
void display(int count, int result[], Flight flights[]);

int main()
{
    int n = 4;
    Flight flights[n];
    char destination[50];
    int result[n];

    input_flights(n, flights);

    printf("\nEnter destination to search: "); // we will enter destination to search only after we have input
                                            // the fights.
    scanf("%s", destination);

    int count = search_flights(n, flights, destination, result);

    display(count, result, flights);

    return 0;
}

/* Function to input flight details */
void input_flights(int n, Flight flights[n])
{
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of flight %d\n", i + 1);

        printf("Enter flight number: ");
        scanf("%d", &flights[i].flight_number);

        printf("Enter destination: ");
        scanf("%s", flights[i].destination);

        printf("Enter available seats: ");
        scanf("%d", &flights[i].available_seats);
    }
}

/* Function to search flights */
int search_flights(int n, Flight flights[n], char destination[], int result[])
{
    int count = 0;

    for (int i = 0; i < n; i++)
    {
        if (strcmp(flights[i].destination, destination) == 0)
        {
            result[count] = i;  // result array is meant to store all the index of the matched flights...
            count++;
        }
    }

    return count;
}

/* Function to display result */
void display(int count, int result[], Flight flights[])
{
    if (count == 0)
    {
        printf("No flight available to the given destination\n");
    }
    else
    {
        printf("Flights available:\n");

        for (int i = 0; i < count; i++)
        {
            int idx = result[i]; //idx collect the index one by one.
            // so basically result was just storing all the indices in form of an array and now we are extracting
            // those indices one by one and feeding it to flights array for it to print all real values.
            printf("Flight Number: %d\n", flights[idx].flight_number);
        }
    }
}
/*
LOGIC OF STORING INDICES IN result array:
- first i values were given to result to store in array
- then in print function we are removing those values one by one and which is getting stored in idx every time
- so idx is also storing indices but one by one cz its not an array its a variable.
- now we are again giving those indices to flights array so that it can extract the actual values.
*/