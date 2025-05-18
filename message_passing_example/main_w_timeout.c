#include <stdio.h>
#include <stdlib.h>

#define MAX_COROUTINES 16
#define MSG_QUEUE_SIZE 8
#define MAX_SCHEDULER_LOOPS 20  // batasi iterasi agar tidak infinite loop

typedef struct coroutine {
    int state;
    int id;

    void *messages[MSG_QUEUE_SIZE];
    int msg_in;
    int msg_out;

    void (*func)(struct coroutine *c);
    int finished;

    int wait_counter;  // waktu timeout tunggu receive message
} coroutine;


typedef struct {
    coroutine *coros[MAX_COROUTINES];
    int count;
    int current;
} scheduler;

#define BEGIN(coro) switch((coro)->state) { case 0:
#define YIELD(coro) do { (coro)->state = __LINE__; return; case __LINE__:; } while (0)
#define END(coro) } (coro)->state = -1; (coro)->finished = 1; return;

void *receive_message_timeout(coroutine *c, int max_wait) {
    if (c->msg_out != c->msg_in) {
        c->wait_counter = 0; // Reset counter kalau ada message
        void *msg = c->messages[c->msg_out];
        c->msg_out = (c->msg_out + 1) % MSG_QUEUE_SIZE;
        printf("Coro %d received a message\n", c->id);
        return msg;
    } else {
        c->wait_counter++;
        if (c->wait_counter >= max_wait) {
            c->wait_counter = 0; // Reset biar bisa dipakai lagi nanti
            printf("Coro %d timeout waiting for message\n", c->id);
            return (void *)-1; // Sentinel: timeout
        }
        return NULL;
    }
}

int send_message(coroutine *target, void *msg) {
    int next_in = (target->msg_in + 1) % MSG_QUEUE_SIZE;
    if (next_in == target->msg_out) {
        printf("Queue full for coro %d, message lost\n", target->id);
        return 0;
    }
    target->messages[target->msg_in] = msg;
    target->msg_in = next_in;
    printf("Message sent to coro %d\n", target->id);
    return 1;
}

void *receive_message(coroutine *c) {
    if (c->msg_out == c->msg_in) {
        return NULL;
    }
    void *msg = c->messages[c->msg_out];
    c->msg_out = (c->msg_out + 1) % MSG_QUEUE_SIZE;
    printf("Coro %d received a message\n", c->id);
    return msg;
}

void coroutine_worker(coroutine *c) {
    BEGIN(c);

    while (1) {
        void *msg = receive_message_timeout(c, 3); // timeout setelah 3 scheduler loop

        if (msg == (void *)-1) {
            printf("[Coro %d] Timeout!\n", c->id);
        } else if (msg) {
            printf("[Coro %d] Received message: %s\n", c->id, (char *)msg);
        } else {
            printf("[Coro %d] No message, yield\n", c->id);
        }

        YIELD(c);
    }

    END(c);
}


void scheduler_init(scheduler *s) {
    s->count = 0;
    s->current = 0;
}

coroutine *scheduler_add(scheduler *s, void (*func)(coroutine *)) {
    if (s->count >= MAX_COROUTINES) return NULL;
    coroutine *c = malloc(sizeof(coroutine));
    c->state = 0;
    c->id = s->count;
    c->msg_in = 0;
    c->msg_out = 0;
    c->func = func;
    c->finished = 0;

    s->coros[s->count++] = c;
    return c;
}

void scheduler_run(scheduler *s) {
    int active = 1;
    int loop = 0;

    while (active && loop < MAX_SCHEDULER_LOOPS) {
        active = 0;
        printf("=== Scheduler loop %d ===\n", loop);
        for (int i = 0; i < s->count; i++) {
            coroutine *c = s->coros[i];
            if (!c->finished) {
                printf("Calling coro %d\n", c->id);
                c->func(c);
                active = 1;
            }
        }
        loop++;
    }

    if (loop == MAX_SCHEDULER_LOOPS) {
        printf("Scheduler stopped after max loops.\n");
    }
}

int main() {
    scheduler sched;
    scheduler_init(&sched);

    coroutine *c1 = scheduler_add(&sched, coroutine_worker);
    coroutine *c2 = scheduler_add(&sched, coroutine_worker);

    send_message(c1, "Hello from main to coro 1");
    send_message(c2, "Hello from main to coro 2");

    scheduler_run(&sched);

    // free memory
    for (int i = 0; i < sched.count; i++) {
        free(sched.coros[i]);
    }

    return 0;
}
