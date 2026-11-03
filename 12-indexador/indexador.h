#ifndef INDEXADOR_H
#define INDEXADOR_H

typedef struct no_arvore ArvNo;

struct no_arvore { // os nós de uma árvore 
    ArvNo *esquerda;
    ArvNo *direita;
    ArvNo *pai;
    int altura;
    char nivel;
    char estado;
    long i;
};

typedef struct arvore { // começo de uma árvore 
    ArvNo *raiz;
} Arvore;

/**
 * Converte a palavra da visibilidade para um número entre 0 e 3;
 * Retorna o número da respectiva palavra;
 */
char codigo_nivel(char *palavra);

/**
 * Converte a palavra de estado para um número entre 0 e 2;
 * Retorna o número da respectiva palavra;
 */
char codigo_estado(char *palavra);

/**
 * Cria a árvore T;
 * Retorna o endereço dela;
 */
Arvore* criar_arv(void); 

/**
 * Cria nós;
 * (Identificador do documento, visibilidade do documento, estado do documento)
 * Retorna o endereço dele;
 */
ArvNo* criar_no(long i, char *nivel, char *estado); 

/**
 * Adiciona nós para uma árvore;
 * (Árvore T, o nó sendo inserido)
 * Retorna o primeiro char do estado inserido, se não inseriu retorna 'n';
 */
char inserir_no_arv(Arvore *T, ArvNo *novo); 

/**
 * Atualiza um nó com o identificador do novo para uma árvore;
 * (Árvore T, identificador, visibilidade, estado)
 * Retorna o primeiro char do estado antigo se atualizou, se não atualizaou retorna 'n';
 */
char atualizar_no_arv(Arvore *T, long i, char *nivel, char *estado);

/**
 * Remove a árvore;
 * (Árvore T)
 */
void remover_arv(Arvore *T);

/**
 * Busca nós de uma ávore;
 * (Árvore T, identificador do nó)
 */
void buscar_no(Arvore *T, long i); 

/**
 * Imprime os identificadores dos nós em ordem crescente;
 * (Raíz de uma árvore ou subárvore)
 */
void imprimir_identificadores(ArvNo *raiz);

#endif