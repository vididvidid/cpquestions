/*
 * File: 2104B.c
 * Author: vididvidid 
 * Created: 2026-05-16 04:18:51
 */

#include <stdio.h>

#define int long long


void solve()
{
    int n;
    scanf("%lld",&n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&arr[i]);
    }

    int pmax[n];
    pmax[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        pmax[i] = (arr[i] > pmax[i - 1] ) ? arr[i] : pmax[i - 1];
    }

    int smax[n + 1];
    smax[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        smax[i] = smax[i - 1] + arr[ n - i ];
    }

    for (int k = 1; k <= n; k++)
    {
        int ans = smax[k - 1] + pmax[n - k];
        printf("%lld ",ans);
    }
    printf("\n");

}

signed  main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
