/*
 * File: 66B.c
 * Author: vididvidid 
 * Created: 2026-07-09 15:42:59
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);

    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    int ans = 1;

    for (int i = 0; i < n; i++)
    {
        int c = 1;

        for (int j = i - 1; j >= 0; j--)
        {
            if (a[j] <= a[j + 1])
                c++;
            else
                break;
        }

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] <= a[j - 1])
                c++;
            else
                break;
        }

        if (c > ans)
            ans = c;
    }

    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}
