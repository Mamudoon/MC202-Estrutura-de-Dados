typedef struct elemento {
    char t1;
    unsigned int t1chave;
    int t1valor;
    char t2;
    unsigned int t2chave;
    int t2valor; 
} Elem;

typedef struct hash {
    int dim;
    int n;
    Elem* tabela;
} Hash;

/**
 * Cria uma tabela (que contém duas tabelas) de tamanho n
 * 
 * Parâmetros 
 * (Tamanho da tabela)
 * 
 * Retorno: Ponteiro para a tabela
 */
Hash* criar_tabela(int n);

/**
 * Busca por uma chave específica na tabela e imprime o resultado da busca
 * 
 * Parâmetros 
 * (Tabela de hashing, chave sendo procurada)
 * 
 * Retorno: Nada
 */
void buscar(Hash* hash, unsigned int chave);

/**
 * Insere um valor e sua chave no indice correspondente da tabela
 * Atualiza o valor se a chave já estiver na tabela
 * 
 * Parâmetros 
 * (Tabela de hashing, chave sendo procurada, ponteiro para o valor)
 * 
 * Retorno: Nada
 */
void inserir(Hash* hash, unsigned int chave, int valor);

/**
 * Remove uma elemento associado a chave sendo procurada
 * Se ela não estiver na tabela, não faz nada;
 * 
 * Parâmetros 
 * (Tabela de hashing, chave sendo procurada)
 * 
 * Retorno: Nada
 */
void remover(Hash* hash, unsigned int chave);

/**
 * Remove e libera toda memória alocada por uma tabela
 * 
 * Parâmetros 
 * (Tabela de hashing)
 * 
 * Retorno: Nada
 */
void liberar_tabela(Hash* hash);