/*
 * File: 1766A.c
 * Author: vididvidid 
 * Created: 2026-04-14 09:20:54
 */

// count the numbers between range [1, n] in which only one positive digit is 
// there..
// [1,9] ==> there are 9 digits..
// [10,19] ==> only 1 digit (10)
// so after 9 there is only one time when one positiv digit appear is on 10th
// place..
// 100 => 100/10 + (if n > 9 +9)= 19
// 3 => 
//
#include <stdio.h>
#define int long long 

void solve()
{
    int n;
    scanf("%lld",&n);
    int count = 0;
    int t = 1;
    while (t <=n )
    {
        if (t < 10 ) t+=1;
        else if (t < 100) t += 10;
        else if (t < 1000) t += 100;
        else if (t < 10000) t += 1000;
        else if (t < 100000) t += 10000;
        else if (t < 1000000) t += 100000;
        else if (t < 10000000) t += 1000000;
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
