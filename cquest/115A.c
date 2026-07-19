/*
 * File: 115A.c
 * Author: vididvidid 
 * Created: 2026-07-19 17:10:44
 */

/*
 * n employees [1,n] numbered
 * each employee -> 1 manager or not
 * eA is superior to eb:
 * 1. if immediate manager
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);

    int manager[2005];
    for (int i = 1; i <=n; i++)
    {
        scanf("%d", &manager[i]);
    }

    int max_depth = 0;

    for (int i = 1; i <= n; i++)
    {
        int depth = 1;
        int curr = i;

        while (manager[curr] != -1)
        {
            depth++;
            curr = manager[curr];
        }

        if (depth > max_depth)
        {
            max_depth = depth;
        }
    }

    printf("%d\n", max_depth);
}

int main()
{
    solve();
    return 0;
}
