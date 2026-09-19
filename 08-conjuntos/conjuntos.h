#include <stdio.h>
#include <stdlib.h>

typedef struct elemento Elemento;

struct elemento {
    int n; // elemento
    Elemento* proximo; // próximo elemento na lista
};

void inserir_elementos(int valor, Elemento* antes) { // n do elemento que vai ser inserido, o elemento que virá antes do inserido 
    Elemento* novo = (Elemento*) malloc(sizeof(Elemento));
    novo->n = valor;
    novo->proximo = antes->proximo; 
    antes->proximo = novo;
}

void remover_elemento(Elemento* antes) { // remove o elemento que segue o antes
    Elemento* lixo;
    lixo = antes->proximo;
    antes->proximo = lixo->proximo;
    free(lixo);
}

// cria o conjunto i vazio
void comando_c(Elemento* cabeca) { // cabeca do conjunto i
    while (cabeca->proximo != NULL) {
        remover_elemento(cabeca);
    }
}

// insere j elementos em i
void comando_i(int j, Elemento* cabeca) { // número de elementos que seram inseridos, cabeca do conjunto 
    int valor;
    for (int a = 0; a < j; ++a) { // a é o índice
        scanf(" %d", &valor);
        inserir_elementos(valor, cabeca);
    }
}

//comando_r();

//comando_u();

//comando_n();

//comando_m();

//comando_e();

// imprime os conteúdos de i
void comando_p(Elemento* cabeca) { // cabeca do conjunto i
    Elemento* elemento = cabeca->proximo;
    while (elemento != NULL) {
        printf("%d", elemento->n);
        if (elemento->proximo != NULL) {
            printf(", ");
        }
        elemento = elemento->proximo;
    }
    printf("}\n");
    
}
