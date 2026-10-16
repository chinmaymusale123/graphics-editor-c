CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LDFLAGS = -lm

TARGET = graphics_editor
TEST_TARGET = test_shapes

ifeq ($(OS),Windows_NT)
    EXE = .exe
    RM = del /Q /F
else
    EXE =
    RM = rm -f
endif

all: $(TARGET)$(EXE)

$(TARGET)$(EXE): graphics_editor.c
	$(CC) $(CFLAGS) -o $(TARGET)$(EXE) graphics_editor.c $(LDFLAGS)

test: $(TEST_TARGET)$(EXE)
	./$(TEST_TARGET)$(EXE)

$(TEST_TARGET)$(EXE): tests/test_shapes.c
	$(CC) $(CFLAGS) -o $(TEST_TARGET)$(EXE) tests/test_shapes.c $(LDFLAGS)

clean:
	$(RM) $(TARGET)$(EXE) $(TEST_TARGET)$(EXE) *.o

.PHONY: all test clean
