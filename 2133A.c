/*
 * File: 2133A.c
 * Author: vididvidid 
 * Created: 2026-04-22 12:48:26
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n],cnt[101],flag = 0;
    for (int i = 0; i < 101; i++) cnt[i] = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
        cnt[arr[i]]++;
        if (cnt[arr[i]] >= 2) {
            flag = 1;
        }
    }
    if (flag)
    {
        printf("YES\n");
    } else 
    {
        printf("NO\n");
    }
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
