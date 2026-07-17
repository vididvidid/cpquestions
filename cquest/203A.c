/*
 * File: 203A.c
 * Author: vididvidid 
 * Created: 2026-07-17 21:42:43
 */

/*
 * x points  -> first contest
 * constest -> t minutes -> 2 question only 
 *      1st problem : a points -> every minutes reduce by da points. 
 *      2nd problem : b points -> every minutes reduce by db points.
 */
#include <stdio.h>

void solve()
{
    int x, t, a, b, da, db;
    scanf("%d %d %d %d %d %d", &x, &t, &a, &b, &da, &db);

    if (x == 0)
    {
        printf("YES\n");
        return;
    }

    for (int i = 0; i < t; i++)
    {
        if (a - i * da == x)
        {
            printf("YES\n");
            return;
        }
    }

    for (int i = 0; i < t; i++)
    {
        if (b - i * db == x) {
            printf("YES\n");
            return;
        }
    }

    for (int i = 0; i < t; i++)
    {
        for (int j = 0; j < t; j++)
        {
            if ((a-i * da) + (b - j * db) == x) {
                printf("YES\n");
                return;
            }
        }
    }

    printf("NO\n");
}

int main()
{
    solve();
    return 0;
}
