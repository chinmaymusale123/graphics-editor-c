/**
 * test_shapes.c — Unit tests for 2D graphics raster algorithms.
 * Tests canvas initialization, Bresenham line algorithm, midpoint circle algorithm,
 * rectangle, and triangle drawing without interactive user prompts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define ROWS 25
#define COLS 60
#define EMPTY '_'
#define DRAW  '*'

char canvas[ROWS][COLS];

void initCanvas() {
    for (int i = 0; i < ROWS; i++)
        for (int j = 0; j < COLS; j++)
            canvas[i][j] = EMPTY;
}

void setPixel(int r, int c, char ch) {
    if (r >= 0 && r < ROWS && c >= 0 && c < COLS)
        canvas[r][c] = ch;
}

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
    drawLine(r1, c1, r1, c2, ch);
    drawLine(r2, c1, r2, c2, ch);
    drawLine(r1, c1, r2, c1, ch);
    drawLine(r1, c2, r2, c2, ch);
}

void drawTriangle(int r1, int c1, int r2, int c2, int r3, int c3, char ch) {
    drawLine(r1, c1, r2, c2, ch);
    drawLine(r2, c2, r3, c3, ch);
    drawLine(r3, c3, r1, c1, ch);
}

// ─── Test Cases ──────────────────────────────────────────────────────────────

void test_initCanvas() {
    initCanvas();
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            assert(canvas[i][j] == EMPTY);
        }
    }
    printf("  [PASS] Canvas initialization (25x60)\n");
}

void test_setPixel_bounds() {
    initCanvas();
    setPixel(0, 0, DRAW);
    assert(canvas[0][0] == DRAW);

    setPixel(ROWS - 1, COLS - 1, DRAW);
    assert(canvas[ROWS - 1][COLS - 1] == DRAW);

    // Negative coordinates & out of bounds should be safely ignored
    setPixel(-1, 0, DRAW);
    setPixel(0, -1, DRAW);
    setPixel(ROWS, 0, DRAW);
    setPixel(0, COLS, DRAW);
    printf("  [PASS] Pixel bounds checking\n");
}

void test_drawLine() {
    initCanvas();
    // Draw horizontal line
    drawLine(5, 10, 5, 20, DRAW);
    for (int c = 10; c <= 20; c++) {
        assert(canvas[5][c] == DRAW);
    }
    assert(canvas[5][9] == EMPTY);
    assert(canvas[5][21] == EMPTY);

    // Draw vertical line
    drawLine(2, 30, 8, 30, DRAW);
    for (int r = 2; r <= 8; r++) {
        assert(canvas[r][30] == DRAW);
    }
    printf("  [PASS] Bresenham line algorithm (horizontal & vertical)\n");
}

void test_drawCircle() {
    initCanvas();
    int cr = 12, cc = 30, radius = 6;
    drawCircle(cr, cc, radius, DRAW);

    // Cardinal points of the circle
    assert(canvas[cr + radius][cc] == DRAW);
    assert(canvas[cr - radius][cc] == DRAW);
    assert(canvas[cr][cc + radius] == DRAW);
    assert(canvas[cr][cc - radius] == DRAW);
    // Center remains untouched
    assert(canvas[cr][cc] == EMPTY);
    printf("  [PASS] Midpoint circle algorithm (symmetry points verified)\n");
}

void test_drawRectangle() {
    initCanvas();
    drawRectangle(2, 5, 10, 25, DRAW);
    // 4 Corners must be drawn
    assert(canvas[2][5] == DRAW);
    assert(canvas[2][25] == DRAW);
    assert(canvas[10][5] == DRAW);
    assert(canvas[10][25] == DRAW);
    // Interior remains empty
    assert(canvas[5][15] == EMPTY);
    printf("  [PASS] Rectangle rasterization\n");
}

void test_drawTriangle() {
    initCanvas();
    drawTriangle(2, 10, 10, 5, 10, 15, DRAW);
    // Vertices must be set
    assert(canvas[2][10] == DRAW);
    assert(canvas[10][5] == DRAW);
    assert(canvas[10][15] == DRAW);
    printf("  [PASS] Triangle 3-edge rasterization\n");
}

int main() {
    printf("Running 2D Graphics Editor Shape Tests:\n");
    printf("----------------------------------------\n");
    test_initCanvas();
    test_setPixel_bounds();
    test_drawLine();
    test_drawCircle();
    test_drawRectangle();
    test_drawTriangle();
    printf("----------------------------------------\n");
    printf("All shape rasterization tests passed successfully!\n");
    return 0;
}
