/*
 * File: 2134C.c
 * Author: vididvidid 
 * Created: 2026-07-11 17:48:07
 */

/*
 * given an array we need to make array so that sum of even indices > sum of odd
 * indices. We can decrease any number by 1 but they should be non-negative
 * return minimum number of oprn.. 
 *
 * n -> 2 * 10^5  => < O(n)
 * ai -> 10^9     => long long
 */

#include <stdio.h>
#include <limits.h>

#define int long long
#define ABS(a) (a) > 0 ? (a) : -1 * (a)

void solve()
{
    int n;
    scanf("%lld", &n);
    int arr[n + 1];
    arr[0] = 0;
    int me = LLONG_MAX;
    int se = 0, so = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
        if (i % 2 == 0)
        {
            se += arr[i];
            if (me > arr[i])
            {
                me = arr[i];
            }
        }
        else {
            so += arr[i];
        }
    }

    int cn = 0;
    for (int i = 1; i <= n; i++)
    {
        if (i % 2 != 0)
        {
            if (arr[i] > me)
            {
                cn += ABS(arr[i] - me);
            }
        }
    }
    
    int ans = 0;
    so -= cn;
    if (so > se)
    {
        ans += ABS(so - se);
    }
    printf("%lld\n",ans + cn);
}

int main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
