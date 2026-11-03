/*
 * File: 919C.c
 * Author: vididvidid 
 * Created: 2026-11-03 05:15:38
 */

/*
 * find the consecutive '.' and check how many are >= k and count the ways.
 *
 */

#include <stdio.h>

#define N 2000
char grid[N][N];

void solve()
{
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);

    for (int i = 0; i < n; i++)
    {
        scanf("%s", grid[i]);
    }

    long long ans = 0;

    for (int i = 0; i < n; i++)
    {
        int cd = 0;
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == '.')
            {
                cd++;
                if (cd >= k)
                {
                    ans++;
                }
            }
            else
            {
                cd = 0;
            }
        }
    }

    if (k > 1)
    {
        for (int j = 0; j < m; j++)
        {
            int cd = 0;
            for (int i = 0; i < n; i++)
            {
                if (grid[i][j] == '.')
                {
                    cd++;
                    if (cd >= k)
                    {
                        ans++;
                    }
                }
                else
                {
                    cd = 0;
                }
            }
        }
    }

    printf("%lld\n",ans);
}

int main()
{
    solve();

    return 0;
}
