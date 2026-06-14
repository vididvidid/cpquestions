/*
 * File: 2111B.c
 * Author: vididvidid 
 * Created: 2026-06-14 12:41:10
 */

#include <stdio.h>

#define SWAP(a,b) do {int tmp = (a); (a) = (b); (b) = tmp;} while (0);

void solve()
{
    int n, m;
    scanf("%d %d",&n, &m);
    int f[n];
    f[0] = 1, f[1] = 2;
    for (int i = 2; i < n; i++)
    {
        f[i] = f[i - 1] + f[i - 2];
    }

    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        scanf("%d %d %d", &a , &b, &c);
        if (a > b) SWAP(a, b);
        if (a > c) SWAP(a, c);
        if (b > c) SWAP(b, c);
        int ans = a >= f[n - 1] && b >= f[n - 1] && c >= f[n - 1] + f[n - 2];
        if (ans)
        {
            printf("1");
        }
        else 
        {
            printf("0");
        }
    }
    printf("\n");
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}


