# 2D Graphics Editor in C

[![C Build & Test CI](https://github.com/chinmaymusale123/graphics-editor-c/actions/workflows/ci.yml/badge.svg)](https://github.com/chinmaymusale123/graphics-editor-c/actions/workflows/ci.yml)
[![Language: C99](https://img.shields.io/badge/Language-C99-00599C?style=flat&logo=c)](https://en.wikipedia.org/wiki/C99)
[![Compiler: GCC](https://img.shields.io/badge/Compiler-GCC-green.svg)](https://gcc.gnu.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

A lightweight, menu-driven **2D Terminal Graphics Editor** written in pure C. It renders geometric primitives directly onto a 2D character array canvas using classical computer graphics rasterization algorithms without external graphics library dependencies.

---

## Visual Canvas Preview

```text
____________________________________________________________
_____********************___________________________________
_____*__________________*__________________****_____________
_____*__________________*________________**____**___________
_____*__________________*_______________*________*__________
_____*__________________*_______________*________*__________
_____*__________________*________________**____**___________
_____********************__________________****_____________
____________________________________________________________
```

---

## Features

- **25×60 Character Canvas Grid:** Canvas initialized with `_` (empty pixels) and drawn with `*` (active pixels).
- **Geometric Primitives:**
  - **Line:** Arbitrary orientation with slope interpolation.
  - **Circle:** Outlined radius drawing using 8-way symmetry.
  - **Rectangle:** 4-edge aligned bounding boxes.
  - **Triangle:** 3-vertex connected wireframe.
- **Interactive Object Management:**
  - **Object Store:** Tracks up to 50 active objects with unique IDs.
  - **Non-destructive Modification:** Modify coordinates of existing shapes by ID.
  - **Delete by ID:** Deletes a specific object and automatically redraws the canvas.
  - **Canvas Clear & Redraw:** Reset canvas state instantly.
- **Input Sanitization:** Safe input buffer flushing to prevent infinite loops on invalid input.

---

## Computer Graphics Algorithms

### 1. Bresenham's Integer Line Algorithm
Used for drawing lines, rectangles, and triangles. It avoids costly floating-point divisions by tracking error increments with integer arithmetic:

$$\Delta r = |r_2 - r_1|, \quad \Delta c = |c_2 - c_1|$$

At each step along the dominant axis, an integer decision parameter determines whether to increment the perpendicular coordinate.

### 2. Midpoint Circle Algorithm
Used for circles. Computes pixel coordinates for one octant $(0 \le x \le y)$ using second-order finite differences:

$$d = 1 - r$$

The remaining 7 octants are plotted simultaneously through 8-way reflection symmetry, minimizing arithmetic operations.

---

## Project Structure

```
graphics-editor-c/
├── .github/
│   └── workflows/
│       └── ci.yml             # Automated GCC build & test workflow
├── tests/
│   └── test_shapes.c          # Headless automated unit tests for raster algorithms
├── .gitignore                 # Binary and IDE ignore rules
├── Makefile                   # Cross-platform build script
├── graphics_editor.c          # Main interactive graphics editor application
└── README.md
```

---

## Build & Run

### Prerequisites
- GCC / Clang compiler
- `make` utility (optional, direct GCC commands supported)

### Using Make (Linux / macOS / MinGW)

```bash
# Build the editor
make

# Run the application
./graphics_editor        # On Windows: graphics_editor.exe

# Run automated shape unit tests
make test

# Clean compiled binaries
make clean
```

### Manual Compilation with GCC

**Windows (PowerShell / Command Prompt):**
```bash
gcc -Wall -Wextra -std=c99 -O2 graphics_editor.c -o graphics_editor.exe -lm
.\graphics_editor.exe
```

**Linux / macOS:**
```bash
gcc -Wall -Wextra -std=c99 -O2 graphics_editor.c -o graphics_editor -lm
./graphics_editor
```

---

## Automated Testing

An automated test suite verifies line, circle, rectangle, and triangle rasterization without requiring interactive console inputs:

```bash
# Compile and run headless shape tests
gcc -Wall -Wextra -std=c99 tests/test_shapes.c -o test_shapes -lm
./test_shapes
```

Output:
```text
Running 2D Graphics Editor Shape Tests:
----------------------------------------
  [PASS] Canvas initialization (25x60)
  [PASS] Pixel bounds checking
  [PASS] Bresenham line algorithm (horizontal & vertical)
  [PASS] Midpoint circle algorithm (symmetry points verified)
  [PASS] Rectangle rasterization
  [PASS] Triangle 3-edge rasterization
----------------------------------------
All shape rasterization tests passed successfully!
```

---

## Author

**Chinmay Musale**  
GitHub: [@chinmaymusale123](https://github.com/chinmaymusale123) | [LinkedIn](https://www.linkedin.com/in/chinmay-musale-97b23432a)

---

## License

This project is licensed under the [MIT License](LICENSE).