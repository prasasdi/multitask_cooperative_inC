#include <windows.h>
#include <stdio.h>

#define MAX_TASKS 3

typedef struct Task Task;
typedef void (*TaskFunc)(Task*);

typedef struct Task {
    TaskFunc func;
    int state;
    int is_done;
    int i;
} Task;


Task tasks[MAX_TASKS];
int task_count = 0;

#define BEGIN() switch(current->state) { case 0:
#define YIELD() do { current->state = __LINE__; return; case __LINE__:; } while (0)
#define END() } current->is_done = 1; return;    

void AddTask(TaskFunc func) {
    if (task_count < MAX_TASKS) {
        tasks[task_count].func = func;
        tasks[task_count].state = 0;
        tasks[task_count].is_done = 0;
        task_count++;
    }
}

// Task 1
void Task1(Task* current) {
    BEGIN();
    current->i = 0;
    while (current->i < 120) {
        printf("Task 1 - Step %d\n", current->i);
        Sleep(200);
        current->i++;
        YIELD();
    }
    END();
}


// Task 2
void Task2(Task* current) {
    BEGIN();
    current->i = 0;
    while (current->i < 3) {
        printf("Task 2 - Step %d\n", current->i);
        Sleep(300);
        current->i++;
        YIELD();
    }
    END();
}

// Task 3
void Task3(Task* current) {
    BEGIN();
    current->i = 0;
    while (current->i < 125) {
        printf("Task 3 - Step %d\n", current->i);
        Sleep(1);
        current->i++;
        YIELD();
    }
    END();
}

int main(void) {
    AddTask(Task1);
    AddTask(Task1);
    AddTask(Task3);

    int done;
    char* exitt;

    do {
        done = 1;
        for (int i = 0; i < task_count; i++) {
            if (!tasks[i].is_done) {
                tasks[i].func(&tasks[i]);
                done = 0;
            }
        }
    } while (!done);

    printf("Semua task selesai.\nPress any key to exit.");

    scanf("%c", exitt);
    return 0;
}
