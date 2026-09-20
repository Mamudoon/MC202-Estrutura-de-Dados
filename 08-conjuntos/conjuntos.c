#include "conjuntos.h"

int main(void) {
    char comando;
    int i, j, k; // escolhi 3 variáveis porque é o máximo que qualquer comando exige, i.e união em i de j e k.
    Elemento lista[128] = {0}, sentinela[128] = {0}; // lista com o primeiro elemento de todos os conjuntos, lista com o sentinela de todos
    // o sentinela aponta para o elemento logo antes dele

    while(scanf(" %c", &comando) == 1) {
        switch(comando) {
            case 'c':
                scanf(" %d", &i); // o número do conjunto i criado
                comando_c(&lista[i], &sentinela[i]);
                break;

            case 'i':
                scanf(" %d %d", &i, &j); // o número do conjunto i e número de elementos inseridos j
                comando_i(j, &lista[i], &sentinela[i]);
                break;

            case 'r':
                scanf(" %d %d", &i, &j); // o número do conjunto i e número de elementos removidos j
                comando_r(j, &lista[i], &sentinela[i]);
                break;

            case 'u':
                scanf(" %d %d %d", &i, &j, &k); // o número do conjunto final i, número do conjuto1 j e número do conjunto2 k que sofrem a união
                comando_u(&lista[i], &lista[j], &lista[k], &sentinela[i], &sentinela[j], &sentinela[k]);
                break;

            case 'n':
                scanf(" %d %d %d", &i, &j, &k); // o número do conjunto final i, número do conjuto1 j e número do conjunto2 k que sofrem a interseção
                comando_n(&lista[i], &lista[j], &lista[k], &sentinela[i], &sentinela[j], &sentinela[k]);
                break;

            case 'm':
                scanf(" %d %d %d", &i, &j, &k); // o número do conjunto final i, número do conjuto1 j e número do conjunto2 k que sofrem a diferença. i = j - k
                comando_m(&lista[i], &lista[j], &lista[k], &sentinela[i], &sentinela[j], &sentinela[k]);
                break;

            case 'e':
                scanf(" %d %d", &i, &j); // o número do conjunto i e o elemento j sendo conferido dentro do conjunto
                comando_e(i, j, &lista[i], &sentinela[i]);
                break;

            case 'p':
                scanf(" %d", &i); // o número do conjunto i imprimido
                printf("C%d = {", i);
                comando_p(&lista[i], &sentinela[i] );
                break;

            case 't':
            for (int a = 0; a < 128; ++a) { // remover todos os mallocs antes de fechar
                    comando_c(&lista[a], &sentinela[a]);
                }
                return 0;

            default:
                continue;
        }
    }
}