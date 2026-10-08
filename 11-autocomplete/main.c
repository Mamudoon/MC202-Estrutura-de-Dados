#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autocomplete.h"

int main(void) {
    Arvore *T, *F;
    char comando[13], palavra[257];
    long n;
    int inseriu = 0;
    T = criar_arv();
    F = criar_arv();
    while(scanf(" %12s", comando) == 1) {
        if (strcmp(comando, "INSERT") == 0) {
            scanf(" %s %ld", palavra, &n);
            ArvNo *novo_T = criar_no(palavra, n);
            ArvNo *novo_F = criar_no(palavra, n);
            inseriu = inserir_no_arv(T, novo_T, comparar_palavras);
            if (inseriu == 1) {
                remover_no(F, palavra);
            }
            inserir_no_arv(F, novo_F, comparar_freq);
        } else if (strcmp(comando, "SEARCH") == 0) {
            scanf(" %s", palavra);
            buscar_no(T->raiz, palavra); 
        } else if (strcmp(comando, "AUTOCOMPLETE") == 0) {
            scanf(" %s %ld", palavra, &n);
            autocompletar(T, F, palavra, n);
        } else if (strcmp(comando, "DELETE") == 0) {
            scanf(" %s", palavra);
            remover_no(T, palavra);
            remover_no(F, palavra);
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
    remover_arv(F);
    return 0;
}