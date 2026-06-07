# 2D Graphics Editor in C

A menu-driven 2D Graphics Editor using a character array as the drawing canvas.

## Features
- Canvas: 25×60 grid initialized with `_` (underscore)
- Draw shapes using `*` (asterisk): Line, Circle, Rectangle, Triangle
- Add, Delete, and Modify objects
- Object list with IDs for easy management

## Build & Run
```bash
make
./graphics_editor
```

## Algorithms Used
- Bresenham's Line Algorithm for lines and rectangle edges
- Midpoint Circle Algorithm for circles
- Triangle drawn as 3 connected lines