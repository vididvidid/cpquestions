/*
 * File: 1743A.c
 * Author: vididvidid 
 * Created: 2026-04-23 08:14:13
 */

/*
 * choose from the digits.. 
 * total digits we have after we remove the ones (M)
 * total digits we have to choose is 2
 * so calculate MC2 than multipy it by the 6 
 *
 * 10! / (n-1)! * (n!)
 *
 * factorial = 5! => 1 * 2 * 3 * 4 * 5
 *
 */

#include <stdio.h>

#define int long long

int fact(int n)
{
    int ans = 1;
    for (int i = 1; i <= n; i++) ans *= i;
    return ans;
}

int comb(int m, int v)
{
    int num = fact(m);
    int den1 = fact(m-v);
    int den2 = fact(v);
    int den = den1 * den2;
    int ans = num / den;
    /* printf("Comb of %lld C %lld is %lld \n",m,v,ans); */
    /* printf("num: %lld den1: %lld den2: %lld den: %lld \n",\ */
    /*         num,den1,den2,den); */
    return ans;

}

void solve()
{
    int k;
    scanf("%lld",&k);
    int arr[k];
    for (int i = 0; i < k; i++) scanf("%lld", &arr[i]);

    int rel = 10 - k;
    int ans = comb(rel,2) * 6;
    printf("%lld\n",ans);
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
