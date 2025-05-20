# Manifesting dulu
Liat tiap `readme.md` yang gw buat dan ada berapa update? Itu adalah bukti kalau walaupun dengan contoh kecil dan biasa begini gw bisa belajar banyak. Kalau gw bisa, kalian juga bisa.

# (Update 20/05/2025) Apa manfaatnya buat hidup manusia?
Dengan gw belajar `cooperative programming`, gw bisa utilisasi multitasking di bahasa pemograman tingkat rendah seperti C atau C++ bahkan Arduino (Hayo anak-anak IT yang kuliahnya ada kelas embeded pasti melotot kalau ngulik apa yang gw kulik disini) pada sistem ber-single-threaded (bahasa pemograman modern kayak Javascript dan Python dong?)

Selain itu gw jadi ngerti kenapa ada `yield` atau `coroutine`, bahkan setiap pendekatannya serupa dengan `async/await` yang gw sendiri pengen lakuin.

Oh iya, dan ini **cocok untuk kalian yang lagi ada di mata kuliah pemograman dasar dengan menggunakan C** atau pakai C++ (bukan C/C++ ya) dan pastiin ini kompatibel di OS kalian. Gw sendiri di Windows, lu gimana? Pastiin bisa jelasinnya ya *wink

# (Update 20/05/2025) Saran susur folder
Udah banyak folder bukan berarti satu-satu disusur, enggak ya. Semua contoh multitasking di sini pakai makro `yield` yang memanfaatkan teknik `switch-case` seperti `Duff's Device` untuk menyimpan dan melanjutkan eksekusi di titik tertentu, dan dari urutan `blatant_version` sampai `_example` adalah perkembangan dari day-0 sampai day-N. 

Saran gw bisa mulai dari 
1. `common_asyncwait_example` karena disana sudah kucoba untuk simplifikasi pemakaian / perakitan dari `coroutine`, `coroutine scheduler`, `interval` dan `fungsi "await"`, kemudian,
2. `duff_device_version` dengan banyak task/coroutine lebih dari dua, dan kalian akan melihat struktur `coroutine` yang ditambah variabelnya, memang begitu karena kita rakit sendiri/manual coroutinenya bebas terserah, yang penting ada `state machine` dan mungkin `interval` juga `data`,
3. `message_passing_example` disini udah mulai praktek `timeout` kayak `async` dari Javascript dengan contoh `passing message`,
4. `with_mutex` disini belajar belakang layar `mutex` dengan sederhana, gw yakin dengan cooperative multitasking ini tidak seutuhnya terjadi race condition karena semua proses berjalan dengan harmonis dan saling kooperatif (hence it's called cooperative multitasking)

Saran gw diatas akan berubah, dan yang gw rasa udah jadi semacam kertas coret=coret=an nantinya gw tandain. Jadi kalian enggak perlu susah-susah susur foldernya.

## Kok ada folder-foldernya?
Iya, karena konsep coroutine enggak sesimpel yang ada pada `blatant_version`. Gw ada salah, bukan berarti menghalang gw untuk belajar. 

+ `blatant_version`; versi naif untuk menghibur diri kalau elu(gw) bisa lakuin cooperative multitasking.

+ `duff_device`; gw udah mulai engeh yang diambil dari duff's device adalah pola switch-case yang unik, bisa diadaptasi untuk bikin state-machine coroutine. Dari sisi ilmu, ini jatuhnya "lompat" karena ada yang lebih ribet pakai stack terpisah dan mekanisme switch yang berat.

+ `message_passing_example`; Update 18/05/2025 contoh send receive yang isi pesannya di bawa didalam coroutine/task. Dan ini terakhir gw pakai duff's device. Setelahnya gw pakai `green thread`

+ `common_asyncwait_example`; Update 20/05/2025 gw ngide dari contoh `message_passing_example` bisa enggak gw bikin dengan style contoh-contoh umum untuk `async/await`, pendekatannya mirip dengan `message_passing`, tapi ada yang kurang. Dan gw belum pakai `green thread`

+ `preemptivestyle_cooperative_scheduler`; Update 20/05/2025 gw coba untuk pakai gaya preemptive dengan memaksa task/coroutine yield oleh timer/interupt dan tetep bisa single-thread

+ `with_mutex`; ini tambahan ngomong-ngomong dan btw gw engeh satu hal. Dari dua contoh versi diatas (padahal sama-sama aja, cuman dari duff's device lebih dalem lagi kenapa ada macro `yield`, `begin` dan `end`) adalah masing-masing coroutine / task punya data / counter masing-masing. Bisa enggak gw pakai satu dua variabel "global" yang diakses oleh coroutine secara bebarengan? Ajimumpung belajar `mutex` cuy.

# Latar Belakang
Oke, gw pelajarin ada satu fungsi yang namanya `MQTTClient_yield(void)` yang isinya adalah ~~konteks switching. Untuk sementara itu dulu sih~~ (update 20/05/2025) memindahkan proses fetch alamat / topik, berdasarkan tempo interval yang udah kita berikan mau baca berapa ms.

# Buat gw, rekomendasi runtutan belajar
1. Pelajari dulu coroutine dari tingkah lakunya: Misal, gimana coroutine bisa berhenti ditengah, dan lanjut lagi.
2. Eksperimen dengan API, misal Win32 Fiber karena coroutine level OS, katanya sih gampang dan cukup cepat.
3. Bikin sendiri stackful coroutine pakai malloc + manual context switching (`setjmp` atau bahkan asm)
4. Pelajari libtask


## Gimana kabar gw dari rekomendasi gw sendiri?
Update 20/05/2025; Gw lagi eksplor di `coroutine`, kenapa pakai `yield` dan dampaknya ke `cooperative multitasking`, dan ternyata teknik multitasking ini serupa dengan `async/await` yang bersingle-threaded dan cocok untuk nganu.