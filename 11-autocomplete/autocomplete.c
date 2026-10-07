#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "autocomplete.h"

Arvore* criar_arv(void) {
    Arvore *T = (Arvore*) malloc(sizeof(Arvore));
    T->raiz = NULL;
    return T;
}

ArvNo* criar_no(char *palavra, long freq) {
    ArvNo *novo = (ArvNo*) malloc(sizeof(ArvNo));
    novo->pai = NULL;
    novo->direita = NULL;
    novo->esquerda = NULL;
    char *temp = (char*) malloc((strlen(palavra) + 1)*sizeof(char));
    strcpy(temp, palavra);
    novo->palavra = temp;
    novo->freq = freq;
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

static void balancear_remocao(Arvore *T, ArvNo *u) {
    while (u != NULL) {
        atualizar_altura(u);
        int fb = fator(u);

        if (fb > 1) { // pesa para a esquerda
            if (fator(u->esquerda) < 0) { // caso LR
                rotacionar_RR(T, u->esquerda);
            }
            rotacionar_LL(T, u);
            u = u->pai; 
        } else if (fb < -1) { // pesa para a direita
            if (fator(u->direita) > 0) { // caso RL
                rotacionar_LL(T, u->direita);
            }
            rotacionar_RR(T, u);
            u = u->pai;
        }

        u = u->pai;
    }
}

static void adicionar(Vetor *vet, ArvNo *no) {
    if (vet->n == vet->cap) {
        vet->cap = 2*vet->cap;
        vet->v = (ArvNo**) realloc(vet->v, vet->cap*sizeof(ArvNo*));
    }
    vet->v[vet->n++] = no;
}

static void coletar(ArvNo *raiz, const char *prefixo, int tam, Vetor *vet) {
    if (raiz == NULL) return;
    int i = strncmp(raiz->palavra, prefixo, tam);
    if (i < 0) {
        coletar(raiz->direita, prefixo, tam, vet);
    } else if (i > 0) {
        coletar(raiz->esquerda, prefixo, tam, vet);
    } else {
        adicionar(vet, raiz);
        coletar(raiz->esquerda, prefixo, tam, vet);
        coletar(raiz->direita, prefixo, tam, vet);
    }
}

static int comparar(const void *a, const void *b) {
    ArvNo *A = *(ArvNo* const*) a;
    ArvNo *B = *(ArvNo* const*) b;
    if (A->freq != B->freq) {
        return (A->freq < B->freq) ? 1 : -1;
    }
    return strcmp(A->palavra, B->palavra);
}

void buscar_no(ArvNo *raiz, char *palavra) {
    ArvNo *u = raiz;
    while (u != NULL && strcmp(u->palavra, palavra) != 0) { // percorre a árvore até achar um nó com a chave igual a palavra ou até não achar
        if (strcmp(u->palavra, palavra) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (u == NULL) {
        printf("%s not found.\n", palavra);
    } else {
        printf("%s %ld\n", palavra, u->freq);
    }
}

void remover_no(Arvore* T, char* lixo) {
    ArvNo *u = T->raiz, *p = NULL;
    ArvNo *inicio = NULL;
    while (u != NULL && strcmp(u->palavra, lixo) != 0) {
        if (strcmp(u->palavra, lixo) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (u != NULL) {
        if (u->direita != NULL) {
            p = u->direita;
            while (p->esquerda != NULL) {
                p = p->esquerda;
            }
            if (p != u->direita) {
                inicio = p->pai; 
                p->pai->esquerda = p->direita;
                if (p->direita != NULL) {
                    p->direita->pai = p->pai;
                }
                p->direita = u->direita;
                p->esquerda = u->esquerda;
                if (u->esquerda != NULL) {
                    u->esquerda->pai = p;
                }
                u->direita->pai = p;
                p->pai = u->pai;
            } else {
                inicio = p;  
                if (u->esquerda != NULL) {
                    u->esquerda->pai = p;
                }
                p->esquerda = u->esquerda;
                p->pai = u->pai;
            }
        } else if (u->esquerda != NULL) {
            p = u->esquerda;
            while (p->direita != NULL) {
                p = p->direita;
            }
            if (p != u->esquerda) {
                inicio = p->pai; 
                p->pai->direita = p->esquerda;
                if (p->esquerda != NULL) {
                    p->esquerda->pai = p->pai;
                }
                p->direita = u->direita;
                p->esquerda = u->esquerda;
                u->esquerda->pai = p;
                p->pai = u->pai;
            } else {
                inicio = p;
                p->direita = u->direita;
                p->pai = u->pai;
            }
        } else {
            inicio = u->pai; 
        }

        if (u == T->raiz) {
            T->raiz = p;
        } else if (u->pai->esquerda == u) {
            u->pai->esquerda = p;
        } else {
            u->pai->direita = p;
        }

        free(u->palavra);
        free(u);
        balancear_remocao(T, inicio); 
    }
}

static void remover_todos_nos_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        remover_todos_nos_arv(raiz->esquerda);
        remover_todos_nos_arv(raiz->direita);
        free(raiz->palavra);
        free(raiz);
    }
}

void remover_arv(Arvore *T) {
    remover_todos_nos_arv(T->raiz);
    free(T);
}

void inserir_no_arv(Arvore *T, ArvNo *novo) {
    ArvNo *u, *p;
    u = T->raiz;
    p = NULL;
    while (u != NULL) {
        p = u;
        if (strcmp(novo->palavra, u->palavra) == 0) {
            u->freq = novo->freq;
            free(novo->palavra);
            free(novo);
            return;
        } else if (strcmp(novo->palavra, u->palavra) < 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (p == NULL) {
        T->raiz = novo;
    } else if ((strcmp(novo->palavra, p->palavra) < 0)) {
        p->esquerda = novo;
    } else {
        p->direita = novo;
    }
    novo->pai = p;
    balancear_insercao(T, novo);
}

void autocompletar(Arvore *T, char *prefixo, long k) {
    Vetor vet;
    vet.v = (ArvNo**) malloc(8*sizeof(ArvNo*));
    vet.n = 0;
    vet.cap = 8;
    coletar(T->raiz, prefixo, strlen(prefixo), &vet);

    if (vet.n == 0) {
        printf("nothing for %s.\n", prefixo);
    } else {
        qsort(vet.v, vet.n, sizeof(ArvNo*), comparar);
        for (long i = 0; i < vet.n && i < k; i++) {
            printf("(%s,%ld) ", vet.v[i]->palavra, vet.v[i]->freq);
        }
        printf("\n");
    }
    free(vet.v);
}

void imprimir_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        imprimir_arv(raiz->esquerda);
        printf("%s ", raiz->palavra);
        imprimir_arv(raiz->direita);
    }
}