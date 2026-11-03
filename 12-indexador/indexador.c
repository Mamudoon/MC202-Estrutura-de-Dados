#include "indexador.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *niveis[] = {"restrito", "interno", "publico", "bloqueado"}, *estados[] = {"atualizado", "desatualizado", "obsoleto"};

char codigo_nivel(char *palavra) {
    switch (palavra[0]) {
    case 'r': return 0;
    case 'i': return 1;
    case 'p': return 2;
    default:  return 3;  
    }
}
 
char codigo_estado(char *palavra) {
    switch (palavra[0]) {
    case 'a': return 0;
    case 'd': return 1;
    default:  return 2;  
    }
}


Arvore* criar_arv(void) {
    Arvore *T = (Arvore*) malloc(sizeof(Arvore));
    T->raiz = NULL;
    return T;
}

ArvNo* criar_no(long i, char *nivel, char *estado) {
    ArvNo *novo = (ArvNo*) malloc(sizeof(ArvNo));
    novo->pai = novo->esquerda = novo->direita = NULL;
    novo->i = i;
    novo->nivel = codigo_nivel(nivel);
    novo->estado = codigo_estado(estado);
    novo->altura = 1;
    return novo;
}

static int altura(ArvNo *no) { // devolve a altura do nó
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

static int maior(int a, int b) { // devolve o maior dos dois
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

static void atualizar_altura(ArvNo *no) { // atualiza a altura do nó
    no->altura = 1 + maior(altura(no->esquerda), altura(no->direita));
}

static int fator(ArvNo *no) { // devolve o fator de balanceamento
    return altura(no->esquerda) - altura(no->direita);
}

static void rotacionar_LL(Arvore *T, ArvNo *z) {
    ArvNo *x = z->esquerda;

    z->esquerda = x->direita;
    if (x->direita != NULL) {
        x->direita->pai = z;
    }
    x->direita = z;

    x->pai = z->pai;
    if (z->pai != NULL) {
        if (z->pai->esquerda == z) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
    } else {
        T->raiz = x;
    }
    z->pai = x;

    atualizar_altura(z);
    atualizar_altura(x);
}

static void rotacionar_RR(Arvore *T, ArvNo *z) {
    ArvNo *x = z->direita;

    z->direita = x->esquerda;
    if (x->esquerda != NULL) {
        x->esquerda->pai = z;
    }
    x->esquerda = z;

    x->pai = z->pai;
    if (z->pai != NULL) {
        if (z->pai->esquerda == z) {
            z->pai->esquerda = x;
        } else {
            z->pai->direita = x;
        }
    } else {
        T->raiz = x;
    }
    z->pai = x;

    atualizar_altura(z); 
    atualizar_altura(x);  
}

static void balancear_insercao(Arvore *T, ArvNo *novo) {
    ArvNo *u = novo->pai;
    while (u != NULL) {
        int altura_antiga = u->altura;
        atualizar_altura(u);
        int fb = fator(u);

        if (fb > 1) { // pesa para a esquerda
            if (fator(u->esquerda) < 0) { // caso LR
                rotacionar_RR(T, u->esquerda);
            }
            rotacionar_LL(T, u);
            break;
        } else if (fb < -1) { // pesa para a direita
            if (fator(u->direita) > 0) { // caso RL
                rotacionar_LL(T, u->direita);
            }
            rotacionar_RR(T, u);
            break;
        }

        if (u->altura == altura_antiga) {
            break;
        }
        u = u->pai;
    }
}

char inserir_no_arv(Arvore *T, ArvNo *novo) {
    ArvNo *u, *p;
    u = T->raiz;
    p = NULL;
    while (u != NULL) {
        p = u;
        if (u->i == novo->i) {
            return 3; // os estados só vão de 0 a 2, então é um bom número para quando não fazemos nada
        }
        if (novo->i < u->i) {
                u = u->esquerda;
            } else {
                u = u->direita;
        }
    }
    if (p == NULL) {
        T->raiz = novo;
    } else if (novo->i < p->i) {
        p->esquerda = novo;
    } else {
        p->direita = novo;
    }
    novo->pai = p;

    balancear_insercao(T, novo);
    return novo->estado;
}

char atualizar_no_arv(Arvore *T, long i, char *nivel, char *estado) {
    ArvNo *u = T->raiz;
    while (u != NULL) {
        if (u->i == i) {
            char antigo = u->estado;
            u->nivel = codigo_nivel(nivel);
            u->estado = codigo_estado(estado);
            return antigo;
        }
        if (i < u->i) {
                u = u->esquerda;
            } else {
                u = u->direita;
        }
    }
    return 3;
}

void buscar_no(Arvore *T, long i) {
    printf("%ld", i);
    ArvNo *u;
    u = T->raiz;
    while (u != NULL) {
        if (u->i == i) {
            printf(", %s, %s\n", niveis[u->nivel], estados[u->estado]);
            return;
        }
        if (i < u->i) {
                u = u->esquerda;
            } else {
                u = u->direita;
            }
    }
    printf(" nao existe\n");
}

void imprimir_identificadores(ArvNo *raiz) {
    if (raiz != NULL) {
        imprimir_identificadores(raiz->esquerda);
        printf("%ld ", raiz->i);
        imprimir_identificadores(raiz->direita);
    }
}

static void remover_todos_nos_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        remover_todos_nos_arv(raiz->esquerda);
        remover_todos_nos_arv(raiz->direita);
        free(raiz);
    }
}

void remover_arv(Arvore *T) {
    remover_todos_nos_arv(T->raiz);
    free(T);
}