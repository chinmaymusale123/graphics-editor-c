// each memeber like rects will have its own length, breadth and area.
// and Rectangle is a strcuture.
#include <stdio.h>

/* Structure Definition */
typedef struct{
    int length;
    int width;
    int area;
}Rectangle;

/* Function Prototypes */
void input_rectangles(int n, Rectangle rects[n]);
void calculate_areas(int n, Rectangle rects[n]);
int find_max_index(int n, Rectangle rects[n]);
void display_areas(int n, Rectangle rects[n]);
void display_max(Rectangle rects[], int max_index);

int main()
{
    int n;
    printf("Enter number of rectangles: ");
    scanf("%d",&n);

    if(n<=0)
    {
        printf("Invalid number of rectangles\n");
        return 0;
       
    }
    Rectangle rects[n];//created an array.
    input_rectangles(n,rects);
    calculate_areas(n,rects);
    display_areas(n,rects);
    int max_index=find_max_index(n,rects);
    display_max(rects,max_index);
    return 0;
}

/* Function to input rectangle details */
void input_rectangles(int n, Rectangle rects[n])
{
        for(int i=0;i<n;i++)
        {   
            printf("Enter length of rectangle %d: ",i+1);
            scanf("%d",&rects[i].length);
            
            printf("Enter width of rectangle %d: ",i+1);
            scanf("%d",&rects[i].width);
        }
    
        // write code

        
        // write code
}


void calculate_areas(int n, Rectangle rects[n])
{
        for(int i=0;i<n;i++)
        {
            rects[i].area=rects[i].length*rects[i].width;
        }
}

/* Function to display all areas */
void display_areas(int n, Rectangle rects[n])
{
    printf("\nAreas of rectangles:\n");
    for(int i=0;i<n;i++)
    {
        printf("Rectangle %d area = %d\n", i+1,rects[i].area);
    }

}

/* Function to find index of rectangle with maximum area */
int find_max_index(int n, Rectangle rects[n])
{
   
    int max_index=0;
    for(int i=1;i<n;i++)// we will not start i with one as we will be comparing it with 0th element
                        // only as max_index is 0.
    {
        if(rects[i].area>rects[max_index].area)
        {
            max_index=i;
        }
    }
    
    return max_index;
}

/* Function to display rectangle with maximum area */
void display_max(Rectangle rects[], int max_index)
{   
    
    printf("\nRectangle %d has the largest area = %d\n",(max_index+1),rects[max_index].area);
}
// whenver you wann display someting using index then always write +1, because by default indexing starts from 0

