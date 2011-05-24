#include <stdio.h>
#include <stdlib.h>
int a[1010], pos[1010];

int best[1010][1010], bef[1010][1010];

int main(void) {
    int i, j, l, N, T, x, y;

    scanf("%d", &T);

    while(T--) {
        scanf("%d", &N);

        for (i=1; i<=N; i++) {
            scanf("%d", &a[i]);

            pos[a[i]] = i;
        }

        for (i=1; i<=N; i++) {
            bef[i][0] = 0;

            for (j=1; j<=N; j++) {
                bef[i][j] = bef[i][j-1];

                if ( pos[j] < pos[i] ) bef[i][j]++;
            }
        }

        for (i=1; i<=N; i++ ){
            best[i][i] = pos[i];
        }

        for (l=2; l<=N; l++) {
            for (i=1; i<=N-l+1; i++) {
                j = i+l-1;

                x = best[i+1][j] + l * (pos[i] - (bef[i][j]  -  bef[i][i]));
                y = best[i][j-1] + l * (pos[j] - (bef[j][j-1]-bef[j][i-1]));

                if ( x < y ) best[i][j] = x;
                else best[i][j] = y;
            }
        }

        printf("%d\n", best[1][N]);
    }

    return 0;
}
