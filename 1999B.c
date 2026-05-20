/*
 * File: 1999B.c
 * Author: vididvidid 
 * Created: 2026-05-18 12:12:48
 */

#include <stdio.h>

int helper(int s1, int sl1, int s2, int sl2)
{
    int score1 = 0;
    int score2 = 0;

    if (s1 > sl1) score1++;
    else if (s1 < sl1) score2++;

    if (s2 > sl2) score1++;
    else if (s2 < sl2) score2++;

    return score1 > score2 ? 1: 0;
}

void solve()
{
    int a1, a2, b1, b2;
    scanf("%d %d %d %d",&a1, &a2, &b1, &b2);
    int ans = 0;
    ans += helper(a1,b1,a2,b2);
    ans += helper(a1,b2,a2,b1);
    ans += helper(a2,b1,a1,b2);
    ans += helper(a2,b2,a1,b1);
    printf("%d\n",ans);
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
