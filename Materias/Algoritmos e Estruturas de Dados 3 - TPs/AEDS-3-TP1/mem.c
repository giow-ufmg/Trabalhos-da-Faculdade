// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                NÃO MODIFIQUE ESTE ARQUIVO!               =
// = Ou modifique, não sou seu rei! Sou só um aviso...        =
// = Faça-o por sua conta e risco. Não poderei ajudar caso    =
// = você o faça.                                             =
// =                                                          =
// = Lembre-se que, na hora de compilar, usarei este arquivo  =
// = da forma como ele está agora!                            =
// =----------------------------------------------------------=

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "mem.h"

#define BUCKETS 10240

static unsigned int mathias_memory_peak = 0;
static unsigned int mathias_memory_using = 0;

struct PtrT {
    void* ptr;
    unsigned int size;
    struct PtrT* next;
};

static struct PtrT mathias_buckets[BUCKETS];

void _mathias_memory_init() {
    for (int i = 0; i < BUCKETS; ++i) {
        mathias_buckets[i].ptr = NULL;
        mathias_buckets[i].size = 0;
        mathias_buckets[i].next = NULL;
    }
}

unsigned int _mathias_memory_get_bucket(void* ptr) {
    uintptr_t n = (uintptr_t) ptr;
    return (unsigned int)(n % BUCKETS);
}

struct PtrT* _mathias_memory_find(void* ptr) {
    unsigned int bucket = _mathias_memory_get_bucket(ptr);

    struct PtrT* query = mathias_buckets[bucket].next;
    while (query != NULL && query->ptr != ptr) {
        query = query->next;
    }

    return query;
}

void _mathias_memory_add(void* ptr, unsigned int size) {
    struct PtrT* find = _mathias_memory_find(ptr);
    struct PtrT* new = find;

    if (find == NULL) {
        unsigned int bucket = _mathias_memory_get_bucket(ptr);
        new = malloc(sizeof(struct PtrT));
        new->next = mathias_buckets[bucket].next;
        mathias_buckets[bucket].next = new;
    }

    new->ptr = ptr;
    new->size = size;
}

unsigned int get_memory_peak() {
    return mathias_memory_peak;
}

unsigned int get_memory_using() {
    return mathias_memory_using;
}

void* mathias_malloc(unsigned int size) {
    void* ptr = malloc(size);

    if (ptr != NULL) {
        mathias_memory_using += size;
    } else {
        fprintf(stderr, "NÃO FOI POSSÍVEL ALOCAR `%u` BYTES DE MEMÓRIA.\n", size);
        exit(1);
    }

    if (mathias_memory_using > mathias_memory_peak) {
        mathias_memory_peak = mathias_memory_using;
    }

    _mathias_memory_add(ptr, size);

    return ptr;
}

void mathias_free(void* ptr) {
    struct PtrT* find = _mathias_memory_find(ptr);

    if (find == NULL) {
        fprintf(stderr, "VOÇÊ SÓ PODE EXECUTAR `free` EM MEMÓRIA ALLOCADA POR `mathias_malloc`.\n");
        exit(1);
    } else {
        mathias_memory_using -= find->size;
    }

    free(ptr);
}

