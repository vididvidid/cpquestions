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
    int arr[n + 2];
    arr[0] = 0;
    arr[n + 1] = 0;

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    int ans = 0;

    for (int i = 2; i <= n; i += 2)
    {
        int left = arr[i - 1];
        int right = (i + 1 <= n) ? arr[i + 1] : 0;
        int val = arr[i];

        int extra = (left + right) - val;

        if (extra > 0)
        {
            ans += extra;

            int rv = (right < extra) ? right : extra;
            if (i + 1 <= n)
            {
                arr[i + 1] -= rv;
            }
        }
    }

    printf("%lld\n", ans);
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
