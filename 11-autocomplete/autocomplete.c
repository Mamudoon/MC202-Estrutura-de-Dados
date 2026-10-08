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
    novo->freq = novo->freq_min = novo->freq_max = freq;
    novo->altura = 1;
    return novo;
}

static int altura(ArvNo *no) { // devolve a altura do nó
    if (no == NULL) {
        return 0;
    }
    return no->altura;
}

static void atualizar_no(ArvNo *no) { // atualiza a altura, freq_min e freq_max do nó
    if (altura(no->esquerda) > altura(no->direita)) {
        no->altura = 1 + altura(no->esquerda);
    } else {
        no->altura = 1 + altura(no->direita);
    }
    
    if (no->esquerda != NULL) {
        if (no->freq_min > no->esquerda->freq) {
            no->freq_min = no->esquerda->freq;
        }
        if (no->freq_max < no->esquerda->freq) {
            no->freq_max = no->esquerda->freq;
        }
    }

    if (no->direita != NULL) {
        if (no->freq_min > no->direita->freq) {
            no->freq_min = no->direita->freq;
        }
        if (no->freq_max < no->direita->freq) {
            no->freq_max = no->direita->freq;
        }
    }
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

    atualizar_no(z);
    atualizar_no(x);
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

    atualizar_no(z); 
    atualizar_no(x);  
}

static void balancear_insercao(Arvore *T, ArvNo *novo) {
    ArvNo *u = novo->pai;
    while (u != NULL) {
        int altura_antiga = u->altura;
        long min_ant = u->freq_min;
        long max_ant = u->freq_max;
        atualizar_no(u);
        int fb = fator(u);

        if (fb > 1) { // pesa para a esquerda
            if (fator(u->esquerda) < 0) { // caso LR
                rotacionar_RR(T, u->esquerda);
            }
            rotacionar_LL(T, u);
        } else if (fb < -1) { // pesa para a direita
            if (fator(u->direita) > 0) { // caso RL
                rotacionar_LL(T, u->direita);
            }
            rotacionar_RR(T, u);
        }

        if (u->altura == altura_antiga && u->freq_min == min_ant && u->freq_max == max_ant) { // nada mudou
            break;
        }
        u = u->pai;
    }
}

static void balancear_remocao(Arvore *T, ArvNo *u) {
    while (u != NULL) {
        int altura_antiga = u->altura;
        long min_ant = u->freq_min;
        long max_ant = u->freq_max;
        atualizar_no(u);
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

        if (u->altura == altura_antiga && u->freq_min == min_ant && u->freq_max == max_ant) { // nada mudou
            break;
        }

        u = u->pai;
    }
}

int comparar_freq(const void *a, const void *b) {
    ArvNo *A = (ArvNo*) a;
    ArvNo *B = (ArvNo*) b;
    if (A->freq != B->freq) {
        if (A->freq > B->freq) {
            return 1; // A é maior
        } else {
            return -1; // B é maior
        }
    }

    if (strcmp(A->palavra, B->palavra) < 0) {
        return 1; // A é menor lexicograficamente
    } else {
        return -1; // B é menor lexicograficamente
    }
}

int comparar_palavras(const void *a, const void *b) {
    ArvNo *A = (ArvNo*) a;
    ArvNo *B = (ArvNo*) b;
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

int inserir_no_arv(Arvore *T, ArvNo *novo, int (*comparar)(const void*, const void*)) {
    ArvNo *u, *p;
    u = T->raiz;
    p = NULL;
    while (u != NULL) {
        p = u;
        if (comparar(novo, u) == 0) {
            u->freq = novo->freq;
            free(novo->palavra);
            free(novo);
            return 1; // A frequencia de u mudou
        } else if (comparar(novo, u) < 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }
    if (p == NULL) {
        T->raiz = novo;
    } else if (comparar(novo, p) < 0) {
        p->esquerda = novo;
    } else {
        p->direita = novo;
    }
    novo->pai = p;
    balancear_insercao(T, novo);
    return 0; // inseriu o novo na árvore
}

long buscar_autocompletar(long *K, long max, ArvNo *raiz_F, char *prefixo) {
    if (raiz_F != NULL && *K != 0) {
        if (raiz_F->freq < max) {
            *K = buscar_autocompletar(K, max, raiz_F->direita, prefixo); 
            if (*K == 0) {
                return *K;
            }
        } else if (raiz_F->freq > max) {
            *K = buscar_autocompletar(K, max, raiz_F->esquerda, prefixo);
            if (*K == 0) {
                return *K;
            }
        }

        if (*K == 0) {
            return *K;
        }
        
        if (strstr(raiz_F->palavra, prefixo) ==  raiz_F->palavra) {
            printf("(%s,%ld) ", raiz_F->palavra, raiz_F->freq);
            *K -= 1;
        }
        *K = buscar_autocompletar(K, max, raiz_F->esquerda, prefixo);
    }
    return *K;
}

void autocompletar(Arvore *T, Arvore *F, char *prefixo, long k) {
    ArvNo *u = T->raiz;
    long *K = &k;
    while (u != NULL && strstr(u->palavra, prefixo) != u->palavra) { // percorre a árvore até achar um nó cuja palavra começa com prefixo ou até não achar
        if (strcmp(u->palavra, prefixo) > 0) {
            u = u->esquerda;
        } else {
            u = u->direita;
        }
    }

    if (u == NULL) {
        printf("nothing for %s.\n", prefixo);
    } else {
        buscar_autocompletar(K, u->freq_max, F->raiz, prefixo);
        printf("\n");
    }
}

void imprimir_arv(ArvNo *raiz) {
    if (raiz != NULL) {
        imprimir_arv(raiz->esquerda);
        printf("%s ", raiz->palavra);
        imprimir_arv(raiz->direita);
    }
}