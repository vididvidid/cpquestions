/*
 * File: 463B.c
 * Author: vididvidid 
 * Created: 2026-07-09 14:38:41
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int e = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            e += (0 - arr[i]);
        }
        else
        {
            e += (arr[i - 1] - arr[i]);
        }

        if (e < 0)
        {
            ans += -e;
            e = 0;
        }
    }

    printf("%d\n",ans);
}

int main()
{
    solve();
    return 0;
}
