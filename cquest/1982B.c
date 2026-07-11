/*
 * File: 1982B.c
 * Author: vididvidid 
 * Created: 2026-07-11 18:18:04
 */

/*
 * final value of x after doing oprn k times oprn ( incr by 1, divide x by y
 * till its divisible )
 *
 * x = x + 1 -> while (x % y == 0) x /= y;
 *
 * k is also 10^9. so we can't just directly brute force it
 * x any y also goes to 10^9 which means we have to use long long
 *
 * i think we can reduce this division opertion.. this while is dangerous
 * but there doesn't exist any. way because divison will take O(logy x);
 *
 *
 */

#include <stdio.h>

#define int long long

void solve()
{
    int x, y, k;
    scanf("%lld %lld %lld", &x, &y, &k);

    while (k--)
    {
        x += 1;
        while (x % y == 0)
        {
            x /= y;
        }
    }

    printf("%lld\n", x);
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
