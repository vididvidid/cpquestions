#include <stdio.h>



void solve() {

    int t, n, a, m, s, i;

    if (scanf("%d", &t) != 1) return;

    while (t--) {

        scanf("%d", &n);

        s = 0;

        m = 2000;

        for (i = 0; i < n; i++) {

            scanf("%d", &a);

            if (a < m) m = a;

            s += m;

        }

        printf("%d\n", s);

    }

}



int main() {

    solve();

    return 0;

}
