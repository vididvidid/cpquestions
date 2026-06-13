/*
 * File: 2137C.c
 * Author: vididvidid 
 * Created: 2026-06-13 18:23:30
 */

#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define int long long

void solve()
{
    int a, b;
    scanf("%lld %lld", &a, &b);
    
    int pa = 0, pb = 0;
    int ta = a, tb = b;

    while (ta % 2 == 0){
        pa++;
        ta /= 2;
    }

    while (tb % 2 == 0)
    {
        pb++;
        tb /= 2;
    }

    int ob = tb;

    int minp, maxp;

    if (pa == 0 && pb == 0) {
        minp = 0;
        maxp = 0;
    }
    else
    {
        minp = (pa == 0) ? 1 : 0;
        maxp = pb - 1;
    }

    if (minp > maxp)
    {
        printf("-1\n");
        return;
    }

    int kmin = 1;
    for (int i = 0; i < minp; i++)
    {
        kmin *= 2;
    }

    int kmax = ob;
    for (int i = 0; i < maxp; i++)
    {
        kmax *= 2;
    }

    int ans1 = a * kmin + b/kmin;
    int ans2 = a * kmax + b/kmax;

    if (ans1 > ans2){
        printf("%lld\n",ans1);
    }
    else
    {
        printf("%lld\n",ans2);
    }
}
int main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
