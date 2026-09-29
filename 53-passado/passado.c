#include <stdio.h>

int main(void) {
    int dias, periodo, acoes, compra = -1, venda = -1;
    float valor, dinheiro, comeco, total, max;
    scanf(" %d", &dias);
    float valores[dias];
    for (int i = 0; i < dias; ++i) {
        scanf(" %f", &valor);
        valores[i] = valor;
    }
    scanf(" %d", &periodo);
    scanf(" %f", &dinheiro);
    comeco = max = dinheiro;
    for (int i = 0; i < dias; ++i) {
        acoes = dinheiro/valores[i];
        dinheiro = dinheiro - acoes*valores[i];
        for (int j = 1; j <= periodo && i+j < dias; ++j) {
            total = dinheiro + acoes*valores[i+j];
            if (total > max) {
                max = total;
                compra = i;
                venda = j;
            }
        }
        dinheiro = comeco;
    }
    acoes = dinheiro/valores[compra];
    if (compra == -1) {
        printf("Dia da compra: 0\n");
        printf("Valor de compra: R$ 00.00\n");
        printf("Dia da venda: 0\n");
        printf("Valor de venda: R$ 00.00\n");
        printf("Quantidade de acoes compradas: 0\n");
        printf("Lucro: R$ 00.00\n");
    } else {
    printf("Dia da compra: %d\n", compra+1);
    printf("Valor de compra: R$ %.2f\n", valores[compra]);
    printf("Dia da venda: %d\n", compra+venda+1);
    printf("Valor de venda: R$ %.2f\n", valores[compra+venda]);
    printf("Quantidade de acoes compradas: %d\n", acoes);
    printf("Lucro: R$ %.2f\n", max - dinheiro);
    }
    return 0;
}