#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "indice.h"

static void transferir_chaves(int med, ArvNoB* no, ArvNoB* novo_no) {
    int i, novo_n_filhos = 0;
    for (i = med + 1; i < no->n; i++) {
        novo_no->chaves[i - med - 1] = no->chaves[i];
        if (i < no->n_filhos) {
            novo_no->filhos[i - med - 1] = no->filhos[i];
            novo_no->filhos[i - med - 1]->pai = novo_no;
            novo_n_filhos += 1;
        } 
    }
    if (i < no->n_filhos) {
        novo_no->filhos[i - med - 1] = no->filhos[i];
        novo_no->filhos[i - med - 1]->pai = novo_no;
        novo_n_filhos += 1;
    }
    //mudando os parâmetros do nó antigo
    no->n = med;
    no->n_filhos -= novo_n_filhos; 
    //mudando os parâmetros do novo_no
    novo_no->n = i - med - 1;
    novo_no->n_filhos = novo_n_filhos;
    novo_no->eh_folha = no->eh_folha;
    novo_no->pai = no->pai;
}

ArvNoB* criar_no(int t) {
    ArvNoB* no = (ArvNoB*) malloc(sizeof(ArvNoB));
    no->t = t;
    no->n = 0;
    no->n_filhos = 0;
    no->eh_folha = 1; // 1 significa que é folha
    no->chaves = (Trio*) malloc((2*t-1)*sizeof(Trio));
    no->filhos = (ArvNoB**) malloc(2*t*sizeof(ArvNoB*));
    no->pai = NULL;
    return no;
}

ArvB* criar_arvb(int t) {
    ArvB* B = (ArvB*) malloc(sizeof(ArvB));
    B->raiz = criar_no(t);
    return B;
}

Trio* formar_trio(int x, long ini, long fim) {
    Trio* trio = (Trio*) malloc(sizeof(Trio));
    trio->chave = x;
    trio->ini = ini;
    trio->fim = fim;
    return trio;
}

static void divisao(ArvNoB* no) {
/**
 * Divide um nó quando seu array está cheio e o divide de acordo com o caso
 * 
 * Parâmetros
 * (Nó que está cheio)
 * 
 * Retorno: Nada
 */
    int med = no->n/2, i;
    ArvNoB* novo_no = criar_no(no->t);
    if (no->pai) { // o nó sendo dividido não é a raiz
        transferir_chaves(med, no, novo_no);

        for (i = 0; i < no->pai->n; i++) {
            if (no->chaves[med].chave < no->pai->chaves[i].chave){
                memmove(&no->pai->chaves[i + 1], &no->pai->chaves[i], sizeof(Trio)*(no->pai->n - i));
                memmove(&no->pai->filhos[i + 2], &no->pai->filhos[i + 1], sizeof(ArvNoB*)*(no->pai->n_filhos - i - 1));
                break;
            }
        }
        no->pai->chaves[i] = no->chaves[med];
        no->pai->filhos[i + 1] = novo_no;
        no->pai->n++;
        no->pai->n_filhos++;
    } else { // o nó é a raiz
        ArvNoB* nova_raiz = criar_no(no->t);
        no->pai = nova_raiz;
        transferir_chaves(med, no, novo_no);
        //mudando os parâmetros do pai de ambos
        nova_raiz->n = 1;
        nova_raiz->n_filhos = 2;
        nova_raiz->eh_folha = 0;
        nova_raiz->chaves[0] = no->chaves[med];
        nova_raiz->filhos[0] = no;
        nova_raiz->filhos[1] = novo_no;
        nova_raiz->pai = NULL;
    }
}

void inserir_chave(Trio* info, ArvB* B) {
    int i;
    ArvNoB* q = B->raiz;
    i = buscar_chave(info->chave, B, info); // faço a busca primeiro, pois não devo fazer a divisão se a chave já existir
    if (i == 1) {
        free(info);
        return;
    }
    while (1) {
        if (q->n == 2*q->t - 1) { // nó está cheio
            int era_raiz = (q->pai == NULL);
            divisao(q);     
            q = q->pai;
            if (era_raiz) {
                B->raiz = q;
            }
        }
        if (q->eh_folha == 1) {
            break;
        }
        for (i = 0; i < q->n; i++) {
            if (q->chaves[i].chave == info->chave) {
                free(info);
                return;
            } else if (q->chaves[i].chave > info->chave) {
                break;
            }
        }
        q = q->filhos[i]; // fica fora do for, pois pode ser o filho mais a direita
    }

    for (i = 0; i < q->n; i++) {
        if (info->chave < q->chaves[i].chave){
            memmove(&q->chaves[i + 1], &q->chaves[i], sizeof(Trio) *(q->n - i));
            break;
        } else if (info->chave == q->chaves[i].chave) {
            free(info);
            return;
        }
    }
    q->chaves[i] = *info;
    q->n++;
    free(info);
}

