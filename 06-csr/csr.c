#include <stdio.h>
#include <stdlib.h>

struct matriz {
    int i, j, x;    // i, j são coodenadas da matriz e x é o valor do número nessas coordenadas
};

typedef struct matriz Matriz;

int comparar(const void *a, const void *b) {
    const Matriz* endereco_A = (const Matriz*) a; // identifica a como um tipo const Ponto*
    const Matriz* endereco_B = (const Matriz*) b; // identifica b como um tipo const Ponto*
    
    if (endereco_A -> i < endereco_B -> i) return -1;   // compara os is
    if (endereco_A -> i > endereco_B -> i) return 1;

    if (endereco_A -> j < endereco_B -> j) return -1;   // compara os js
    if (endereco_A -> j > endereco_B -> j) return 1;
    return 0;
}

int procurar_em_C(int* A, int* C, int j, int comeco, int fim) { // checa se a coluna j da linha i (identificada no procurar_M) tem número diferente de 0 
    for (int n = comeco; n < fim; ++n) {
        if (C[n] == j) { 
            return A[n];    // A e C têm o mesmo número de elementos k. O A[0] corresponde ao x do j de C[0] e assim por diante
        } 
    }
    return 0;   // significa que a coluna j não estava em C para a linha i, portanto seu valor é 0
}

int procurar_em_M(int* A, int* C, int* R, int m, int i, int j) {    // checa se a linha i tem números diferentes de 0
    if (i > m) {    // se i for maior do que o número de linhas identificadas, ele tem que ser 0
        return 0;
    }

    int comeco, fim;
    comeco = R[i];
    fim = R[i + 1];
    if (comeco != fim) { 
        return procurar_em_C(A, C, j, comeco, fim); // significa que a linha tem números diferentes de 0
    } else {
        return 0;   // significa que a linha só tem 0
    }
}

int* arrumar_vetores(Matriz* M, int* A, int* C, int k) {
    qsort(M, k, sizeof(Matriz), comparar);   // deixa em ordem crescente, dando prioridade para o i e depois para o j
    int linhas = M[k - 1].i + 1; // linhas = a linha com o maior i que possui números diferentes de 0
    int *R = (int*) calloc(linhas + 1, sizeof(int));
    for (int n = 0; n < k; ++n) {
        A[n] = M[n].x;
        C[n] = M[n].j;
        ++R[M[n].i + 1];    // toda vez que uma linha i aparece, adiciona 1 para o correspondente R[i +1]
    }

    for (int n = 0; n <= linhas ; ++n) { // soma o R[n] com o anterior para que ele represente o total de aparições de números != 0 até aquela linha
        if (n != 0) {
            R[n] += R[n - 1];
        }
    }
    return R;
}


int main(void) {
    int k, i, j;
    scanf(" %d", &k);
    Matriz *M = (Matriz*) malloc(k * sizeof(Matriz));
    int *A = (int*) malloc(k * sizeof(int));
    int *C = (int*) malloc(k * sizeof(int));
    int *R;
    for (int n = 0; n < k; ++n) { 
        scanf(" %d %d %d", &M[n].i, &M[n].j, &M[n].x);
    }

    R = arrumar_vetores(M, A, C, k);

    while(scanf(" %d %d", &i, &j) == 2) {
        if (i == -1 && j == -1) {
            break;
        }
        printf("(%d,%d) = %d\n", i, j, procurar_em_M(A, C, R, M[k - 1].i, i, j));
    }

    free(M);
    free(A);
    free(C);
    free(R);
    return 0;
}