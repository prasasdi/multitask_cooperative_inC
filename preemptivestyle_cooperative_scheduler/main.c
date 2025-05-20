#include <stdio.h>
#include "task_scheduler.h"

// Contoh task
int task_func1(Coroutine* coro) {
    CORO_BEGIN(coro);
    printf("[Task %d] Hello, sleep...\n", coro->id);
    coro->wakeup_time = now_ms() + 1000;
    while (now_ms() < coro->wakeup_time) {
        CORO_YIELD(coro);
        printf("[Task %d] Hello, sleeping...\n", coro->id);
    }
    printf("[Task %d] Done\n", coro->id);
    CORO_END(coro);
}

int task_func2(Coroutine* coro) {
    CORO_BEGIN(coro);
    printf("[Task %d] Hello, i am working...\n", coro->id);
    coro->wakeup_time = now_ms() + 2000;
    while (now_ms() < coro->wakeup_time) {
        printf("[Task %d] Oh, hi...\n", coro->id);
        CORO_YIELD(coro);
    }
    printf("[Task %d] Done\n", coro->id);
    CORO_END(coro);
}

int main(void) {
    await(task_func1);
    await(task_func2);
    run_scheduler();
    return 0;
}
