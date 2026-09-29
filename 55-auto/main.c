#include <stdio.h>
#include <stdlib.h>

#include "auto.h"

int main(void) {
    Lista *L_SEQ = (Lista*) malloc(sizeof(Lista)); // precisa de 4 listas porque 3 dos 4 métodos alteram ela
    Lista *L_MTF = (Lista*) malloc(sizeof(Lista)); 
    Lista *L_TRANS = (Lista*) malloc(sizeof(Lista));
    Lista *L_COUNT = (Lista*) malloc(sizeof(Lista));
    L_SEQ->primeiro = L_MTF->primeiro = L_TRANS->primeiro = L_COUNT->primeiro = NULL;
    L_SEQ->ultimo = L_MTF->ultimo = L_TRANS->ultimo = L_COUNT->ultimo = NULL;
    int n, buscas, buscado;
    int bseq = 0, bmtf = 0, btrans = 0, bcount = 0;
    scanf(" %d %d", &n, &buscas);
    criar(L_SEQ, n);
    criar(L_MTF, n);
    criar(L_TRANS, n);
    criar(L_COUNT, n);
    for (int i = 0; i < buscas; ++i) {
        scanf(" %d", &buscado);
        bseq += buscar(L_SEQ, buscado, SEQ);
        bmtf += buscar(L_MTF, buscado, MTF);
        btrans += buscar(L_TRANS, buscado, TRANSPOSE);
        bcount += buscar(L_COUNT, buscado, COUNT);
    }
    remover_tudo(L_SEQ);
    remover_tudo(L_MTF);
    remover_tudo(L_TRANS);
    remover_tudo(L_COUNT);
    printf("Sequencial: %d\n", bseq);
    printf("MTF: %d\n", bmtf);
    printf("Transpose: %d\n", btrans);
    printf("Count: %d\n", bcount);
    return 0;
}