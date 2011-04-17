#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500
#define Q 2000

int main(void) {
    freopen("input.txt", "w", stdout);
    int i, j, k, a, b, c, d;

    srand(time(NULL));

    printf("%d\n", N);

    for (k=0; k<=1; k++) {
        for (i=1; i<=500; i++) {
            for (j=1; j<=500; j++) {
                printf("%d ", rand()%1000000);
            }
            printf("\n");
        }
    }

    printf("%d\n", Q);

    for (i=0; i<Q; i++) {
        printf("%d ", rand()%3);

        a = rand()%N + 1;
        b = rand()%(N-a+1) + a;
        c = rand()%N + 1;
        d = rand()%(N-c+1) + c;
        printf("%d %d %d %d\n", a, c, b, d);
    }

    return 0;
}

