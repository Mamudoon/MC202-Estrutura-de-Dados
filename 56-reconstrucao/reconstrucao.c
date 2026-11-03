#include <stdio.h>
#include <stdlib.h>

typedef struct no ArvNo;
struct no {
    unsigned long long n;
    ArvNo *esquerda;
    ArvNo *direita;
};

ArvNo* criar_no(unsigned long long n) {
    ArvNo *no = (ArvNo*) malloc(sizeof(ArvNo));
    no->n = n;
    no->esquerda = NULL;
    no->direita = NULL;
    return no;
}

void recriar(ArvNo *raiz, unsigned long long *pre, unsigned long long *ordem, unsigned long long pre_inicio, unsigned long long ordem_incio, unsigned long long tam) {
    unsigned long long indice_raiz;
    for (indice_raiz = ordem_incio; indice_raiz < ordem_incio + tam; indice_raiz++) {
        if (ordem[indice_raiz] == raiz->n) {
            break;
        }
    }
    unsigned long long tam_esq = indice_raiz - ordem_incio;
    unsigned long long tam_dir = tam - tam_esq - 1;

    if (tam_esq > 0) {
        ArvNo *no_esq = criar_no(pre[pre_inicio + 1]);
        raiz->esquerda = no_esq;
        recriar(raiz->esquerda, pre, ordem, pre_inicio + 1, ordem_incio, tam_esq);
    }

    if (tam_dir > 0) {
        ArvNo *no_dir = criar_no(pre[pre_inicio + tam_esq + 1]);
        raiz->direita = no_dir;
        recriar(raiz->direita, pre, ordem, pre_inicio + tam_esq + 1, indice_raiz + 1, tam_dir);
    }
}

void percorrer_pre(ArvNo *raiz) {
    printf("(");
    if (raiz != NULL) {
        printf("%llu", raiz->n);
        percorrer_pre(raiz->esquerda);
        percorrer_pre(raiz->direita);
    }
    printf(")");
}

void liberar_arvore(ArvNo *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esquerda);
        liberar_arvore(raiz->direita);
        free(raiz);
    }
}

int main(void) {
    unsigned long long tam, n;
    while (scanf(" %llu", &tam) == 1) {
        if (tam == 0) {
            printf("()\n");
            continue;
        }
        unsigned long long *pre = (unsigned long long*) malloc(tam*sizeof(unsigned long long));
        unsigned long long *ordem = (unsigned long long*) malloc(tam*sizeof(unsigned long long));
        for (unsigned long long i = 0; i < tam; i++) {
            scanf(" %llu", &n);
            pre[i] = n;
        }
        for (unsigned long long i = 0; i < tam; i++) {
            scanf(" %llu", &n);
            ordem[i] = n;
        }
        
        ArvNo *raiz = criar_no(pre[0]);

        recriar(raiz, pre, ordem, 0, 0, tam);

        percorrer_pre(raiz);
        printf("\n");
        liberar_arvore(raiz);
        free(pre);
        free(ordem);
    }
    return 0;
}