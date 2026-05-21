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
    int cn = 1, ans = 1;
    for (int i = 2; i * i <= n; i++)
    {
        if ((n%i==0) && (n%(i-1)==0)) cn++;
        else cn = 1;
        if (cn > ans)
        {
            ans = cn;
        }
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
