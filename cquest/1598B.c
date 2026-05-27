/*
 * File: 1598B.c
 * Author: vididvidid 
 * Created: 2026-05-27 11:31:41
 */

/*
 * count if we can divide student in two groups to separtely study in different
 * days 
 *
 * cases:
 * for all days if its greater than 2 than we can divide it.. 
 * >2 >2 >2 >2 >2
 *
 * if its >2 >2 >2 >2 1 than false 
 * if its >2 >2 >2  1 1 true
 *
 * 1 2 0 3 1
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);

    int arr[n][5];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            int ci = 0, cj = 0, cn = 0;

            for (int k = 0; k < n; k++)
            {
                if (arr[k][i] == 1) ci++;
                if (arr[k][j] == 1) cj++;
                if (arr[k][i] == 0 && arr[k][j] == 0) cn++;
            }

            if (cn > 0) continue;
            if (ci >= n/2 && cj >= n/2) {
                printf("YES\n");
                return;
            }
        }
    }

    printf("NO\n");
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
