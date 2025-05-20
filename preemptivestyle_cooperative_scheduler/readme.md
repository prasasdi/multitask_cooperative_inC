# Apa ini?
Kita fokus di skeduler coroutine. Ada enggak metode yang bisa kita buat untuk mengembangkan lebih lagi scheduler yang udah kita pakai selama dua - tiga kode terakhir

Gw buat header terpisah untuk scheduler coroutine sendiri dan juga bungkus coroutine jadi satu header dengan scheduler, nantinya kita tinggal bikin `task_func` dan `run_scheduler` aja

```c
int task_func1(Coroutine* coro) {
    CORO_BEGIN(coro);
    printf("[Task %d] Hello, sleeping...\n", coro->id);
    coro->wakeup_time = now_ms() + 1000;
    while (now_ms() < coro->wakeup_time)
        CORO_YIELD(coro);
    printf("[Task %d] Done\n", coro->id);
    CORO_END(coro);
}

int main(void) {
    await(task_func1);
    run_scheduler();
    return 0;
}
```