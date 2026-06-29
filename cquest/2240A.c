/*
 * File: 2240A.c
 * Author: vididvidid 
 * Created: 2026-06-29 22:18:59
 */

#include <stdio.h>

#define int long long

void solve()
{
    int n, k;
    scanf("%lld %lld", &n, &k);

    int total = 0;
    int bc = 1;

    while (n >= bc)
    {
        int take = n / bc;
        if (take >  k)
        {
            take = k;
        }

        total += take;
        n -= take * bc;

        bc *= 2;
    }

    printf("%lld\n", total);
}

signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
