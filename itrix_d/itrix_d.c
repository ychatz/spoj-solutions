#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)

long long arr[2][511][511], sum[2][40][40], inv[40][40];
int bsize;

void cinv(int R, int C, int r1, int c1, int r2, int c2) {
    int i, j;
    long long a, b;

    r1 = max(r1, R * bsize);
    r2 = min(r2, (R+1) * bsize - 1);
    c1 = max(c1, C * bsize);
    c2 = min(c2, (C+1) * bsize - 1);

    for (i=r1; i<=r2; i++) {
        for (j=c1; j<=c2; j++) {
            a = arr[0][i][j];
            b = arr[1][i][j];

            sum[0][R][C] += b-a;
            sum[1][R][C] += a-b;

            arr[0][i][j] = b;
            arr[1][i][j] = a;
        }
    }
}

long long csum(int k, int R, int C, int r1, int c1, int r2, int c2) {
    int i, j;
    long long ans = 0;

    r1 = max(r1, R * bsize);
    r2 = min(r2, (R+1) * bsize - 1);
    c1 = max(c1, C * bsize);
    c2 = min(c2, (C+1) * bsize - 1);

    for (i=r1; i<=r2; i++) {
        for (j=c1; j<=c2; j++) {
            ans += arr[k][i][j];
        }
    }

    return ans;
}

inline int whole(int R, int C, int r1, int c1, int r2, int c2) {
    return (R * bsize >= r1 && (R + 1) * bsize - 1 <= r2 && C * bsize >= c1 && (C + 1) * bsize - 1 <= c2);
}

int main(void) {
    /* freopen("input.txt", "r", stdin); */
    register int i, j, k;
    int N, Q, type, r1, c1, r2, c2, R1, R2, C1, C2;
    long long ans;

    scanf("%d", &N);

    bsize = sqrt(N); /* bucket size */

    for (k=0; k<=1; k++) {
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) {
                scanf("%lld", &arr[k][i][j]);
                sum[k][i/bsize][j/bsize] += arr[k][i][j];
            }
        }
    }

    scanf("%d", &Q);

    while(Q--) {
        scanf("%d", &type);

        scanf("%d %d %d %d", &r1, &c1, &r2, &c2);
        c1--; r1--; c2--; r2--;

        R1 = r1/bsize; R2 = r2/bsize;
        C1 = c1/bsize; C2 = c2/bsize;

        switch(type) {
            case 0: /* swap */
                for (i=R1; i<=R2; i++) {
                    for (j=C1; j<=C2; j++) {
                        if ( whole(i, j, r1, c1, r2, c2) ) {
                            inv[i][j] ^= 1;
                        }
                        else {
                            cinv(i, j, r1, c1, r2, c2);
                        }
                    }
                }
                break;

            case 1: /* sum of X */
                ans = 0;

                for (i=R1; i<=R2; i++) {
                    for (j=C1; j<=C2; j++) {
                        if ( whole(i, j, r1, c1, r2, c2) ) {
                            ans += sum[ inv[i][j] ][ i ][ j ];
                        }
                        else {
                            ans += csum(inv[i][j], i, j, r1, c1, r2, c2);
                        }
                    }
                }

                printf("%lld\n", ans);

                break;

            case 2: /* sum of Y */
                ans = 0;


                for (i=R1; i<=R2; i++) {
                    for (j=C1; j<=C2; j++) {
                        if ( whole(i, j, r1, c1, r2, c2) ) {
                            ans += sum[ 1^inv[i][j] ][ i ][ j ];
                        }
                        else {
                            ans += csum(1^inv[i][j], i, j, r1, c1, r2, c2);
                        }
                    }
                }

                printf("%lld\n", ans);

        }
    }

    return 0;
}
