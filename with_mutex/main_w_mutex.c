#include <stdio.h>
#include <stdatomic.h>

typedef struct {
    int state;
} Coroutine;

#define CORO_BEGIN(coro) switch((coro)->state) { case 0:
#define CORO_YIELD(coro) do { (coro)->state = __LINE__; return; case __LINE__:; } while (0)
#define CORO_END(coro) } (coro)->state = -1; return;

typedef struct {
    atomic_flag locked;
    int owner_task_id;  // ID task yang pegang lock, -1 kalau kosong
} mutex_t;

void mutex_init(mutex_t *m) {
    atomic_flag_clear(&m->locked);
    m->owner_task_id = -1;
}

int mutex_try_lock(mutex_t *m, int task_id) {
    if (!atomic_flag_test_and_set(&m->locked)) {
        m->owner_task_id = task_id;
        return 1;
    }
    return 0;
}

int mutex_unlock(mutex_t *m, int task_id) {
    if (m->owner_task_id != task_id) {
        printf("ERROR: Task %d mencoba unlock tapi bukan pemilik (owner = %d)\n", task_id, m->owner_task_id);
        return 0; // gagal unlock
    }
    m->owner_task_id = -1;
    atomic_flag_clear(&m->locked);
    return 1;
}

// Shared data dan mutex
int shared_counter = 0;
mutex_t lock;

// Task A
void taskA(Coroutine *coro) {
    static int step = 0;
    CORO_BEGIN(coro);

    while (1) {
        printf("Task A mencoba lock\n");
        while (!mutex_try_lock(&lock, 1)) {
            CORO_YIELD(coro);
        }
        printf("Task A dapat lock\n");

        int local = shared_counter;
        local++;
        printf("Task A update shared_counter: %d -> %d\n", shared_counter, local);
        shared_counter = local;

        if (step == 0) {
            printf("Task A akan gagal unlock (simulasi)\n");
            // Simulasi unlock oleh task lain (unlock ilegal)
            mutex_unlock(&lock, 2);  // task_id 2 coba unlock, bukan owner
            step++;
        }

        // Baru task A unlock dengan benar
        if (!mutex_unlock(&lock, 1)) {
            printf("Task A gagal unlock\n");
        } else {
            printf("Task A unlock berhasil\n");
        }

        CORO_YIELD(coro);
    }

    CORO_END(coro);
}

// Task B
void taskB(Coroutine *coro) {
    CORO_BEGIN(coro);

    while (1) {
        printf("Task B mencoba lock\n");
        while (!mutex_try_lock(&lock, 2)) {
            CORO_YIELD(coro);
        }
        printf("Task B dapat lock\n");

        int local = shared_counter;
        local += 10;
        printf("Task B update shared_counter: %d -> %d\n", shared_counter, local);
        shared_counter = local;

        if (!mutex_unlock(&lock, 2)) {
            printf("Task B gagal unlock\n");
        } else {
            printf("Task B unlock berhasil\n");
        }

        CORO_YIELD(coro);
    }

    CORO_END(coro);
}

int main() {
    mutex_init(&lock);

    Coroutine coroA = {0};
    Coroutine coroB = {0};

    for (int i = 0; i < 5; i++) {
        taskA(&coroA);
        taskB(&coroB);
    }

    printf("Final shared_counter: %d\nEnter to exit.", shared_counter);
    getchar();
    return 0;
}
