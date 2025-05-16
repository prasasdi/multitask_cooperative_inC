#include <stdio.h>
#include <string.h>

typedef struct {
    int state;
    int data; // dipakai sebagai loop counter umum
    // simpan nilai fibonaci
    int fiboa; // simpan 'a'
    int fibob; // simpan 'b'
} Coroutine;

#define CORO_BEGIN(coro) switch((coro)->state) { case 0:
#define CORO_YIELD(coro) do { (coro)->state = __LINE__; return; case __LINE__:; } while (0)
#define CORO_END(coro) } (coro)->state = -1; return;

void task0(Coroutine* c) { // counting up
    CORO_BEGIN(c);
    for (c->data = 1; c->data <= 3; ++c->data) {
        printf("[task0] count: %d\n", c->data);
        CORO_YIELD(c);
    }
    CORO_END(c);
}

void task1(Coroutine* c) { // countdown
    CORO_BEGIN(c);
    for (c->data = 3; c->data >= 1; --c->data) {
        printf("[task1] countdown: %d\n", c->data);
        CORO_YIELD(c);
    }
    CORO_END(c);
}

void task2(Coroutine* c) { // print even numbers
    CORO_BEGIN(c);
    for (c->data = 0; c->data <= 4; c->data += 2) {
        printf("[task2] even: %d\n", c->data);
        CORO_YIELD(c);
    }
    CORO_END(c);
}

void task3(Coroutine* c) {
    CORO_BEGIN(c);

    // inisialisasi hanya sekali saat state=0
    if (c->state == 0) {
        c->fiboa = 0;  // a
        c->fibob = 1;  // b
    }

    for ( ; c->data < 12; ++c->data) {
        printf("[task3] fib: %d\n", c->fiboa);
        int next = c->fiboa + c->fibob;
        c->fiboa = c->fibob;
        c->fibob = next;
        CORO_YIELD(c);
    }

    CORO_END(c);
}

void task4(Coroutine* c) { // delay simulation
    CORO_BEGIN(c);
    for (c->data = 0; c->data < 8; ++c->data) {
        printf("[task4] sleeping...\n");
        CORO_YIELD(c);
        printf("[task4] woke up\n");
        CORO_YIELD(c);
    }
    CORO_END(c);
}

void task5(Coroutine* c) {
    static const char* pattern[] = {"OFF", "ON", "ON", "OFF"};
    CORO_BEGIN(c);

    if (c->state == 0) {
        c->data = 0;
    }

    for (; c->data < 4; ++c->data) {
        printf("[task5] LED: %s\n", pattern[c->data]);
        CORO_YIELD(c);
    }

    CORO_END(c);
}

void task6(Coroutine* c) { // count chars
    CORO_BEGIN(c);
    {
        const char* str = "DuffsDevice";
        for (c->data = 0; str[c->data]; ++c->data) {
            printf("[task6] char: %c\n", str[c->data]);
            CORO_YIELD(c);
        }
    }
    CORO_END(c);
}

void task7(Coroutine* c) { // simulate sensor read
    CORO_BEGIN(c);
    for (c->data = 0; c->data < 4; ++c->data) {
        int fake_read = 100 + c->data * 5;
        printf("[task7] sensor: %d\n", fake_read);
        CORO_YIELD(c);
    }
    CORO_END(c);
}

void task8(Coroutine* c) { // bit toggling
    CORO_BEGIN(c);
    {
        int bit = 0;
        for (c->data = 0; c->data < 5; ++c->data) {
            bit ^= 1;
            printf("[task8] bit: %d\n", bit);
            CORO_YIELD(c);
        }
    }
    CORO_END(c);
}

void task9(Coroutine* c) { // show progress
    CORO_BEGIN(c);
    for (c->data = 0; c->data <= 100; c->data += 10) {
        printf("[task9] progress: %d%%\n", c->data);
        CORO_YIELD(c);
    }
    CORO_END(c);
}

#define MAX_TASKS 10

int main(void) {
    Coroutine tasks[MAX_TASKS] = {0};
    memset(tasks, 0, sizeof(tasks));  // Inisialisasi semua field di semua Coroutine ke 0

    void (*task_funcs[MAX_TASKS])(Coroutine*) = {
        task0
        , task1
        , task2
        , task3
        , task4
        , task5
        , task6
        , task7
        , task8
        , task9
    };

    int active;
    do {
        active = 0;
        for (int i = 0; i < MAX_TASKS; ++i) {
            if (tasks[i].state != -1) {
                task_funcs[i](&tasks[i]);
                if (tasks[i].state != -1)
                    active = 1;
            }
        }
    } while (active);

    printf("All tasks finished.\nEnter to exit.");
    getchar();

    return 0;
}
