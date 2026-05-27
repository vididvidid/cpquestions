/*
 * File: 1750B.c
 * Author: vididvidid 
 * Created: 2026-05-03 05:44:59
 */

#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define int unsigned long long

void solve()
{
    int n;
    scanf("%llu",&n);
    char s[n];
    int ones = 0, zeros = 0;
    int tone = 0, tzero = 0;
    int sum1 =0, sum0 = 0 ;
    for (int i = 0; i < n; i++)
    {
        scanf(" %c",&s[i]);
        if (s[i] == '1') tone++;
        else if (s[i] == '0') tzero++;

        if (s[i] == '1')
        {
            sum1++;
        }
        else {
            ones = MAX(ones,sum1);
            sum1 = 0;
        }

        if (s[i] == '0')
        {
            sum0++;
        }
        else {
            zeros = MAX(zeros, sum0);
            sum0 = 0;
        }
    }        
    if (sum0 != 0)
    {
        zeros = MAX(zeros,sum0);
        sum0 = 0;
    }
    if (sum1 != 0)
    {
        ones = MAX(ones, sum1);
        sum1 = 0;
    }
    /* printf("D: ones: %d zeros: %d tone: %d tzero: %d\n",ones,zeros,tone,tzero); */
    int xy = tone * tzero;
    int x2 = ones * ones;
    int y2 = zeros * zeros;
    int ans = MAX(xy, MAX(x2,y2));
    printf("%llu\n",ans);
}

signed main()
{
    int t;
    scanf("%llu",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
