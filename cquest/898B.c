/*
 * File: 898B.c
 * Author: vididvidid 
 * Created: 2026-06-28 21:19:07
 */
#include <stdio.h>

#define int long long

void solve()
{
    int n, a, b;
    scanf("%lld %lld %lld",&n, &a, &b);

    for (int i = 0; i * b <= n; i++)
    {
        int rem = n - (i  * b);

        if (rem % a == 0)
        {
            int x = rem / a;
            printf("YES\n%lld %lld\n", x, i);
            return;
        }
    }

    printf("NO\n");
}

signed main()
{
    solve();
    return 0;
}
