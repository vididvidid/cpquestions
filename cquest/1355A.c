/*
 * File: 1355A.c
 * Author: vididvidid 
 * Created: 2026-07-16 15:12:58
 */

/*
 * recurrence relation an+1 = an + min(an) + max(an)
 *
 * observation that i forgot ..
 * after sometime there will be min as 0 only.. so all it bcome 0 * max = 0
 *
 * here important point was we are adding something to original a and that is
 * multiple of min * max so as min becoame 0 the a will never change it will
 * stuck at the same number
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
        int mn = s % 10;
        int mx = s / 10;
        if (mn == 0)
            break;
        a += mn * mx;
        
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
