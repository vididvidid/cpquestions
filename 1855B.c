/*
 * File: 1855B.c
 * Author: vididvidid 
 * Created: 2026-05-21 13:28:18
 */

#include <stdio.h>

#define int unsigned long long

void solve()
{
    int n;
    scanf("%llu",&n);
    int ans = 0;
    for (int i = 1; ;i++)
    {
        if (n % i == 0) ans++;
        else break;
    }
    printf("%llu\n",ans);
}

int main()
{
    int t;
    scanf("%llu",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
