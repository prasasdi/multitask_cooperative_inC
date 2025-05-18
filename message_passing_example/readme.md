# Ide
Kan udah tau multitasking, cuman jenis multitasking ini cooperative. Alangkah serunya kalau coba bikin sistem pasing. Dari gw sendiri ada catatan yang bisa gw sampaikan

# Coroutine
Mungkin kalian perhatiin dari tiap coroutine atau task, isi dari strukturnya beda-beda. Emang, karena tidak punya coroutine / task / generator native dari C sendiri. Jadi kita perlu definisikan sendiri. Terus juga enggak ada async/await (ya iyalah) bawaan.

## Pengen gw sih gini
Pengennya ya, yang receive ini perlu nunggu berapa `ms` sampai akhirnya timeout.

# With Timeout
Update 18/05/2025: Gw ngide untuk nambahin with timeout, replikasi kayak "websocket" yang ada timeoutnya. Tapii, alangkah baiknya kalau misal gw tambahin "timeout" ini di projek websocket beneran dimana service ini berjalan hanya untuk menerima pesan dari luar. 