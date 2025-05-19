# Menjalankan aplikasi
GW udah buatin `makefile`nya dan kalian tjukup dengan `make run` aja udah dapet.

# Harapannya begini
Tau tutorial `async/await` di bahasa pemograman yang lain? Entah Javascript, atau C# misalnya? Kayak gini kira-kira
```bash
Hello from main thread
Hello from task, doing sleep for 3000ms
Goodbye from main thread
... <<< setelah 3000 milisekon
Goodbye from task, after doing sleep for 3000ms
```
Kayak gitu idenya.

# Contoh kode
Dari contohnya udah mengarah ke ide dan harapan gw diatas tadi. Sekarang gw mengarah ke skeduler dan cara gw utilisasi `cross-platform` dengan `#if-#else`.

Btw, tetep dengan Duff's Defice untuk macro `yield` dan dengan `interval` untuk state waktu. Gw sendiri udah paham, kenapa ada `yield` dan apa maknanya, lu gimana?