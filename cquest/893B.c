/*
 * File: 893B.c
 * Author: vididvidid 
 * Created: 2026-06-03 09:12:26
 */

#include <stdio.h>
#include <limits.h>

#define int long long
#define MAX(a,b) (a)>(b)?(a):(b)

int trr[28], srr[28];

void solve()
{
    for (int i = 0; i < 28; i++)
    {
        if (i == 0) trr[i] = 1;
        else trr[i] = 2 * trr[i - 1];
    }
    /* for (int i = 0; i < 28; i++) */
    /* { */
    /*     printf("%lld ",trr[i]); */
    /* } */
    /* printf("\n"); */

    srr[0] = trr[0];
    for (int i =  1; i < 28; i++)
    {
        srr[i] = srr[i - 1] + trr[i];
    }
    /* for (int i = 0; i < 28; i++) */
    /* { */
    /*     printf("%lld ",srr[i]); */
    /* } */
    /* printf("\n"); */
    
    int n;
    scanf("%lld",&n);
    
    int ans = 1;
    for (int i = 0; i < 28; i++)
    {
        int val = srr[i+i] - srr[i - 1];
        if (n % val == 0)
        {
            ans = MAX(ans, val);
        }
    }

    printf("%lld\n",ans);
}

signed main()
{
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}
