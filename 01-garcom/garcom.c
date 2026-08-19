#include <stdio.h>

int main(void) {
    int bandejas, latas, copos, quebrados = 0, i = 0;

    scanf("%d", &bandejas); 

    for (i = 0; i < bandejas; i++) { //roda para cada bandeja

        scanf("%d %d", &latas, &copos); 

        if (latas > copos) { 
            quebrados += copos; 
        }
    }

    printf("%d\n", quebrados);
    return 0;
}