# Compiler dan flags
CC = x86_64-w64-mingw32-gcc
CFLAGS = -O2
LDFLAGS =

SRC_W_MUTEX = main_w_mutex.c
OBJ_W_MUTEX = $(SRC_W_MUTEX:.c=.o)
TARGET_W_MUTEX = main_w_mutex.exe

SRC_WO_MUTEX = main_wo_mutex.c
OBJ_WO_MUTEX = $(SRC_WO_MUTEX:.c=.o)
TARGET_WO_MUTEX = main_wo_mutex.exe

# Default target
all: $(TARGET_W_MUTEX) $(TARGET_WO_MUTEX)

$(TARGET_W_MUTEX): $(OBJ_W_MUTEX)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET_WO_MUTEX): $(OBJ_WO_MUTEX)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run_w_mutex: $(TARGET_W_MUTEX)
	./$(TARGET_W_MUTEX)

run_wo_mutex: $(TARGET_WO_MUTEX)
	./$(TARGET_WO_MUTEX)

clean:
	del /Q *.o *.exe 2>nul || exit 0

asm_w_mutex: $(SRC_W_MUTEX)
	$(CC) $(CFLAGS) -S -masm=intel $< -o $(SRC_W_MUTEX:.c=.asm)

asm_wo_mutex: $(SRC_WO_MUTEX)
	$(CC) $(CFLAGS) -S -masm=intel $< -o $(SRC_WO_MUTEX:.c=.asm)
