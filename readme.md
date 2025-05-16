# Kok ada folder-foldernya?
Iya, karena konsep coroutine enggak sesimpel yang ada pada `blatant_version` dan pemikiran tolol gw. Gw ada salah, bukan berarti menghalang gw untuk belajar. 

+ `blatant_version`; versi tolol banget buat menghibur diri kalau elu(gw) bisa lakuin cooperative multitasking.

+ `duff_device`; gw udah mulai engeh yang diambil dari duff's device adalah pola switch-case yang unik, bisa diadaptasi untuk bikin state-machine coroutine. Dari sisi ilmu, ini jatuhnya "lompat" karena ada yang lebih ribet pakai stack terpisah dan mekanisme switch yang berat.

+ `with_mutex`; btw gw engeh satu hal. Dari dua contoh versi diatas (padahal sama-sama aja, cuman dari duff's device lebih dalem lagi kenapa ada macro `yield`, `begin` dan `end`) adalah masing-masing coroutine / task punya data / counter masing-masing. Bisa enggak gw pakai satu dua variabel "global" yang diakses oleh coroutine secara bebarengan? Ajimumpung belajar `mutex` cuy.

# Latar Belakang
Oke, gw pelajarin ada satu fungsi yang namanya `MQTTClient_yield(void)` yang isinya adalah konteks switching. Untuk sementara itu dulu sih

# Buat gw, rekomendasi runtutan belajar
1. Pelajari dulu coroutine dari tingkah lakunya: Misal, gimana coroutine bisa berhenti ditengah, dan lanjut lagi.
2. Eksperimen dengan API, misal Win32 Fiber karena coroutine level OS, katanya sih gampang dan cukup cepat.
3. Bikin sendiri stackful coroutine pakai malloc + manual context switching (`setjmp` atau bahkan asm)
4. Pelajari libtask