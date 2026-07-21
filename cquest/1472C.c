/*
 * File: 1472C.c
 * Author: vididvidid 
 * Created: 2026-07-21 21:54:31
 */

/*
 * array a of size n 
 *
 */
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);

    long long a[n + 1];
    long long dp[n + 1];

    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &a[i]);
        dp[i] = 0;
    }

    long long max_score = 0;

    for (int i = n; i >= 1; i--)
    {
        long long next_index = i + a[i];

        if (next_index <= n)
        {
            dp[i] = a[i] + dp[next_index];
        }
        else
        {
            dp[i] = a[i];
        }

        if (dp[i] > max_score)
        {
            max_score = dp[i];
        }
    }

    printf("%lld\n", max_score);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