int buscar_chave(int x, ArvB* B, Trio* p) {
    int i;
    if (B == NULL) {
        return 0;
    }
    ArvNoB* q = B->raiz;
    while (1) { // isso tudo é igual o do inserir
        if (q->eh_folha == 1) {
            break;
        }
        for (i = 0; i < q->n; i++) {
            if (q->chaves[i].chave == x) {
                p->ini = q->chaves[i].ini;
                p->fim = q->chaves[i].fim;
                return 1;
            } else if (q->chaves[i].chave > x) {
                break;
            }
        }
        q = q->filhos[i];
    }
    for (i = 0; i < q->n; i++) {
        if (q->chaves[i].chave == x) {
            p->ini = q->chaves[i].ini;
            p->fim = q->chaves[i].fim;
            return 1;
        } 
    }
    return 0;
}

static Fila* criar_fila(void) {
    Fila* fila = (Fila*) malloc(sizeof(Fila));
    fila->ini = NULL;
    fila->fim = NULL;
    fila->tam = 0;
    return fila;
}

static void enfileirar(Fila* fila, ArvNoB* no) {
    Elem* novo = (Elem*) malloc(sizeof(Elem));
    novo->no = no;
    novo->prox = NULL;
    if (fila->fim) {
        fila->fim->prox = novo;
    } else {
        fila->ini = novo;
    }
    fila->fim = novo;
    fila->tam++;
}

static ArvNoB* desenfileirar(Fila* fila) {
    Elem* primeiro = fila->ini;
    ArvNoB* no = primeiro->no;
    fila->ini = primeiro->prox;
    if (fila->ini == NULL) {
        fila->fim = NULL;
    }
    free(primeiro);
    fila->tam--;
    return no;
}

static void imprimir_nivel(Fila* fila) {
    int largura = fila->tam;
    for (int i = 0; i < largura; i++) {
        ArvNoB* no = desenfileirar(fila);
        int j;
        printf("[%d", no->chaves[0].chave);
        for (j = 1; j < no->n; j++) {
            printf(",%d", no->chaves[j].chave);
        }
        for (j = 0; j < no->n_filhos; j++) {
            enfileirar(fila, no->filhos[j]);
        }
        printf("] ");
    }
    return;
}

void imprimir_niveis(ArvB* B) {
    if (B == NULL || B->raiz->n == 0) {
        printf("A arvore esta vazia.\n");
        return;
    }
    Fila* fila = criar_fila(); // precisa de fila para fazer em nível
    enfileirar(fila, B->raiz);
    int nivel = 0;
    while (fila->tam != 0) {
        printf("nivel %d: ", nivel);
        imprimir_nivel(fila);
        printf("\n");
        nivel++;
    }
    free(fila);
}


void imprimir_chaves(ArvNoB* raiz) {
    for (int i = 0; i < raiz->n; i++) {
        if (i < raiz->n_filhos) {
            imprimir_chaves(raiz->filhos[i]);
        }
        printf("%d ", raiz->chaves[i].chave);
    }
    if (raiz->n < raiz->n_filhos) { // caso para exceção porquê o filho mais a direita não seria contado no for
        imprimir_chaves(raiz->filhos[raiz->n]);
    }
}

static void remover_arvno(ArvNoB* raiz) {
    for (int i = 0; i < raiz->n_filhos; i++) {
        remover_arvno(raiz->filhos[i]);
    }
    free(raiz->chaves);
    free(raiz->filhos);
    free(raiz);
}

void remover_arv(ArvB* B) {
    if (B == NULL) {
        return;
    }
    remover_arvno(B->raiz);
    free(B);
}