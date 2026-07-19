/*
 * File: 1055A.c
 * Author: vididvidid 
 * Created: 2026-07-19 17:33:54
 */

/*
 * bob wants to travel from station 1 to station s out of n total metro station
 * the metro system has two directional tracks:
 * track1: moves forward from station 1 to n. Station i is accessible if ai = 1
 * track2: moves backward from station n to 1. station i is accessible if bi =1
 * determine if bob can reach station s starting from station 1.
 *
 * n <=1000
 */

#include <stdio.h>

void solve()
{
    int n, s;
    scanf("%d %d", &n ,&s);
    int a[1005], b[1005];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &b[i]);
    }

    if (a[1] == 0)
    {
        printf("NO\n");
        return;
    }

    if (a[s] == 1)
    {
        printf("YES\n");
        return;
    }

    if (b[s] == 1) 
    {
        for (int k = s + 1; k <= n; k++)
        {
            if (a[k] == 1 && b[k] == 1) 
            {
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
