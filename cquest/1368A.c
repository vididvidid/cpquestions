/*
 * File: 1368A.c
 * Author: vididvidid 
 * Created: 2026-04-14 08:29:51
 */

// a += b ==> (a+b) += b ===> (a + b + b) += b we have to make till
// (a + b + b ....) == n
// in a how many times we add the b so that i equals to n
// like 5, 4, 100
// so here we did
// 1 => 4 += 5      9, 4
// 2 => 5 += 9      14, 9
// 3 => 9 += 14     23, 14
// 4 => 14 += 23    37, 23
// 5 => 23 += 37    60, 37
// 6 => 37 += 60    97, 60
// 7 => 60 += 97    157, 97
//
// while (a < 100 || b < 100) sum and keep the max value on right..
//
#include <stdio.h>
#define int unsigned long long
void solve()
{
    int a, b, n, count=0;
    scanf("%lld %lld %lld",&a, &b, &n);
    while ((a <= n+1 && b <= n+1))
    {
        if (a > n) break;
        if (b > n) break;
        if (a > b){
            b +=a ;
        }
        else{
            a +=b;
        }

        count++;
    }
    printf("%lld\n",count);
}

signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
