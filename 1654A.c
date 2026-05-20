/*
 * File: 1654A.c
 * Author: vididvidid 
 * Created: 2026-04-24 04:00:08
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define int unsigned long long

void solve()
{
    int n;
    scanf("%llu",&n);
    int arr[n];
    for (int i = 0; i < n ;i++){
        scanf("%llu",&arr[i]);
    }
    int mx1 = 0, mx2 = 0;
    for (int i = 0; i < n; i++){
        if (arr[i] > mx1){
            mx2 = mx1;
            mx1 = arr[i];
        } else if (arr[i] > mx2) {
            mx2 = arr[i];
        }
    }
    /* printf("%lld %lld\n",mx1, mx2); */
    printf("%llu\n",mx1+mx2);
}

signed main()
{
    int t;
    scanf("%llu",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
