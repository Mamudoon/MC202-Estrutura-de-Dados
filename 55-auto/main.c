#include <stdio.h>
#include <stdlib.h>

#include "auto.h"

int main(void) {
    Lista *L = (Lista*) malloc(sizeof(Lista));
    L->primeiro = NULL;
    int n, buscas;
    scanf(" %d", &n);
    criar(L, n);
    for (No *p = L->primeiro; p != NULL; p = p->next) {
        printf("%d\n", p->valor);
    }
    return 0;
}