#include <stdio.h>
#include <stdlib.h>

typedef struct elemento Elemento;

struct elemento {
    int n; // elemento
    Elemento *proximo; // próximo elemento na lista
};

void inserir_elemento(int valor, Elemento *antes) {	// n do elemento que vai ser inserido, o elemento que virá antes do inserido 
    Elemento *novo = (Elemento *) malloc(sizeof(Elemento));
    novo->n = valor;
    novo->proximo = antes->proximo;
    antes->proximo = novo;
}

Elemento *localizar(int valor, Elemento *antes) { // encontra o elemento no conjunto
    if (antes->proximo->n == valor) {
	    return antes;
    } else {
	    return localizar(valor, antes->proximo);
    }
}

Elemento *localizar_crescente(int valor, Elemento *antes, Elemento* sentinela) {	// acha onde valor pode ser inserido para manter uma ordem crescente e impede repetidos
    if (antes->proximo == sentinela || valor < (antes->proximo)->n) { // impede erro para caso não haja proximo, checa se fica entre o antes e o próximo dele
	    return antes;
    } else if (valor == (antes->proximo)->n) {	// se for repetido ele não é para entrar no conjunto
	    return NULL;
    } else {
	    return localizar_crescente(valor, antes->proximo, sentinela);	// é maior que ambos então precisa ir para o próximo intervalo
    }
}

void remover_elemento(Elemento *antes) { // remove o elemento que segue o antes
    Elemento *lixo;
    lixo = antes->proximo;
    antes->proximo = lixo->proximo;
    free(lixo);
}

// cria o conjunto i vazio
void comando_c(Elemento *cabeca, Elemento *sentinela) {	// cabeca do conjunto i
    cabeca->proximo = sentinela; // adiciona o sentinela de volta
    sentinela->proximo = NULL;

    while (cabeca->proximo != sentinela) {	// faz o conjunto ficar vazio 
	    remover_elemento(cabeca);
    }
}

// insere j elementos no conjunto i
void comando_i(int j, Elemento *cabeca, Elemento *sentinela) { // número de elementos que serão inseridos, cabeca do conjunto 
    int valor;
    Elemento *local_inserir;
    for (int a = 0; a < j; ++a) {
        scanf(" %d", &valor);
        local_inserir = localizar_crescente(valor, cabeca, sentinela);
        if (local_inserir != NULL) {
            inserir_elemento(valor, local_inserir);
        }
    }
}

void comando_r(int j, Elemento *cabeca, Elemento *sentinela) { // número de elementos que serão inseridos, cabeca do conjunto 
    int valor;
    Elemento *local_remover = cabeca;	// chamei a variável assim, pois ela é reutilizada depois

    for (int a = 0; a < j; ++a) {
        scanf(" %d", &valor);
        sentinela->n = valor;
        local_remover = localizar(valor, cabeca);
        if (local_remover->proximo != sentinela) {
            remover_elemento(local_remover);
        }
    }
}

void comando_u(Elemento *cabeca_i, Elemento *cabeca_j, Elemento *cabeca_k, Elemento *sentinela_i, Elemento *sentinela_j, Elemento *sentinela_k) { 
    // conjunto i que receberá a união de j e k 
    comando_c(cabeca_i, sentinela_i); // criamos o conjunto i
    int valor;
    Elemento *local_inserir;

    for (Elemento * a = cabeca_j->proximo; a != sentinela_j; a = a->proximo) {	// mesma lógica do comando_i aplicado duas vezes para cada conjunto
        valor = a->n;
        local_inserir = localizar_crescente(valor, cabeca_i, sentinela_i);
        if (local_inserir != NULL) {
            inserir_elemento(valor, local_inserir);
        }
    }

    for (Elemento * a = cabeca_k->proximo; a != sentinela_k; a = a->proximo) {
        valor = a->n;
        local_inserir = localizar_crescente(valor, cabeca_i, sentinela_i);
        if (local_inserir != NULL) {
            inserir_elemento(valor, local_inserir);
        }
    }
}

void comando_n(Elemento *cabeca_i, Elemento *cabeca_j, Elemento *cabeca_k, Elemento *sentinela_i, Elemento *sentinela_j, Elemento *sentinela_k) { 
    // conjunto i que receberá a interseção de j e k
    comando_c(cabeca_i, sentinela_i); // criamos o conjunto i
    int valor;
    Elemento *local_inserir = cabeca_j;

    for (Elemento * a = cabeca_k->proximo; a != sentinela_k; a = a->proximo) {
        valor = a->n;
        sentinela_j->n = valor;
        local_inserir = localizar(valor, cabeca_j);
        if (local_inserir->proximo != sentinela_j) {
            local_inserir = localizar_crescente(valor, cabeca_i, sentinela_i);
            if (local_inserir != NULL) {
                inserir_elemento(valor, local_inserir);
            }
        }
    }
}

void comando_m(Elemento *cabeca_i, Elemento *cabeca_j, Elemento *cabeca_k, Elemento *sentinela_i, Elemento *sentinela_j, Elemento *sentinela_k) { 
    // conjunto i que receberá a diferença de j e k
    comando_c(cabeca_i, sentinela_i); // criamos o conjunto i
    int valor;
    Elemento *local_inserir, *local_remover;; 
    for (Elemento * a = cabeca_j->proximo; a != sentinela_j; a = a->proximo) {	// mesma lógica do comando_i, aqui estamos inserindo os valores de j em i
        valor = a->n;
        local_inserir = localizar_crescente(valor, cabeca_i, sentinela_i);
        if (local_inserir != NULL) {
            inserir_elemento(valor, local_inserir);
        }
    }

    for (Elemento * a = cabeca_k->proximo; a != sentinela_k; a = a->proximo) {
        valor = a->n;
        sentinela_i->n = valor;
        local_remover = localizar(valor, cabeca_i);
        if (local_remover->proximo != sentinela_i) {
            remover_elemento(local_remover);
        }
    }
}

void comando_e(int i, int x, Elemento *cabeca, Elemento *sentinela) { // procura o elemento x no conjunto i
    Elemento* local;
    sentinela->n = x; 
    local = localizar(x, cabeca);
    if (local->proximo != sentinela) {
	    printf("%d esta em C%d\n", x, i);
    } else {
	    printf("%d nao esta em C%d\n", x, i);
    }
}

// imprime os conteúdos de conjunto i
void comando_p(Elemento *cabeca, Elemento *sentinela) { // cabeca do conjunto i
    Elemento *elemento = cabeca->proximo;
    while (elemento != sentinela) {
        printf("%d", elemento->n);
        if (elemento->proximo != sentinela) {
            printf(", ");
        }
        elemento = elemento->proximo;
    }
    printf("}\n");

}