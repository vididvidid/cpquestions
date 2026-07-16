/*
 * File: 1355A.c
 * Author: vididvidid 
 * Created: 2026-07-16 15:12:58
 */

/*
 * recurrence relation an+1 = an + min(an) + max(an)
 *
 */

#include <stdio.h>
#include <limits.h>

#define int unsigned long long
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

int mm (int a)
{
    int mn = ULLONG_MAX, mx = 0ULL;
    while (a > 0)
    {
        int tmp = a % 10;
        mn = MIN(mn, tmp);
        mx = MAX(mx, tmp);
        a /= 10;
    }
    return mx * 10 + mn;
}

void solve()
{
    int a, k;
    scanf("%llu %llu", &a, &k);
    if (k == 1)
    {
        printf("%llu\n", a);
        return;
    }

    for (int i = 2; i <= k; i++)
    {
        int s = mm(a);
        int tmp = a;
        /* printf("D: a = %llu mn = %llu mx = %llu\n",tmp, s % 10, s/10); */
        a = tmp + ((s % 10) * (s / 10));
    }

    printf("%llu\n",a);
}

signed main()
{
    int t;
    scanf("%llu", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
