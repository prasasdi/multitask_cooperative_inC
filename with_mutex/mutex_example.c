/*
Ini contoh implementasi sementara dari mutex, dengan stdatomic.h, iya ada error. Tapi percaya deh, secara kayak gini;

> atomic_flag adalah flag boolean atomik yang mendukung operasi test-and-set secara atomik.
> Fungsi atomic_flag_test_and_set akan meng-set flag ke true dan mengembalikan nilai sebelumnya, jadi kita bisa tahu apakah flag sudah terkunci.
> Jika sudah terkunci, loop akan terus berjalan (spin) sampai flag dibebaskan.
> Ini adalah spinlock, bukan blocking mutex, jadi cocok untuk cooperative multitasking atau di mana blocking tidak diperlukan.

Ada yang lebih kompleks, tapi yang jelas sudah tidak portabel dan tidak terbatas. Untuk versi ini adalah versi yang amat sangat terbatas (ya iyalah portabel)
*/

#include <stdatomic.h>

typedef struct {
    atomic_flag locked;
} mutex_t;

// Inisialisasi mutex
void mutex_init(mutex_t *m) {
    atomic_flag_clear(&m->locked);
}

// Lock mutex (spinlock)
void mutex_lock(mutex_t *m) {
    // Tunggu sampai bisa mengambil lock
    while (atomic_flag_test_and_set(&m->locked)) {
        // spin wait
    }
}

// Unlock mutex
void mutex_unlock(mutex_t *m) {
    atomic_flag_clear(&m->locked);
}
