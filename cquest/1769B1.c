/*
 * File: 1769B1.c
 * Author: vididvidid 
 * Created: 2026-05-30 16:58:13
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);

    int a[105];
    long long sum = 0;

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
    }

    int ans[101] = {0};
    ans[0] = 1;

    long long total = 0;

    for (int i = 0; i < n; i++)
    {
        for (long long x = 1; x <= a[i]; x++) {
            int p1 = (100LL * x) / a[i];

            int p2 = (100LL * (total + x)) / sum;

            if (p1 == p2) {
                ans[p1] = 1;
            }
            
        }
        total += a[i];
    }

    for (int i = 0; i <= 100; i++) {
        if (ans[i]) {
            printf("%d\n",i);
        }
    }
}

int main()
{
    solve();
}
