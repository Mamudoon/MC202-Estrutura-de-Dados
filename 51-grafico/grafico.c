#include <stdio.h>

int main(void) {
    int i, j;
    char c;
    while(scanf(" (%d,%d,%c)", &i, &j, &c) == 3) {
        if (i/10 < 1) {
            printf("   %d ", i);
        } else if (i/10 < 10) {
            printf("  %d ", i);
        } else if (i/10 < 100) {
            printf(" %d ", i);
        } else {
            printf("%d ", i);
        }
        printf("|");
        for (int n = 0; n < j; ++n) {
            printf("%c", c);
        }
        printf(" %d\n", j);
    }
    return 0;
}