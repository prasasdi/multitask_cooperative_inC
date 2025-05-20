# Compiler dan flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -O2
LDFLAGS = 

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

# Target dan sumber
TARGETS = main.exe main_w_timeout.exe

all: $(TARGETS)

# Build main.exe
main.exe: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: main.exe
	./main.exe
	
clean:
	del /Q *.o *.exe *.asm 2>nul || exit 0

asm:
	$(CC) $(CFLAGS) -S -masm=intel main.c -o main.asm
	$(CC) $(CFLAGS) -S -masm=intel main_w_timeout.c -o main_w_timeout.asm
