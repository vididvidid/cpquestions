/*
 * File: 1244B.c
 * Author: vididvidid 
 * Created: 2026-06-02 16:41:15
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d",&n);
    char s[1001];
    scanf("%s",&s[1]);

    int ans = n;
    for (int i = 1; i <= n; i++)
    {
        if (s[i] == '1')
        {
            int tmp = MAX(2 * i , 2 * (n - i + 1));
            ans = MAX(ans, tmp);
        }
    }

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
