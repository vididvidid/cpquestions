/*
 * File: 1176A.c
 * Author: vididvidid 
 * Created: 2026-04-26 04:29:41
 */

#include <stdio.h>

#define int unsigned long long

void solve()
{
    int n;
    scanf("%llu",&n);
    int flag = 1, count = 0 ;
    while ( n > 1)
    {
        while (n % 5 == 0) {
            n /= 5;
            n *= 4;
            flag = 0;
            count++;
        }
        while (n % 3 == 0) {
            n /= 3;
            n *= 2;
            flag = 0;
            count++;
        }
        while (n % 2 == 0) {
            n /= 2;
            flag = 0;
            count++;
        }
        if (n%2 != 0 || n%3 != 0 || n%5 != 0) {
            break;
        }
    }
    if (n == 1)
    printf("%llu\n",count);
    else
    printf("-1\n");
}

signed  main()
{
    int t;
    scanf("%llu",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
