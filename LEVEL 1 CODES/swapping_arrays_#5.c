#include <stdio.h>

/* Function Prototypes (Pointer version) */
void read_array(int n, int *arr);
void swap_arrays(int n, int *arr1, int *arr2);
void display_arrays(int n, int *arr1, int *arr2);

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d",&n);

    if(n<=0)
    {
        printf("Invalid array size\n");
      
    }
    int arr1[n];
    int arr2[n];
    
    printf("Enter elements of array 1:\n");
    read_array(n,arr1);

    printf("Enter elements of array 2:\n");
    read_array(n,arr2);

    /* Before swapping */
    printf("\nBefore swapping:\n");
    display_arrays(n,arr1, arr2);

    /* Call swap function */
    swap_arrays(n, arr1,arr2);
    

    /* After swapping */
    printf("\nAfter swapping:\n");
    display_arrays(n,arr1, arr2);
    
    return 0;
}

/* Function to input array elements */
void read_array(int n, int *arr)
{
        for(int i=0;i<n;i++)
        {
            printf("Enter element at index %d: ", i);
            scanf("%d",&arr[i]);
        }
}

/* Function to swap arrays */
void swap_arrays(int n, int *arr1, int *arr2)
{
    int temp=0;
    for(int i=0;i<n;i++)
    {
     temp=arr1[i];
     arr1[i]=arr2[i];
     arr2[i]=temp;
    }
}

/* Function to display arrays */
void display_arrays(int n, int *arr1, int *arr2)
{
    printf("Array 1:\n");
    for(int i=0;i<n;i++)
    {
    printf("%d ", arr1[i]);  
    }

    printf("\nArray 2:\n");
    for(int i=0;i<n;i++)
    {
    printf("%d ", arr2[i]);  
    }
    

}