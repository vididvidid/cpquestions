/*
 * File: 2103A.c
 * Author: vididvidid 
 * Created: 2026-04-22 12:56:53
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n], cnt[n+1];
    for (int i = 0; i <= n; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
        cnt[arr[i]]++;
    }
    int cn = 0;
    for (int i = 0; i <= n; i++)
    {
        if (cnt[i]>=1) cn++;
    }
    printf("%d \n",cn);
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
