/*
 * File: 9C.c
 * Author: vididvidid 
 * Created: 2026-07-18 13:44:23
 */

/*
 * find number that contain only 1 and 0 from range [1, n];
 *
 * n < 10^9
 */
#include <stdio.h>

#define int long long

int q[2048];

void solve()
{
     int n;
     scanf("%lld", &n);

     int head = 0, tail = 0;
     q[tail++] = 1;

     while (q[head] <= n)
     {
         q[tail++] = q[head] * 10;
         q[tail++] = q[head] * 10 + 1;
         head++;
     }

     printf("%lld\n", head);
}

signed main()
{
    solve();
    return 0;
}
