#include <stdio.h>

/* Structure Definition */
typedef struct{
    int length;
    int width;
    int area;
}Rectangle;

/* Function Prototypes */
Rectangle input();

int calculate_area(Rectangle rect);
int compare_areas(Rectangle r1, Rectangle r2, Rectangle r3);
void output(int result, Rectangle r1, Rectangle r2, Rectangle r3);

int main() {
    Rectangle r1,r2,r3;
    
    printf("Enter details of Rectangle 1\n");
    r1=input();
    r1.area=calculate_area(r1);
    
    printf("\nEnter details of Rectangle 2\n");
    r2=input();
    r2.area=calculate_area(r2);

    printf("\nEnter details of Rectangle 3\n");
    r3=input();
    r3.area=calculate_area(r3);
    
    int result=compare_areas(r1,r2,r3);
    output(result,r1,r2,r3);
    return 0;
}

/* Function to read rectangle details */
Rectangle input() {
    Rectangle rect;
    
    
    printf("Enter length: ");
    /* write code to read length */
    scanf("%d",&rect.length);
    
    printf("Enter width: ");
    /* write code to read width */
    scanf("%d",&rect.width);
    
    return rect;
}

/* Function to calculate area */
int calculate_area(Rectangle rect) {


   rect.area= rect.length*rect.width;
   return rect.area;
    /* write code to calculate area */

}

/* Function to compare areas */
int compare_areas(Rectangle r1, Rectangle r2, Rectangle r3) {

    /* write code to compare areas of three rectangles */
if(r1.area>r2.area && r1.area>r3.area)
    return 1;
    
else if(r2.area>r1.area && r2.area>r3.area)
    return 2;
    
else if(r3.area>r1.area && r3.area>r2.area)
    return 3;

else if(r1.area==r2.area && r1.area>r3.area)
    return 12;
    
else if(r1.area==r3.area && r1.area>r2.area)
    return 13;

else if(r2.area==r3.area && r2.area>r1.area)
    return 23;

else
    return 123;
}

/* Function to display result */
void output(int result, Rectangle r1, Rectangle r2, Rectangle r3) {

    printf("\nResult:\n");

    if(result==1)
        printf("Rectangle 1 has the largest area = %d\n", r1.area);

    else if(result==2)
        printf("Rectangle 2 has the largest area = %d\n",r2.area);

    else if(result==3)
        printf("Rectangle 3 has the largest area = %d\n", r3.area);

    else if(result==12)
        printf("Rectangle 1 and Rectangle 2 have the largest equal area = %d\n",r1.area);

    else if(result==13)
        printf("Rectangle 1 and Rectangle 3 have the largest equal area = %d\n",r1.area);

    else if(result==23)
        printf("Rectangle 2 and Rectangle 3 have the largest equal area = %d\n", r2.area);

    else
        printf("All three rectangles have the same area = %d\n", r1.area);
}