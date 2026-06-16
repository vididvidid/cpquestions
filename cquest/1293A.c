/*
 * File: 1293A.c
 * Author: vididvidid 
 * Created: 2026-06-16 22:25:02
 */

#include <stdio.h>
#include <stdbool.h>

void solve()
{
    int n, s, k;
    scanf("%d %d %d", &n, &s, &k);
    
    int close[1005];
    for (int i = 0; i < k; i++)
    {
        scanf("%d", &close[i]);
    }

    for (int d = 0; d <= k; d++)
    {
        if (s - d >= 1)
        {
            bool is_close = false;
            for (int i = 0; i < k; i++)
            {
                if (close[i] == s - d)
                {
                    is_close = true;
                    break;
                }
            }

            if (!is_close)
            {
                printf("%d\n",d);
                return;
            }
        }

        if (s + d <= n)
        {
            bool is_close = false;
            for (int i = 0; i < k; i++)
            {
                if (close[i]  == s + d)
                {
                    is_close = true;
                    break;
                }
            }

            if (!is_close)
            {
                printf("%d\n", d);
                return;
            }
        }
    }
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
