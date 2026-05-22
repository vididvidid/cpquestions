/*
 * File: 1790C.c
 * Author: vididvidid 
 * Created: 2026-05-22 15:23:59
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n + 1][n + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            arr[i][j] = 0;
        }
    }

    int ln = n;
    while (ln--)
    {
        for (int i = 0; i < n - 1; i++)
        {
            int k;
            scanf("%d",&k);
            arr[i][k]++;
        }
    }

    /* for (int i = 0; i <= n; i++) */
    /* { */
    /*     for (int j = 0; j <= n; j++) */
    /*     { */
    /*         printf("%d ",arr[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
    int ans[n];
    for (int x = 1; x <= n; x++)
    {
        int sum = 0;
        for (int i = 0; i < n - 1; i++)
        {
            sum += i * arr[i][x];
        }
        int pos = sum / (n - 2);
        ans[pos] = x;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ",ans[i]);
    }
    printf("\n");
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
