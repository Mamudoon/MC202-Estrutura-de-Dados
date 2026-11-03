#include "indexador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    ArvNo* novo;
    char comando, nivel[10], estado[14];
    long i, n_estados[3];
    char primeiro;
    memset(n_estados, 0, 3*sizeof(long));
    Arvore* T = criar_arv();
    while(scanf(" %c", &comando) == 1) {
        switch (comando) {
        case 'i':
            scanf(" %ld %s %s", &i, nivel, estado);
            novo = criar_no(i, nivel, estado); 
            primeiro = inserir_no_arv(T, novo);
            if (primeiro < 3) {
                n_estados[primeiro]++;
            } else {
                free(novo);
            }
            break;
        case 'a':
            scanf(" %ld %s %s", &i, nivel, estado);
            primeiro = atualizar_no_arv(T, i, nivel, estado);
            if (primeiro < 3) {
                n_estados[primeiro]--;
                n_estados[codigo_estado(estado)]++;
            }
            break;
        case 'b':
            scanf(" %ld", &i);
            buscar_no(T, i);
            break;
        case 'l':
            if (T->raiz != NULL) {
                printf("documentos: ");
                imprimir_identificadores(T->raiz);
                printf("\n");
            } else {
                printf("indice vazio\n");
            }
            break;
        case 't':
            printf("atualizado: %ld, desatualizado: %ld, obsoleto: %ld\n", n_estados[0], n_estados[1], n_estados[2]);
            break;
        case 'f':
            remover_arv(T);
            return 0;
        default:
            break;
        }
    }
}
