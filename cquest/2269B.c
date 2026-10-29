/*
 * File: 2269B.c
 * Author: vididvidid 
 * Created: 2026-10-29 18:46:17
 */

/*
 * apply f(x) = sum of squared digits to every number every night.
 * count pairs that, from some night on, show the same number on 
 * every night.
 *
 */

#include <stdio.h>

#define int long long

int f(int x)
{
    int s = 0;
    while (x > 0)
    {
        int d= x % 10;
        s += d * d;
        x /= 10;
    }

    return s;
}

void solve()
{
    int n;
    scanf("%lld", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    int cnt[1000] = {0};
    for (int i = 0; i < n; i++)
    {
        int x = arr[i];
        for (int night = 0; night < 20; night++)
        {
            x = f(x);
        }
        cnt[x]++;
    }


    int ans = 0;
    for (int v = 0; v < 1000; v++)
    {
        ans += cnt[v] * (cnt[v] - 1) / 2;
    }
    printf("%lld\n",ans);
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
