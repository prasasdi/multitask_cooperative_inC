# Melompat jauh
Sebenarnya dari Duff;s Device kita ambil pola swtich-case uniknya yang bisa diadaptasi untuk bikin state machine coroutine supaya ringan dan efektif. Dan disinilah gw bilang "melompat jauh".

## Kenapa ringan dan efektif?
Sebenernya, coroutine di lower level language itu butuh stack terpisah dan mekanisme context switch. Enggak ada syscall, enggak perlu alokasi memori baru yang membuatnya hanya menggunakan satu `state` aja dan itu berarti ringan.

## Keterbatasannya?
Perlu dibuktikan sih di bagian ASM dan kita telaah lebih jauh lagi, karena keterbatasan ilmu gw pribadi, jadi gw terpaksa harus telan mentah-mentah dan menjadikan bagian ini adalah sebuah "opini", duh walopun gw enggak pengen.

# Kemana `yield`, `begin` dan `end`?
Ada kok, gw tambahin prefix `CORO_` aja