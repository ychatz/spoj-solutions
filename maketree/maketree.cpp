#include <cstdio>
#include <cstdlib>
#include <queue>

using namespace std;

vector< vector<int> > ine;
int outdeg[100010], indeg[100010], sort[100010], scnt, pos[100010];
queue<int> Q;

int main(void) {
    // freopen("input.txt", "r", stdin);
    int i, j, r, K, N, u;

    scanf("%d %d", &N, &K);

    ine.resize(N + 1);

    for (i=1; i<=K; i++) {
        scanf("%d", &j);

        outdeg[i] = j;

        while(j--) {
            scanf("%d", &r);
            indeg[ r ]++;
            ine[ r ].push_back(i);
        }
    }

    /* topological sort O(|E| + |V|) */
    for (i=1; i<=N; i++) {
        if ( outdeg[i] == 0 ) {
            Q.push(i);
        }
    }

    while (!Q.empty()) {
        u = Q.front();
        Q.pop();

        sort[++scnt] = u;
        pos[u] = scnt;

        for (i=0; i<indeg[u]; i++) {
            outdeg[ ine[u][i] ]--;

            if ( outdeg[ ine[u][i] ] == 0 ) {
                Q.push(ine[u][i]);
            }
        }
    }

    for (i=1; i<=N; i++) {
        printf("%d\n", sort[pos[i] + 1]);
    }

    return 0;
}

