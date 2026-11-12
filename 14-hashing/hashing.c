#include <stdlib.h>
#include <stdio.h>
#include "hashing.h"

Hash* criar_tabela(unsigned int n) {
    Hash* hash = (Hash*) malloc(sizeof(Hash));
    hash->dim = n;
    hash->max = n*0.7;
    hash->n = 0;
    hash->tabela = (Elem*) calloc(n, sizeof(Elem));
    return hash;
}

static unsigned int h1(unsigned int chave, int dim) {
    unsigned int fracao = ((long)chave * 2654435769); // 2654435769 é a razão áurea vezes 2^32, porque esse é o tamanho do int
    chave = ((long)fracao * dim) >> 32; // move 32 bits para voltar a escala normal, consequencia de ter multiplicado por 2^32
    return chave;
}

static unsigned int h2(unsigned int chave, int dim) {
    unsigned int fracao = (long)chave * 1779033703; // 1779033703 esse é a razão prata. O resto é o mesmo
    chave =((long)fracao * dim) >> 32;
    return chave;
}

static void redimensionar(Hash* hash) {
    Hash* novo = criar_tabela(2*hash->dim);
    for (unsigned int i = 0; i < hash->dim; i++) {
        if (hash->tabela[i].t1) {
            inserir(novo, hash->tabela[i].t1chave, hash->tabela[i].t1valor);
        }
        if (hash->tabela[i].t2) {
            inserir(novo, hash->tabela[i].t2chave, hash->tabela[i].t2valor);
        }
    } 
    free(hash->tabela);
    *hash = *novo;
    free(novo);
    return;
}

void buscar(Hash* hash, unsigned int chave) {
    unsigned int k;
    k = h1(chave, hash->dim);
    if (chave == hash->tabela[k].t1chave) {
        if (hash->tabela[k].t1) { // como o remover não tira a chave, é preciso fazer essa checagem também
            printf("%u -> %d\n", chave, hash->tabela[k].t1valor);
            return;
        }
    }

    k = h2(chave, hash->dim);
    if (chave == hash->tabela[k].t2chave) {
        if (hash->tabela[k].t2) {
            printf("%u -> %d\n", chave, hash->tabela[k].t2valor);
            return;
        }
    }
    printf("%u -> !E\n", chave);
    return;
}

void inserir(Hash* hash, unsigned int chave, int valor) {
    unsigned int k, temp_chave;
    int temp_valor;
    hash->n++;
    if (hash->n > hash->max) {
        redimensionar(hash);
    }
    for (int i = 0; i < 10; i++) {
        // aqui é a primeira tabela
        k = h1(chave, hash->dim);
        temp_valor = hash->tabela[k].t1valor;
        temp_chave = hash->tabela[k].t1chave;
        hash->tabela[k].t1valor = valor; 
        hash->tabela[k].t1chave = chave; 

        if (!hash->tabela[k].t1) { // acontece se não tiver um elemento
            hash->tabela[k].t1chave = chave;
            hash->tabela[k].t1 = 1;
            return;
        } 
        if (chave == temp_chave) { // é a mesma chave
            return;
        }

        // agora ele vai na segunda tabela
        k = h2(temp_chave, hash->dim);
        valor = hash->tabela[k].t2valor;
        chave = hash->tabela[k].t2chave;
        hash->tabela[k].t2valor = temp_valor; 
        hash->tabela[k].t2chave = temp_chave; 

        if (!hash->tabela[k].t2) { // acontece se não tiver um elemento
            hash->tabela[k].t2chave = temp_chave;
            hash->tabela[k].t2 = 1;
            return;
        } 
        if (temp_chave == chave) { // é a mesma chave
            return;
        }
    }

    redimensionar(hash);
    inserir(hash, chave, valor);
    return;
}

void remover(Hash* hash, unsigned int chave) {
    unsigned int k;
    k = h1(chave, hash->dim);
    if (chave == hash->tabela[k].t1chave) {
        hash->tabela[k].t1 = 0;
        return;
    }

    k = h2(chave, hash->dim);
    if (chave == hash->tabela[k].t2chave) {
        hash->tabela[k].t2 = 0;
        return;
    }
    return;
}

void liberar_tabela(Hash* hash) {
    free(hash->tabela);
    free(hash);
}