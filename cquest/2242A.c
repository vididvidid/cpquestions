#include <stdio.h>

void solve() {
    int k;
    scanf("%d", &k);
    int x = 0, m = 0;
    for (int i = 0; i < k; i++) {
        int c;
        scanf("%d", &c);
        if (c > x) x = c;
        if (c >= 2) m++;
    }
    if (x >= 3 || m >= 2) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
}

int main() {
    int t;
    if (scanf("%d", &t) == 1) {
        while (t--) {
            solve();
        }
    }
    return 0;
}