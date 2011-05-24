#include <stdio.h>
#include <stdlib.h>
#define INF 99000000

int x[200010], y[200010], smallx[200010];

int p[200010];

int N;

int xs[200010], xss[200010], xcnt;

int compare(const void *a, const void *b) {
    return *((int *)a) - *((int *)b);
}

int compareA(const void *a, const void *b) {
    int c = *((int *)a), d = *((int *)b);

    if ( y[c] == y[d] ) {
        return x[c] - x[d];
    }

    return y[c] - y[d];
}

int compareB(const void *a, const void *b) {
    int c = *((int *)a), d = *((int *)b);

    if ( y[c] == y[d] ) {
        return x[d] - x[c];
    }

    return y[c] - y[d];
}

int searchx(int a) {
    int lo = 1, hi = xcnt, mid;

    while (lo!=hi) {
        mid = (lo+hi)/2;

        if ( xss[mid] == a ) { return mid; }

        if ( xss[mid] < a ) {
            lo = mid+1;
        }
        else {
            hi = mid-1;
        }
    }

    return lo;
}

int bit[200010];

int query(int pos) {
    int ans = -INF;

    while(pos > 0) {
        if ( bit[pos] > ans ) {
            ans = bit[pos];
        }

        pos -= (pos & -pos);
    }

    return ans;
}

void insert(int pos, int a) {	
    while(pos <= N) {
        if ( bit[pos] < a ) {
            bit[pos] = a;
        }

        pos += (pos & -pos);
    }
}

int answer[200010];

int main(void) {
    int i, closest, z, sum;

    scanf("%d", &N);

    for (i=1; i<=N; i++) {
        scanf("%d %d", &x[i], &y[i]);

        xs[i] = x[i];

        p[i] = i;		
    }

    qsort(&xs[1], N, sizeof(int), compare);

    xss[xcnt = 1] = xs[1];

    for (i=2; i<=N; i++) {
        if ( xs[i] != xss[xcnt] ) {
            xss[++xcnt] = xs[i];
        }
    }

    for (i=1; i<=N; i++) {
        smallx[i] = searchx(x[i]);

        answer[i] = INF;
    }

    /* case 1 */
    qsort(&p[1], N, sizeof(int), compareA);
    for (i=1; i<=N; i++) bit[i] = -INF;

    for (i=1; i<=N; i++) {
        z = p[i];
        closest = query(smallx[z]);

        answer[z] = x[z] + y[z] - closest;

        insert(smallx[z], x[z] + y[z]);
    }

    /* case 2 */
    for (i=1; i<=N; i++) bit[i] = -INF;

    for (i=N; i>=1; i--) {
        z = p[i];
        closest = query(N-smallx[z]+1);
        sum = - x[z] - y[z];

        if ( sum - closest < answer[z] ) {
            answer[z] = sum - closest;
        }

        insert(N-smallx[z]+1, sum);		
    }

    /* case 3 */
    qsort(&p[1], N, sizeof(int), compareB);
    for (i=1; i<=N; i++) bit[i] = -INF;

    for (i=1; i<=N; i++) {
        z = p[i];
        closest = query(N-smallx[z]+1);
        sum = - x[z] + y[z];

        if ( sum - closest < answer[z] ) {
            answer[z] = sum - closest;
        }

        insert(N-smallx[z]+1, sum);
    }

    /* case 4 */
    for (i=1; i<=N; i++) bit[i] = -INF;

    for (i=N; i>=1; i--) {
        z = p[i];
        closest = query(smallx[z]);
        sum = x[z] - y[z];

        if ( sum - closest < answer[z] ) {
            answer[z] = sum - closest;
        }

        insert(smallx[z], sum);
    }

    /* answer */
    for (i=1; i<=N; i++) {
        printf("%d\n", answer[i]);
    }

    return 0;
}
