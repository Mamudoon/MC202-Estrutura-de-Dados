#include <stdio.h>

int main(){
    int i;
    int bandejas;
    int latas;
    int copos;
    int total = 0;

    scanf("%d", &bandejas);
    for (i = 0; i < bandejas; i++) {
        scanf("%d %d", &latas, &copos);
        if (latas > copos) {
            total += copos;
        }
    }
    printf("%d", total);
    return 0;
}