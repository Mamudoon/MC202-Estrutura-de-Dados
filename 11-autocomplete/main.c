#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autocomplete.h"

int main(void) {
    Arvore *T;
    char comando[13], palavra[257];
    long n;
    T = criar_arv();
    while(scanf(" %12s", comando) == 1) {
        if (strcmp(comando, "INSERT") == 0) {
            scanf(" %s %ld", palavra, &n);
            ArvNo *novo = criar_no(palavra, n);
            inserir_no_arv(T, novo);
        } else if (strcmp(comando, "SEARCH") == 0) {
            scanf(" %s", palavra);
            buscar_no(T->raiz, palavra); 
        } else if (strcmp(comando, "AUTOCOMPLETE") == 0) {
            scanf(" %s %ld", palavra, &n);
            autocompletar(T, palavra, n);
        } else if (strcmp(comando, "DELETE") == 0) {
            scanf(" %s", palavra);
            remover_no(T, palavra);
        } else if (strcmp(comando, "PRINT") == 0) {
            if (T->raiz == NULL) {
                printf("the dictionary is empty.\n");
            } else {
                imprimir_arv(T->raiz);
                printf("\n");
            }
        } else if (strcmp(comando, "EXIT") == 0) {
            break;
        }
    }
    remover_arv(T);
    return 0;
}