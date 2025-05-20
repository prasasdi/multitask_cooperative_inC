#include <stdint.h>
#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
    #define sleep_ms(ms) Sleep(ms)
    uint64_t now_ms() { return GetTickCount64(); }
#else
    #include <sys/time.h>
    #include <unistd.h>
    #define sleep_ms(ms) usleep((ms)*1000)
    uint64_t now_ms() {
        struct timeval tv; gettimeofday(&tv, NULL);
        return (uint64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
    }
#endif

#define CORO_BEGIN(c) switch((c)->state) { case 0:
#define CORO_YIELD(c) do { (c)->state = __LINE__; return 1; case __LINE__:; } while (0)
#define CORO_END(c) } (c)->state = -1; return 0;

typedef struct {
    int id;
    int state;
    uint64_t wakeup_time;
} Coroutine;

// Task function signature
typedef int (*TaskFunc)(Coroutine*);

// Contoh coroutine 1: delay 3 detik lalu print goodbye
int task_func1(Coroutine* coro) {
    CORO_BEGIN(coro);

    printf("[Task %d] Hello from task_func1, sleeping 3000ms\n", coro->id);
    coro->wakeup_time = now_ms() + 3000;

    while (now_ms() < coro->wakeup_time)
        CORO_YIELD(coro);

    printf("[Task %d] Goodbye from task_func1\n", coro->id);

    CORO_END(coro);
}

// Contoh coroutine 2: delay 1 detik lalu print message, ulang 3 kali
int task_func2(Coroutine* coro) {
    static int count;
    CORO_BEGIN(coro);

    for (count = 0; count < 3; count++) {
        printf("[Task %d] task_func2 iteration %d, sleeping 5000ms\n", coro->id, count+1);
        coro->wakeup_time = now_ms() + 5000;

        while (now_ms() < coro->wakeup_time)
            CORO_YIELD(coro);
    }

    printf("[Task %d] task_func2 finished\n", coro->id);

    CORO_END(coro);
}

// Scheduler menerima array coroutine dan array task function
void scheduler(Coroutine* coros, TaskFunc* funcs, int count) {
    int active = count;

    while (active > 0) {
        active = 0;
        for (int i = 0; i < count; i++) {
            if (coros[i].state != -1) {
                int running = funcs[i](&coros[i]);
                if (running) active++;
            }
        }
        sleep_ms(100);
    }
}

#define MAX_COROUTINES 2

int main(void) {
    Coroutine coros[MAX_COROUTINES] = {0};
    coros[0].id = 1;
    coros[1].id = 2;

    TaskFunc funcs[MAX_COROUTINES] = {task_func1, task_func2};

    printf("Hello from main thread\n");

    scheduler(coros, funcs, MAX_COROUTINES);

    printf("Goodbye from main thread\n");
    return 0;
}
