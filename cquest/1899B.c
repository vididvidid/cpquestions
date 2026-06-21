/*
 * File: 1899B.c
 * Author: vididvidid 
 * Created: 2026-06-21 19:18:13
 */

/*
 * find the abs difference btw k chunks of weights given n boxes are there..
 *
 * find all divisors of n
 * for each divisor k, get the sum of k chunks
 * find the max and min sum
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define int long long
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

void solve()
{
    int n;
    scanf("%lld", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }

    int prr[n];
    prr[0] = arr[0];
    for (int i = 1; i < n; i++)
    {
        prr[i] = arr[i] + prr[i - 1];
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
    {
        if (n % i == 0)
        {
            int mx = LLONG_MIN;
            int mn = LLONG_MAX;

            for (int j = 0; j < n; j += i)
            {
                int curr;

                if (j == 0) {
                    curr = prr[i - 1];
                }
                else {
                    curr = prr[j + i - 1] - prr[j - 1];
                }

                mx = MAX(mx, curr);
                mn = MIN(mn, curr);
            }

            ans = MAX(ans, mx - mn);
        }
    }

    printf("%lld\n", ans);
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
