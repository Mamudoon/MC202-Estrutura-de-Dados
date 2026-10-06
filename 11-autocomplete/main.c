#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autocomplete.h"

int main(void) {
    Arvore *T;
    char comando[13], palavra[257];
    long freq;
    T = criar_arv();
    while(1) {
        scanf(" %s", comando);
        if (strcmp(comando, "INSERT") == 0) {
            scanf(" %s %ld", palavra, &freq);
            ArvNo *novo = criar_no(palavra, freq);
            inserir_no(T, novo);
        } else if (strcmp(comando, "SEARCH") == 0) {
            scanf(" %s", palavra);
            buscar_no(T->raiz, palavra); 
        } else if (strcmp(comando, "AUTOCOMPLETE") == 0) {

        } else if (strcmp(comando, "DELETE") == 0) {

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
        //memset(palavra, 0, sizeof(palavra));
    }
    return 0;
}