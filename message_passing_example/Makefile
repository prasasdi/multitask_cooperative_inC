# Compiler dan flags
CC = x86_64-w64-mingw32-gcc
# CFLAGS = -Wall -Wextra -O2 -mwindows
CFLAGS = -O2
LDFLAGS = 
TARGET = main.exe
SRC = main.c
OBJ = $(SRC:.c=.o)

# Default target
all: build

build: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	del /Q *.o *.exe 2>nul || exit 0

asm:
	$(CC) $(CFLAGS) -S -masm=intel $(SRC) -o $(SRC:.c=.asm)
