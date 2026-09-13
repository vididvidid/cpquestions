/*
 * File: 1279B.c
 * Author: vididvidid 
 * Created: 2026-09-12 20:05:06
 */

/*
 * take sum of elements till that second and keep mainating max element and then
 * just remove that and add another if it is possible than good..
 *
 */

#include <stdio.h>

#define int long long

void solve()
{
    int n, s;
    scanf("%lld %lld", &n, &s);

    int sum = 0, max_idx = 0, max_val = 0, ans = 0;

    int found = 0;

    for (int i = 1; i <= n; i++) 
    {
        int a;
        scanf("%lld", &a);

        if (!found) {
            sum += a;

            if (a > max_val) 
            {
                max_val = a;
                max_idx = i;
            }

            if (sum > s) 
            {
                ans = max_idx;
                found = 1;
            }
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
