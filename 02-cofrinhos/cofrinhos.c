#include <stdio.h>

int numero_depositos(void) { // lê o número de depósitos que serão feitos
    int n;
    scanf("%d", &n);

    return n;
}

int diferenca_cofrinhos(void) { // lê o quanto foi depositado em cada cofre e faz a diferença
    int J, Z, diff;
    scanf("%d %d", &J, &Z);
    diff = J - Z;

    return diff;
}

int main(void) {
    int teste = 1, flag = 1, i = 0;
    while (flag == 1) { // loop while para fazer todos os testes da entrada

        int n = numero_depositos(), diff = 0; // diff precisa voltar a ser 0, pois ele não é mantido de teste em teste
        
        if (n == 0) // termina o programa
            break;

        printf("Teste %d\n", teste);
        teste++; //incrementa para o próximo teste

        for (i = 0; i < n; i++) { // resultado das diferenças em cada depósito
            diff += diferenca_cofrinhos();
            printf("%d\n", diff);
        }

        printf("\n"); //pulo de linha no final para separar os testes

    }
    
    return 0;
}