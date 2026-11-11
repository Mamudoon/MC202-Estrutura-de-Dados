#ifndef INDICE_H
#define INDICE_H

typedef struct trio Trio;
typedef struct no ArvNoB;
typedef struct arv ArvB;
typedef struct elem Elem;
typedef struct fila Fila;

struct trio {
    int chave;
    long ini;
    long fim;
};

struct no {
    int t;
    int n;
    int n_filhos;
    int eh_folha;
    Trio* chaves;
    ArvNoB** filhos;
    ArvNoB* pai;
};

struct arv {
    ArvNoB* raiz;
};

struct elem {
    ArvNoB* no;
    Elem* prox;
};

struct fila {
    Elem* ini;
    Elem* fim;
    int tam;
};

/**
 * Cria uma árvore B de grau t
 * 
 * Parâmetros
 * (Grau da árvore)
 * 
 * Retorno: Ponteiro para a árvore B criada
 */
ArvB* criar_arvb(int t);

/**
 * Cria um nó de árvore B de grau t
 * 
 * Parâmetros
 * (Grau da árvore)
 * 
 * Retorno: Ponteiro para o nó criado
 */
ArvNoB* criar_no(int t);

/**
 * Cria um nó de árvore B de grau t
 * 
 * Parâmetros
 * (Grau da árvore)
 * 
 * Retorno: Ponteiro para o nó criado
 */
Trio* formar_trio(int x, long ini, long fim);

/**
 * Insere o struct no local correspondente da árvore B baseado na chave do trio
 * Foi escolhido uma struct pois é mais fácil guardar as informações assim, mas o único que importa para inserir é a chave
 * Se a chave já existir a função não deve fazer nada, incluindo a divisão preventiva
 * 
 * Parâmetros
 * ({info->chave, info->ini, info->fim}, árvore B)
 * 
 * Retorno: Nada
 */
void inserir_chave(Trio* info, ArvB* B);

/**
 * Procura pela chave x desejada na árvore.
 * Antes ela imprimia também, mas mudei isso para que eu pudesse reutilizar essa função na inserção
 * 
 * Parâmetros
 * (Chave, árvore B, informações da chave)
 * 
 * Retorno: 1 se achar, 0 se não achar
 */
int buscar_chave(int x, ArvB* B, Trio* p);

/**
 * Imprime a árvore nível por nível
 * 
 * Parâmetros
 * (Árvore B)
 * 
 * Retorno: Nada
 */
void imprimir_niveis(ArvB* B);

/**
 * Imprime todas as chaves em ordem
 * 
 * Parâmetros
 * (Nó da árvore B)
 * 
 * Retorno: Nada
 */
void imprimir_chaves(ArvNoB* raiz);

/**
 * Remove a árvore e libera toda memória alocada
 * 
 * Parâmetros
 * (Árvore B)
 * 
 * Retorno: Nada
 */
void remover_arv(ArvB* B);

#endif

