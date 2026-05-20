/*
 * File: 1391B.c
 * Author: vididvidid 
 * Created: 2026-05-06 03:25:10
 */

#include <stdio.h>

void solve()
{
    int n, m;
    scanf("%d %d",&n, &m);
    char s[n][m];
    for (int i = 0; i < n; i++)
    {
        scanf("%s",s[i]);
    }

    int rm = 0, bm = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i][m-1] == 'R') rm++;
    }

    for (int i = 0; i < m; i++)
    {
        if (s[n-1][i] == 'D') bm++;
    }

    printf("%d\n",rm+bm);
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
