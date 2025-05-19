# Ide
Kan udah tau multitasking, cuman jenis multitasking ini cooperative. Alangkah serunya kalau coba bikin sistem pasing. Dari gw sendiri ada catatan yang bisa gw sampaikan

# Coroutine
Mungkin kalian perhatiin dari tiap coroutine atau task, isi dari strukturnya beda-beda. Emang, karena tidak punya coroutine / task / generator native dari C sendiri. Jadi kita perlu definisikan sendiri. Terus juga enggak ada async/await (ya iyalah) bawaan.

## Pengen gw sih gini
Pengennya ya, yang receive ini perlu nunggu berapa `ms` sampai akhirnya timeout.

# With Timeout
Update 18/05/2025: Gw ngide untuk nambahin with timeout, replikasi kayak "websocket" yang ada timeoutnya. Tapii, alangkah baiknya kalau misal gw tambahin "timeout" ini di projek websocket beneran dimana service ini berjalan hanya untuk menerima pesan dari luar. 

Update 19/05/2025: Akhirnya, datang saatnya gw utilize `interval` dan gw dapat seperti ini
```bash
=== Scheduler loop 1941 ===
Calling coro 0
Coro 0 waiting... 56 ms remaining before timeout
[Coro 0] No message, yield
Calling coro 1
Coro 1 waiting... 57 ms remaining before timeout
[Coro 1] No message, yield
=== Scheduler loop 1942 ===
Calling coro 0
Coro 0 waiting... 0 ms remaining before timeout
Coro 0 timeout waiting for message
[Coro 0] Timeout!
Calling coro 1
Coro 1 waiting... 0 ms remaining before timeout
Coro 1 timeout waiting for message
[Coro 1] Timeout!
```

Masih pakai Skeduler loop. Gw mau ganti kalau sudah 5x timeout. Langsung keluar
