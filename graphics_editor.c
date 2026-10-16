#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define ROWS 25
#define COLS 60
#define EMPTY '_'
#define DRAW  '*'
#define MAX_OBJECTS 50

// ─── Canvas ───────────────────────────────────────────────────────────────────
char canvas[ROWS][COLS];

void initCanvas() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            canvas[i][j] = EMPTY;
}

void displayCanvas() {
    printf("\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            putchar(canvas[i][j]);
        putchar('\n');
    }
    printf("\n");
}

void setPixel(int r, int c, char ch) {
    if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
        canvas[r][c] = ch;
}

// ─── Drawing Algorithms ───────────────────────────────────────────────────────

// Bresenham's Line Algorithm [web:8]
void drawLine(int r1, int c1, int r2, int c2, char ch) {
    int dr = abs(r2 - r1), dc = abs(c2 - c1);
    int sr = (r1 < r2) ? 1 : -1;
    int sc = (c1 < c2) ? 1 : -1;
    int err = dr - dc;
    while (1) {
        setPixel(r1, c1, ch);
        if (r1 == r2 && c1 == c2) break;
        int e2 = 2 * err;
        if (e2 > -dc) { err -= dc; r1 += sr; }
        if (e2 <  dr) { err += dr; c1 += sc; }
    }
}

// Midpoint Circle Algorithm [web:8]
void drawCircle(int cr, int cc, int radius, char ch) {
    int x = 0, y = radius;
    int d = 1 - radius;
    while (x <= y) {
        setPixel(cr + x, cc + y, ch);
        setPixel(cr - x, cc + y, ch);
        setPixel(cr + x, cc - y, ch);
        setPixel(cr - x, cc - y, ch);
        setPixel(cr + y, cc + x, ch);
        setPixel(cr - y, cc + x, ch);
        setPixel(cr + y, cc - x, ch);
        setPixel(cr - y, cc - x, ch);
        if (d < 0) d += 2 * x + 3;
        else       { d += 2 * (x - y) + 5; y--; }
        x++;
    }
}

void drawRectangle(int r1, int c1, int r2, int c2, char ch) {
    drawLine(r1, c1, r1, c2, ch);  // top
    drawLine(r2, c1, r2, c2, ch);  // bottom
    drawLine(r1, c1, r2, c1, ch);  // left
    drawLine(r1, c2, r2, c2, ch);  // right
}

void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3, char ch) {
    drawLine(r1, c1, r2, c2, ch);
    drawLine(r2, c2, r3, c3, ch);
    drawLine(r3, c3, r1, c1, ch);
}

// ─── Object Store (for delete/modify) ─────────────────────────────────────────
typedef enum { OBJ_LINE, OBJ_CIRCLE, OBJ_RECT, OBJ_TRIANGLE } ObjType;

typedef struct {
    ObjType type;
    int params[6];  // flexible: stores up to 6 integers
    int active;
} Object;

Object objects[MAX_OBJECTS];
int objCount = 0;

void redrawAll() {
    initCanvas();
    for (int i = 0; i < objCount; i++) {
        if (!objects[i].active) continue;
        int *p = objects[i].params;
        switch (objects[i].type) {
            case OBJ_LINE:     drawLine(p[0],p[1],p[2],p[3], DRAW); break;
            case OBJ_CIRCLE:   drawCircle(p[0],p[1],p[2], DRAW);    break;
            case OBJ_RECT:     drawRectangle(p[0],p[1],p[2],p[3], DRAW); break;
            case OBJ_TRIANGLE: drawTriangle(p[0],p[1],p[2],p[3],p[4],p[5], DRAW); break;
        }
    }
}

void listObjects() {
    printf("\nID  Type        Parameters\n");
    printf("--- ----------- --------------------------------\n");
    for (int i = 0; i < objCount; i++) {
        if (!objects[i].active) continue;
        int *p = objects[i].params;
        printf("[%d] ", i);
        switch (objects[i].type) {
            case OBJ_LINE:
                printf("Line        (%d,%d) -> (%d,%d)\n", p[0],p[1],p[2],p[3]); break;
            case OBJ_CIRCLE:
                printf("Circle      center(%d,%d) r=%d\n", p[0],p[1],p[2]); break;
            case OBJ_RECT:
                printf("Rectangle   (%d,%d) to (%d,%d)\n", p[0],p[1],p[2],p[3]); break;
            case OBJ_TRIANGLE:
                printf("Triangle    (%d,%d),(%d,%d),(%d,%d)\n",
                       p[0],p[1],p[2],p[3],p[4],p[5]); break;
        }
    }
}

