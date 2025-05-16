#include <stdio.h>

typedef struct {
    int state;
} Coroutine;

#define CORO_BEGIN(coro) switch((coro)->state) { case 0:
#define CORO_YIELD(coro) do { (coro)->state = __LINE__; return; case __LINE__:; } while(0)
#define CORO_END(coro) } (coro)->state = -1; return;

int shared_counter = 0;

void taskA(Coroutine *coro) {
    CORO_BEGIN(coro);

    while (1) {
        printf("Task A mulai update shared_counter: %d\n", shared_counter);

        int local = shared_counter;
        local++;            // Tambah 1
        shared_counter = local;
        CORO_YIELD(coro);  
        
        printf("Task A selesai update shared_counter: %d\n", shared_counter);

        CORO_YIELD(coro);
    }

    CORO_END(coro);
}

void taskB(Coroutine *coro) {
    CORO_BEGIN(coro);

    while (1) {
        printf("Task B mulai update shared_counter: %d\n", shared_counter);

        int local = shared_counter;
        local += 10;         // Tambah 10
        shared_counter = local;
        CORO_YIELD(coro);    

        printf("Task B selesai update shared_counter: %d\n", shared_counter);

        CORO_YIELD(coro);
    }

    CORO_END(coro);
}

int main() {
    Coroutine coroA = {0};
    Coroutine coroB = {0};

    for (int i = 0; i < 5; i++) {
        taskA(&coroA);
        taskB(&coroB);
    }

    printf("Final shared_counter: %d\n", shared_counter);
    return 0;
}
