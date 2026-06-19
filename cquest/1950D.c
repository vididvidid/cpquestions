/*
 * File: 1950D.c
 * Author: vididvidid 
 * Created: 2026-06-19 18:08:32
 */

/*
 * find if the number can be represented in the product form of some binary
 * decimal number.. i.e the the product of a.b leads to x and a and b only
 * contains 1 or 0 in it..
 *
 *
 * 1 
 * 10
 * 11
 * 111
 * 110
 * 101
 * 1 -> 10 -> 11 -> 100 -> 101 -> 110 -> 111 -> 10000 -> 1001 -> 1010 -> ...
 *
 * 50000
 * 11111
 * 1 + 2 + 4 + 8 + 16  = 31
 */

#include <stdio.h>
#include <math.h>

#define int long long

int d2b(int n)
{
    if (n == 0) return 0;

    long long ans = 0;
    int powr = 1;

    while (n > 0) 
    {
        int bit = n % 2;
        ans += bit * powr;
        n /= 2;
        powr *= 10;
    }

    return ans;
}

void solve()
{

    int n;
    scanf("%lld",&n);
    int i;
    int fg = 0;
    int t = n;
    while (t > 0)
    {
        int c = t % 10;
        if (c != 1 && c != 0)
        {
            fg = 1;
            break;
        }
        t /= 10;
    }
    if (fg)
    {
        while (n > 1)
        {
            for (i = 2; i < 32; i++)
            {
                int b = d2b(i);
                if (n % b == 0)
                {
                    /* printf("%lld ",i); */
                    n /= b;
                    break;
                }
            }
            if (i >= 32)
            {
                printf("NO\n");
                return;
            }
            /* printf("%lld ",n); */
        }
    }
    printf("YES\n");
    return;
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--){
        solve();
    }
}

