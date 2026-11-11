#include <stdlib.h>
#include <stdio.h>
#include "indice.h"

int main(void) {
    char comando;
    int t;
    long ini, fim;
    ArvB* B = NULL; 
    while(scanf(" %c", &comando) == 1) {
        switch (comando) {
        case 'c':
            scanf(" %d", &t);
            remover_arv(B);
            B = criar_arvb(t);
            break;
        case 'i':
            scanf(" %d %ld %ld", &t, &ini, &fim);
            if (B != NULL) {
                Trio* trio = formar_trio(t, ini, fim);
                inserir_chave(trio, B);
            }
            break;
        case 'b':
            Trio* p = (Trio*) malloc(sizeof(Trio));
            scanf(" %d", &t);
            p->chave = t;
            t = buscar_chave(t, B, p);
            if (t == 0) {
                printf("%d nao esta na arvore\n", p->chave);
            } else {
                printf("%d: %ld %ld\n", p->chave, p->ini, p->fim);
            }
            free(p);
            break;
        case 'p':
            imprimir_niveis(B);
            break;
        case 'l':
            if (B == NULL || B->raiz->n == 0) {
                printf("A arvore esta vazia.\n");
                break;
            }
            imprimir_chaves(B->raiz);
            printf("\n");
            break;
        case 'f':
            remover_arv(B);
            return 0;
        default:
            break;
        }
    }
}