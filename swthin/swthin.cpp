#include <cstdio>
#include <cstdlib>
#include <map>

using namespace std;

int gcd(int a, int b) {
    if ( b == 0 ) return a;

    return gcd(b, a%b);
}

struct point {
    int x, y;
} p[1010];

int main(void) {
    int i, j, k, N, test = 0, ans, a, b, c, r;
    pair<int, int> q;

    while(scanf("%d", &N) && N) {
        test++;

        for (i=1; i<=N; i++) {
            scanf("%d %d", &p[i].x, &p[i].y);
        }

        ans = 0;

        for (i=1; i<=N; i++) {
            map< pair<int, int>, int > A;

            for (j=i+1; j<=N; j++) {
                a = p[i].x - p[j].x;
                b = p[i].y - p[j].y;

                if ( a == 0 ) {
                    q = make_pair(0, -1);
                }
                else if ( b == 0 ) {
                    q = make_pair(-1, 0);
                }
                else {
                    if ( b < 0 ) {
                        a = -a;
                        b = -b;
                    }

                    c = gcd(a, b);

                    a /= c; b /= c;

                    q = make_pair(a , b);
                }

                r = (++A[q]);

                if ( r + 1 > ans ) ans = r + 1;
            }
        }		

        if ( ans < 4 ) ans = 0;

        printf("Photo %d: %d points eliminated\n", test, ans);
    }

    return 0;
}
