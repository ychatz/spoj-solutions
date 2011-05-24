#include <stdio.h>
#include <stdlib.h>
#define INF 99000000

int e[310][310], c[310][310], ecnt[310], depth[310], srt[310];

int dp[310][310][2];

int min(int a, int b) { return ( a < b ? a : b ); }

int compare(const void *a, const void *b) {
    int c = *((int *)a), d = *((int *)b);

    return depth[d] - depth[c];
}

int DFS(int id, int lvl) {
    int i;

    depth[id] = lvl;

    for (i=1; i<=ecnt[id]; i++) {
        if ( depth[ e[id][i] ] ) continue;

        DFS( e[id][i], lvl+1 );
    }
}

int main(void) {
    int i, j, k, m, a, b, p, q, N, M, K, T = 10, cur, next, cnt;

    while(T--) {
        scanf("%d %d %d", &N, &M, &K);

        M--;		

        for (i=1; i<=N; i++) {
            ecnt[i] = 0;
            depth[i] = 0;
            srt[i] = i;

            for (j=0; j<=K; j++) {
                dp[i][j][0] = dp[i][j][1] = INF;
            }
        }

        for (i=1; i<N; i++) {
            scanf("%d %d %d", &a, &b, &q);

            e[a][ ++ecnt[a] ] = b;
            c[a][   ecnt[a] ] = q;

            e[b][ ++ecnt[b] ] = a;
            c[b][   ecnt[b] ] = q;
        }

        if ( N-K < M ) {
            printf("-1\n");

            continue;
        }

        DFS(1, 1);

        qsort(&srt[1], N, sizeof(int), compare);

        if ( M > 1 ) {
            for (i=1; i<=N; i++) {
                cur = srt[i];

                for (k=0; k<=K; k++) {
                    dp[cur][k][0] = dp[cur][k][1] = INF;
                }

                dp[cur][0][0] = 0;
                dp[cur][1][1] = 0;

                for (j=1; j<=ecnt[cur]; j++) {
                    next = e[cur][j];

                    if ( depth[next] <= depth[cur] ) continue;

                    for (k=K; k>=1; k--) {
                        for (m=0; m<k; m++) {
                            dp[cur][k][0] = min( dp[cur][k][0], dp[cur][m][0] + min(dp[next][k-m][1], dp[next][k-m][0]) );
                        }
                    }

                    for (k=K; k>=2; k--) {
                        for (m=0; m<k; m++) {
                            dp[cur][k][1] = min( dp[cur][k][1], dp[cur][m][1] + min(dp[next][k-m][1] + c[cur][j], dp[next][k-m][0]) );
                        }
                    }
                }
            }

            printf("%d\n", dp[1][K][1]);
        }
        else {
            for (i=1; i<=N; i++) {
                cur = srt[i];				

                cnt = 0;

                for (j=1; j<=ecnt[cur]; j++) {
                    next = e[cur][j];

                    if ( depth[next] <= depth[cur] ) continue;

                    cnt++;

                    if ( cnt == 1 ) {
                        for (k=1; k<=K; k++) {
                            dp[cur][k][1] = min(dp[next][k-1][0]            , dp[next][k-1][1] + c[cur][j]);
                            dp[cur][k][0] = min(dp[next][k  ][0] + c[cur][j], dp[next][k  ][1]            );
                        }
                        dp[cur][0][1] = INF;
                        dp[cur][0][0] = dp[next][0][0] + c[cur][j];
                    }
                    else {
                        for (k=K; k>=1; k--) {
                            p = INF;
                            q = INF;
                            for (m=0; m<=k; m++) {
                                p = min(p, dp[cur][k-m][0] + min(dp[next][m][0] + c[cur][j], dp[next][m][1]) );
                                q = min(q, dp[cur][k-m][1] + min(dp[next][m][1] + c[cur][j], dp[next][m][0]) );
                            }

                            dp[cur][k][0] = p;
                            dp[cur][k][1] = q;
                        }

                        dp[cur][0][0] += dp[next][0][0] + c[cur][j];
                    }
                }

                if ( cnt == 0 ) {
                    for (k=0; k<=K; k++) dp[cur][k][0] = dp[cur][k][1] = INF;

                    dp[cur][0][0] = 0;
                    dp[cur][1][1] = 0;
                }
            }

            printf("%d\n", dp[1][K][1]);
        }
    }	

    return 0;
}
