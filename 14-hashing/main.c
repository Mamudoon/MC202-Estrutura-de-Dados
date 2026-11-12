#include <stdio.h>
#include "hashing.h"

int main(void) {
    Hash* hash = NULL;
    char c; //comando
    unsigned int n; 
    int x;

    while(scanf(" %c", &c) == 1) {
        switch (c) {
        case 'c':
            scanf(" %u", &n);
            if (hash) { // se já existe
                liberar_tabela(hash);
            }
            hash = criar_tabela(n);
            break;

        case 'i':
            scanf(" %u %d", &n, &x);
            inserir(hash, n, x);
            break;

        case 'r':
            scanf(" %u", &n);
            remover(hash, n);
            break;

        case 'b':
            scanf(" %u", &n);
            buscar(hash, n);
            break;

        case 'f':
            liberar_tabela(hash);
            return 0;

        default:
            break;
        }
    }
    return 0;
}