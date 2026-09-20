#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dna {
    char* linha;    // strind do dna
    int inversoes;  // quantas inversões essa string precisa
};

typedef struct dna DNA;

int comparar(const void *a, const void *b) {
    const DNA* endereco_A = (const DNA*) a; // identifica a como um tipo const DNA*
    const DNA* endereco_B = (const DNA*) b; // identifica b como um tipo const DNA*
    
    if (endereco_A -> inversoes < endereco_B -> inversoes) return -1;   // compara as inversoes
    if (endereco_A -> inversoes > endereco_B -> inversoes) return 1;

    return 0;
}

int desordenar(int j, int inversoes, char* linha) {
    char temp;
    if (linha[j] > linha[j + 1]) {  //se estiver na ordem errada, inverte os dois
        temp = linha[j];
        linha[j] = linha[j + 1];
        linha[j + 1] = temp;
        inversoes += 1; // diz o quão desordenado está
    } else {
        return inversoes;
    }

    if (j != 0) {   // se j == 0 acaba a recursão
        return desordenar(j - 1, inversoes, linha); 
    } else {
        return inversoes;
    }
}

int main(void) {
    int C, J, K;    // C = número de conjuntos, J = tamanho das strings, K = número de strings
    scanf(" %d", &C);
    for (int i = 0; i < C; ++i) {   // percorre de conjunto em conjunto
        scanf(" %d %d", &J, &K);
        DNA* conjunto = (DNA*) calloc(K, sizeof(DNA));
        for (int k = 0; k < K; ++k) {   //percorre as linhas do conjunto
            char* linha_temp = (char*) calloc(J + 1, sizeof(char)); // linha temporária que será desordenada
            conjunto[k].linha = (char*) calloc(J + 1, sizeof(char)); 
            scanf(" %[^\n]", conjunto[k].linha);
            strcpy(linha_temp, conjunto[k].linha);

            for (int j = 0; j < J - 1; ++j) {
                conjunto[k].inversoes += desordenar(j, 0, linha_temp);
            }

            free(linha_temp);
        }
        qsort(conjunto, K, sizeof(DNA), comparar);  // deixa do menos desordenado para o mais
        for (int k = 0; k < K; ++k) {
            printf("%s\n", conjunto[k].linha);
            free(conjunto[k].linha);
        }
        printf("\n");
        free(conjunto);
    }
    return 0;
}