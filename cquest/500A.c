/*
 * File: 500A.c
 * Author: vididvidid 
 * Created: 2026-07-20 00:25:46
 */

/*
 * you are given n cells numbered from 1 to n, and a target cell t.
 * you start at cell 1. From any cell i (1 <= i <= n -1), there is 
 * one way portal that moves you directly to cell i + ai.
 *
 * Determine if it is possible to reach cell t starting from cell 1.
 *
 * n <= 3x10^4
 */

#include <stdio.h>

void solve()
{
    int n, t;
    scanf("%d %d", &n, &t);

    int a[30005];
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int curr = 1;
    while (curr < t) 
    {
        curr += a[curr];
    }

    if (curr == t) 
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

}

int main()
{
    solve();
    return 0;
}
