#include <stdio.h>
#include <stdlib.h>   /* needed for malloc() and free() */

/* ── FUNCTION PROTOTYPES ────────────────────────────────────────────────────── */
int* create_array(int n);           /* returns an ADDRESS (pointer to int) */
void initialize_array(int *arr, int n);
void print_array(int *arr, int n);
void delete_array(int **arr);       /* needs double pointer so it can set original pointer to NULL */

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid size\n");
        return 0;
    }

    /* create_array returns an ADDRESS.
       int *arr  means "arr is a variable that STORES an address".
       The * here is part of the TYPE DECLARATION, NOT dereferencing.
       No value is being read or fetched here — arr simply receives the address. */
    int *arr = create_array(n);

    initialize_array(arr, n);   /* fill the array with user input */

    printf("\nArray elements:\n");
    print_array(arr, n);

    delete_array(&arr);   /* free memory and set arr to NULL */

    return 0;
}

/* Allocate memory for n integers on the HEAP using malloc.
   Returns the ADDRESS of the first integer (not a value). */
int* create_array(int n)
{
    /* malloc finds free memory for n integers and returns its ADDRESS.
       (int *) is a CAST — it tells C "treat this address as pointer to int".
       It does NOT dereference anything.
       The * in int *arr is again a TYPE DECLARATION — arr stores an address. */
    int *arr = (int *) malloc(n * sizeof(int));

    if (arr == NULL)
    {
        /* malloc returns NULL when it cannot find enough free memory */
        printf("Memory allocation failed\n");
        return NULL;
    }

    /* We return arr (the ADDRESS), NOT *arr (the value at that address).
       Returning *arr would give the caller just one integer — useless.
       Returning arr gives the caller the address so it can access the whole array. */
    return arr;
}

/* Fill each slot of the array with a number entered by the user */
void initialize_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter element at index %d: ", i);
        scanf("%d", &arr[i]);   /* &arr[i] = address of i-th element */
    }
}

/* Print every element of the array */
void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

/* Free the heap memory and set the caller's pointer to NULL.
   WHY int **arr (double pointer)?
   → We want to change the ORIGINAL pointer 'arr' in main().
   → If we used int *arr, we'd only change a LOCAL COPY — main's pointer stays unchanged.
   → With int **arr, *arr refers to main's actual pointer, so we can NULL it.

   WHY set *arr = NULL after free()?
   → After free(), the memory is released but 'arr' still holds the old address.
   → This is called a DANGLING POINTER — accessing it causes undefined behavior.
   → Setting *arr = NULL makes it safe: accessing a NULL pointer is a clear crash,
     not silent corruption. */
void delete_array(int **arr)
{
    free(*arr);    /* release the heap memory */
    *arr = NULL;   /* set the original pointer to NULL */
}