#include <stdio.h>
#include <math.h>

void organizar_vetores(int n, int valor_truque, int *S, int *R) { // coloca os valores de S[] e R[] que é o valor das somas
    int i, j = 0, soma = 0;
    for (i = 0 ; i < n; i++) {
        scanf("%d", &S[i]);
        soma += S[i];
        if (i%valor_truque == valor_truque - 1) { // adiciona as somas para o R[]
            R[j] = soma;
            soma = 0;
            j++;
        }
    }
    if (j == n/valor_truque) // inclui o último valor para R[] quando n % valor_truque != 0
        R[j] = soma;
}

int somar(int x, int y, int n, int valor_truque, int *S, int *R) {
    int elemento_inicial, elemento_final, soma = 0;

    if (y - x < valor_truque -1) { // caso a soma seja menor que valor_truque, vale mais a pena só somar tudo direto
        for (int j = x; j <= y; j++) {
            soma += S[j];
        }
    } 
    else {
        if (x % valor_truque == 0) // determina qual R[] vai começar a soma
            elemento_inicial = x / valor_truque;
        else {
            elemento_inicial = x / valor_truque + 1;
            while (x % valor_truque != 0) { // soma os valores que estão no S[] 
                soma += S[x];
                x++;
            }
        }

        if (y % valor_truque == valor_truque - 1 || y == n - 1) // determina qual R[] vai terminar a soma
            elemento_final = y / valor_truque;
        else {
            elemento_final = y / valor_truque - 1;
            while (y % valor_truque != valor_truque - 1) { // soma os valores que estão no S[] 
                soma += S[y];
                y--;
            }
        }

        for (int i = elemento_inicial; i <= elemento_final; i++) { // soma os valores de R[]
            soma += R[i];
        }
    }
    return soma;
}

int main(void) {
    int n, valor_truque, x, y;
    char comando;

    scanf("%d", &n);
    valor_truque = ceil(sqrt(n)); 

    int S[n], R[valor_truque]; 

    organizar_vetores(n, valor_truque, S, R);

    while (scanf(" %c %d %d", &comando, &x, &y) == 3) {
        if (comando == 's') {
            printf("%d\n", somar(x, y, n, valor_truque, S, R));        
        } 
        else {
            R[x/valor_truque] = R[x/valor_truque] - S[x] + y; // atualiza o valor da soma em R[]
            S[x] = y; //atualiza o valor em S[]
        }
    }
    return 0;
}