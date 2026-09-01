#include <stdio.h>
#include <string.h>

struct contato {
    char nome[51], endereco[101], telefone[16], aniversario[9];
};

typedef struct contato Contato;

int inserir(Contato *lista, int fim) {
    scanf(" %50[^\n]", lista[fim].nome);
    scanf(" %100[^\n]", lista[fim].endereco);
    scanf(" %15[^\n]", lista[fim].telefone);
    scanf(" %8[^\n]", lista[fim].aniversario);
    printf("Contato para %s inserido.\n\n", lista[fim].nome);
    return ++fim;
}

int remover(Contato *lista, int fim) {
    char tchau[51]; // string auxiliar do que está send removido
    int removidos = 0;  // indice de quantos contatos foram removidos
    scanf(" %50[^\n]", tchau);
    for (int i = 0; i < fim; ++i) {
        if (strcmp(lista[i].nome, tchau) == 0) { // se for igual ao que queremos tirar
            ++removidos;
        } else {    // adiciona os que queremos manter e os move na lista igual ao número de removidos para manter a ordem
        lista[i - removidos] = lista[i];
        }
    }
    printf("Contatos de %s removidos: %d.\n\n", tchau, removidos);
    return fim - removidos; // o novo final da lista de contatos após remoçãp
}

void buscar(Contato *lista, int fim) {
    char procurado[51]; // string auxiliar para o que estamos procurando
    scanf(" %50[^\n]", procurado);
    int achou = 0;  // booleano para se a busca teve ou não resultados

    for (int i = 0; i < fim; ++i) {
        if (strstr(lista[i].nome, procurado) != NULL) { // identifica se o nome contém a string procurada 
            achou = 1;
            printf("(%d) %s\t%s\t%s\t%s\n\n", i + 1, lista[i].nome, lista[i].endereco, lista[i].telefone, lista[i].aniversario);    // imprime a busca
        }
    }
    if (achou == 0) {
        printf("Nenhum contato.\n\n");
    }
}

int main(void) {
    int fim = 0;  // fim da lista
    char operacao;
    Contato lista[1000];
    while(scanf(" %c", &operacao) == 1) {
        if (operacao == 'i') {  // inserir na lista de contatos
            fim = inserir(lista, fim);
        } else if (operacao == 'r') {   // remover da lista de contatos
            fim = remover(lista, fim);
        } else if (operacao == 'b') {   // buscar na lista de contatos
            printf("Resultado da busca:\n");
            buscar(lista, fim);
        } else if (operacao == 'p') {   // imprimir lista de contatos
            printf("Listagem:\n");
            for (int i = 0; i < fim; ++i) {
                printf("(%d) %s\t%s\t%s\t%s\n", i + 1, lista[i].nome, lista[i].endereco, lista[i].telefone, lista[i].aniversario);
            }
            printf("\n");
            if (fim == 0) {
                printf("Nenhum contato.\n\n");
            }

        } else if (operacao == 'f') {   // finalizar programa
            break;
        }
    }
    return 0;
}