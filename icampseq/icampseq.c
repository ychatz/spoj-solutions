#include <stdio.h>
#include <stdlib.h>

double min[8], max[8], cur, ans;
double a, b, c, d;

int main(void) {
    int i, j, k, N;

    scanf("%d", &N);

    for (i=0; i<=7; i++) {
        min[i] = (1LL<<34);
        max[i] = -(1LL<<34);
    }

    for (i=0; i<N; i++) {
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

        if ( a + b + c + d < min[0] ) min[0] = a + b + c + d;
        if ( a + b + c + d > max[0] ) max[0] = a + b + c + d;

        if ( a + b + c - d < min[1] ) min[1] = a + b + c - d;
        if ( a + b + c - d > max[1] ) max[1] = a + b + c - d;

        if ( a + b - c + d < min[2] ) min[2] = a + b - c + d;
        if ( a + b - c + d > max[2] ) max[2] = a + b - c + d;

        if ( a + b - c - d < min[3] ) min[3] = a + b - c - d;
        if ( a + b - c - d > max[3] ) max[3] = a + b - c - d;

        if ( a - b + c + d < min[4] ) min[4] = a - b + c + d;
        if ( a - b + c + d > max[4] ) max[4] = a - b + c + d;

        if ( a - b + c - d < min[5] ) min[5] = a - b + c - d;
        if ( a - b + c - d > max[5] ) max[5] = a - b + c - d;

        if ( a - b - c + d < min[6] ) min[6] = a - b - c + d;
        if ( a - b - c + d > max[6] ) max[6] = a - b - c + d;

        if ( a - b - c - d < min[7] ) min[7] = a - b - c - d;
        if ( a - b - c - d > max[7] ) max[7] = a - b - c - d;

    }

    for (i=0; i<=7; i++) {
        if ( max[i] - min[i] > ans ) ans = max[i] - min[i];
        if ( min[i] - max[i] > ans ) ans = min[i] - max[i];
    }

    printf("%.3lf\n", ans);
    return 0;
}
