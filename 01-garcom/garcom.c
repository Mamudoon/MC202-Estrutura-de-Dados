#include <stdio.h>

int main() {
    int bandejas;
    int latas;
    int copos;
    int total = 0;

    scanf("%d", &bandejas);

    for (int i = 0; i < bandejas; i++) {
        scanf("%d %d", &latas, &copos);
        if (latas > copos) {
            total += copos;
        }
    }

    printf("%d\n", total);

    return 0;
}