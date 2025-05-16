
# BEGIN, YIELD dan END itu apaan?
## `yield`
kalau `yield` di courutines (Go misalnya), artinya adalah menyerahkan eksekusi sementara, mirip dan serupa dengan cooperative multitasking.

Tambahan(17/05/2025 1:00): coroutine semacam "fungsi" yang bisa di pause (yield) dan lanjut lagi dari titik terakhir (resume) dan dikendalikan oleh program (user-space). Arti multitasking disini berarti satu thread bisa "menjalankan beberapa coroutine" seolah paralel, padahal gantian. Jadinya, pada dasarnya program ini tidak memanfaatkan thread, tapi satu thread yang sama cuman gantian aja. Emang sih

> nanti gw tambahin waktu dimana gw ada update readme gw kayak diatas ini

Kalau di C#, `yield return` untuk iterator yang mirip generator, generator disini bisa kita pinjam definisinya dari `python` yang berarti menghasilkan nilai secara bertahap tanpa harus simpan semua hasil di memori. Beda ya, berarti `yield` dari kacamata C# adalah bermain dengan memori.

Akhirnya, konteks dari `yield` bisa:
1. Menghasilkan data secara bertahap dan,
2. menyerahkan kontrol eksekusi (coroutine/task switching)

Nah, task switiching atau coroutine ini yang kita "incar"

## `begin` dan `end`
Misal untuk task/thread, ada fungsi seperti `start()`, `create()`, atau konstraktor objek.

Buat coroutine / task, biasanya ada fungsi seperti `start()`, `resume()`, dan `stop()`, bukan istilah `begin` atau `end` secara eksplisit. Ini lebih ke sudokode yang didefinisikan untuk mempermudah aja sih.
