# tl;dr
Relatif aman sih kalau cooperative multitasking menggunakan variabel yang sama, karena tau kapan `yield`nya 

# Terus apa?
Katanya sih untuk menangani race condition adalah pemanfaatan mutex. Untuk lock sebuah variabel / objek / entitas yang kemungkinan diakses bersamaan lebih dari satu task. Gitu sih

## Aseli agak bingung
### Interleaving of execution.
Kalau coroutine kamu yield di tempat yang aman, misalnya setelah update shared data selesai, ya race condition gak bakal muncul.
Tapi kalau yield di tengah update shared data (misalnya baca dulu, yield, baru tulis), bisa bikin race condition karena data bisa berubah di antara waktu baca dan tulis.

### Jumlah Task dan Kompleksitas Interaksi
Kalau cuma ada 2 task sederhana yang bergantian dan kamu kontrol yieldnya dengan rapi, kemungkinan besar aman. Tapi kalau:
+ Tasknya banyak (3, 4, ... N)
+ Task punya urutan yield yang tidak terduga
+ Ada kondisi yang membuat task yield di titik berbeda-beda
Maka kompleksitas dan kemungkinan race condition naik drastis.

### Operasi Asynchronous / IO / Event-driven
Kalau mulai gabungin cooperative multitasking dengan operasi asynchronous, misalnya IO, timer, event, dll, maka kompleksitas naik karena:
+ Event bisa datang kapan saja
+ Interleaving lebih rumit
+ Kesalahan sinkronisasi lebih sulit di-trace

## Kesimpulan 
Kompleksitas di multitasking cooperative muncul dari:
+ Banyaknya task dan cara mereka yield
+ Titik yield di tengah operasi kritikal
+ Kompleksitas shared data
+ Interaksi dengan IO/event
+ Manajemen proteksi data (lock, mutex)
