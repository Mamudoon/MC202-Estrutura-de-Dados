#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int eh_caracter_especial_ou_num(char c) {
    if (c >= '0' && c <= '9')
        return 1; //é um número
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        return 0; // é uma letra
    return 1; // é um caracter especial
}

int eh_vogal_ou_cons(char c) {
    if (c == 'A' || c == 'a' || c == 'E' || c == 'e' || c == 'I' || c == 'i' 
        || c == 'O' || c == 'o' || c == 'U' || c == 'u' )
        return 1; // é uma vogal
    return 0; // é uma consoante
}

void traduzir_e_imprimir_palavra(char *frase, char * palavra, int comeco, int i) {
    int pulado = 0, fim;
    for (int j = comeco; j < i; j++) { // percorre a palavra
        if (eh_caracter_especial_ou_num(frase[j]) == 1) // ignora os que não são letras
            pulado += 1;
        else 
            palavra[j - comeco - pulado] = frase[j]; // adiciona as letras para a palavra
    }

    if (pulado != i - comeco) { // não imprime palavra se não houver letras
        int n = i - comeco - pulado; // quantidade de letras
        if (eh_vogal_ou_cons(palavra[0]) == 0) { // se começar com consoante
            // printf("\n%s", palavra);
            palavra[n + 1] = '\0'; // para permitir a concatenação
            palavra[n] = palavra[0];
            palavra[0] = ' '; // adicionei o espaço aqui, pois ele não pode ficar sem nada (por isso o print é diferente)
            strcat(palavra, "ma");

            fim = strlen(palavra); 
            for (int k = 0; k < n; k++) {
                palavra[fim + k] = 'a';
            }
            palavra[fim + n] = '\0';

            printf("%s", palavra);

        } else { // se começar com vogal
            // printf("\n%s", palavra);
            palavra[n] = '\0'; // para permitir a concatenação
            strcat(palavra, "ma");

            fim = strlen(palavra); 
            for (int k = 0; k < n; k++) {
                palavra[fim + k] = 'a';
            }
            palavra[fim + n] = '\0';

            printf(" %s", palavra);
        }
    }
}

int main (void) {
    char frase[300000], palavra[203];
    while (scanf(" %[^\n]", frase) == 1) {
        int soma = 0, valor, comeco = 0, tamanho;
        tamanho = (int) strlen(frase) + 1;
        
        for (int i = 0; frase[i] != '\0'; ) { // percorre a string inteira atrás dos números
            if (frase[i] >= '0' && frase[i] <= '9') { // continua se for um número
                valor = 0; // determina a ordem inicial
                while (frase[i] >= '0' && frase[i] <= '9') {
                    valor = valor * 10 + (frase[i] - '0'); // avança as casas para esquerda com cada novo algarismo
                    i++;
                }
                soma += valor;
            } else
                i++;
        }

        if (soma == 1) 
            printf("%d goat says:", soma); // imprime concordando com 1 sujeito
        else
            printf("%d goats say:", soma); // imprime concordando com mais de 1 sujeito ou 0
        
        for (int i = 0; i < tamanho; i++) { // percorre a string inteira para traduzir as palavras
            if (frase[i] == ' ' || frase[i] == '\0') {
                traduzir_e_imprimir_palavra(frase, palavra, comeco, i);
                memset(palavra, 0, sizeof(palavra)); // formata a string para evitar erros
                comeco = i + 1; // atualiza para o começo da próxima palavra
            }
        }
        printf("\n");
        memset(frase, 0, sizeof(frase)); // formata a string para evitar erros
    }
    return 0;
}