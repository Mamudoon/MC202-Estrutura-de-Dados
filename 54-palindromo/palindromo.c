#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct lista {
    char* palindromo;
    struct lista* next;
} Lista;

Lista* criar_elemento(char *temp, Lista *ultimo, int tamanho) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->palindromo = (char*) malloc(tamanho*sizeof(char));
    strcpy(novo->palindromo, temp);
    ultimo->next = novo;
    novo->next =NULL;
    return novo;
}

void remover(Lista* antes){ 
    Lista* lixo;
    lixo = antes->next;
    antes->next = lixo->next;
    free(lixo->palindromo);
    free(lixo);
}

void achar_palindromos(Lista* lista, int tamanho) {
    int n_eh = 0;
    Lista* ultimo = lista;
    char* temp;
    for (int j = 2; j <= tamanho; ++j) {
        for (int i = 0; i+j <= tamanho; ++i) {
            temp = (char*) malloc((j+2)*sizeof(char));
            for (int k = 0; k <= j+1; ++k) {
                temp[k] = tolower(lista->palindromo[k+i]);
            }
            temp[j+1] = '\0';
            for (int n = 0; n <= j; ++n) {
                if (temp[n] != temp[j-n]) {
                    n_eh = 1;
                    break;
                }
            }
            for (Lista *p = lista->next; p != NULL; p = p->next) {
                if (strcmp(p->palindromo, temp) == 0) {
                    n_eh = 1;
                }
            }            
            if (n_eh == 0) {
                ultimo = criar_elemento(temp, ultimo, j+2);
            }
            n_eh = 0;
            free(temp);
        }
        for (Lista *p = lista->next; p != NULL && p->next != NULL; p = p->next) {
            for (Lista *a = p; a != NULL && a->next != NULL; a = a->next) {
                if (strstr(a->next->palindromo, p->palindromo) != NULL) {
                    remover(a);
                }
            }
        }  
    }
}

int main(void) {
    Lista* primeiro = (Lista*) malloc(sizeof(Lista));
    primeiro->next = NULL;
    int tamanho, i = 0;
    char palavra[257];
    while(scanf("%s", palavra) == 1) {
        tamanho = strlen(palavra);
        primeiro->palindromo = (char*) malloc((tamanho+1)*sizeof(char));
        strcpy(primeiro->palindromo, palavra);
        achar_palindromos(primeiro, tamanho);
        for (Lista *p = primeiro->next; p != NULL; p = p->next) {
            i += 1;
            //printf("Resultado %s\n", p->palindromo);
            if (i == 2) {
                printf("%s\n", palavra);
                break;
            }
        }
        while(primeiro->next != NULL) {
            remover(primeiro);
        }
        free(primeiro->palindromo);
        i = 0;
        memset(palavra, 0, 257);
    }
    free(primeiro);
    return 0;
}