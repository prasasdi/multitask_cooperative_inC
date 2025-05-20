# Ini minjem dari `message_passing_example`

# Compiler dan flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -O2
LDFLAGS = 

# Target dan sumber
TARGETS = main.exe main_w_timeout.exe

all: $(TARGETS)

# Build main.exe dari main.c
main.exe: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build main_w_timeout.exe dari main_w_timeout.c
main_w_timeout.exe: main_w_timeout.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule untuk .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: main.exe
	./main.exe

run_timeout: main_w_timeout.exe
	./main_w_timeout.exe

clean:
	del /Q *.o *.exe *.asm 2>nul || exit 0

asm: 
	$(CC) $(CFLAGS) -S -masm=intel main.c -o main.asm
	$(CC) $(CFLAGS) -S -masm=intel main_w_timeout.c -o main_w_timeout.asm