// ─── Add Object ───────────────────────────────────────────────────────────────
void addObject() {
    if (objCount >= MAX_OBJECTS) { printf("Canvas full!\n"); return; }
    printf("\n1. Line\n2. Circle\n3. Rectangle\n4. Triangle\nChoice: ");
    int ch; scanf("%d", &ch);
    Object obj; memset(&obj, 0, sizeof(obj)); obj.active = 1;
    int *p = obj.params;

    switch (ch) {
        case 1:
            obj.type = OBJ_LINE;
            printf("Enter r1 c1 r2 c2: "); scanf("%d%d%d%d",&p[0],&p[1],&p[2],&p[3]);
            break;
        case 2:
            obj.type = OBJ_CIRCLE;
            printf("Enter center_row center_col radius: "); scanf("%d%d%d",&p[0],&p[1],&p[2]);
            break;
        case 3:
            obj.type = OBJ_RECT;
            printf("Enter r1 c1 r2 c2: "); scanf("%d%d%d%d",&p[0],&p[1],&p[2],&p[3]);
            break;
        case 4:
            obj.type = OBJ_TRIANGLE;
            printf("Enter r1 c1 r2 c2 r3 c3: "); scanf("%d%d%d%d%d%d",&p[0],&p[1],&p[2],&p[3],&p[4],&p[5]);
            break;
        default: printf("Invalid!\n"); return;
    }
    objects[objCount++] = obj;
    redrawAll();
    printf("Object added with ID %d\n", objCount - 1);
}

// ─── Delete Object ────────────────────────────────────────────────────────────
void deleteObject() {
    listObjects();
    printf("Enter object ID to delete: ");
    int id; scanf("%d", &id);
    if (id < 0 || id >= objCount || !objects[id].active) {
        printf("Invalid ID.\n"); return;
    }
    objects[id].active = 0;
    redrawAll();
    printf("Object %d deleted.\n", id);
}

// ─── Modify Object ────────────────────────────────────────────────────────────
void modifyObject() {
    listObjects();
    printf("Enter object ID to modify: ");
    int id; scanf("%d", &id);
    if (id < 0 || id >= objCount || !objects[id].active) {
        printf("Invalid ID.\n"); return;
    }
    objects[id].active = 0;  // temporarily remove
    printf("Re-enter parameters for the object:\n");
    int *p = objects[id].params;
    switch (objects[id].type) {
        case OBJ_LINE:
            printf("Enter r1 c1 r2 c2: "); scanf("%d%d%d%d",&p[0],&p[1],&p[2],&p[3]); break;
        case OBJ_CIRCLE:
            printf("Enter center_row center_col radius: "); scanf("%d%d%d",&p[0],&p[1],&p[2]); break;
        case OBJ_RECT:
            printf("Enter r1 c1 r2 c2: "); scanf("%d%d%d%d",&p[0],&p[1],&p[2],&p[3]); break;
        case OBJ_TRIANGLE:
            printf("Enter r1 c1 r2 c2 r3 c3: "); scanf("%d%d%d%d%d%d",&p[0],&p[1],&p[2],&p[3],&p[4],&p[5]); break;
    }
    objects[id].active = 1;
    redrawAll();
    printf("Object %d modified.\n", id);
}

// ─── Input Helper ─────────────────────────────────────────────────────────────
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ─── Main Menu ────────────────────────────────────────────────────────────────
int main() {
    initCanvas();
    int choice;
    do {
        printf("\n====== 2D Graphics Editor ======\n");
        printf("1. Add Object\n");
        printf("2. Delete Object\n");
        printf("3. Modify Object\n");
        printf("4. Display Canvas\n");
        printf("5. List All Objects\n");
        printf("6. Clear Canvas\n");
        printf("0. Exit\n");
        printf("Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input! Please enter a number.\n");
            clearInputBuffer();
            choice = -1;
            continue;
        }
        switch (choice) {
            case 1: addObject();    break;
            case 2: deleteObject(); break;
            case 3: modifyObject(); break;
            case 4: displayCanvas(); break;
            case 5: listObjects();  break;
            case 6: initCanvas(); objCount = 0; printf("Canvas cleared.\n"); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 0);
    return 0;
}