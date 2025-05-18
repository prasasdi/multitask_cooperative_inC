# Ide
Kan udah tau multitasking, cuman jenis multitasking ini cooperative. Alangkah serunya kalau coba bikin sistem pasing. Dari gw sendiri ada catatan yang bisa gw sampaikan

# Coroutine
Mungkin kalian perhatiin dari tiap coroutine atau task, isi dari strukturnya beda-beda. Emang, karena tidak punya coroutine / task / generator native dari C sendiri. Jadi kita perlu definisikan sendiri. Terus juga enggak ada async/await (ya iyalah) bawaan.

## Pengen gw sih gini
Pengennya ya, yang receive ini perlu nunggu berapa `ms` sampai akhirnya timeout. Pengennya sih