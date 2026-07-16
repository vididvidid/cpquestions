/*
 * File: 1121B.c
 * Author: vididvidid 
 * Created: 2026-07-16 16:48:14
 */

/*
 * find the number of pairs such that ai + aj = x, i != j in the array
 * n < 1000 so we can go O(n^2)
 * but ai < 10^5 which can fit in int
 *
 */

#include <stdio.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int cn = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int tcn = 0;
            int sum = arr[i] + arr[j];
            for (int p = 0; p < n; p++)
            {
                for (int q = p + 1; q < n; q++)
                {
                    if (p != i && p != j && q != i && q != j)
                    {
                        int tsum = arr[q] + arr[p];
                        if (tsum == sum)
                        {
                            tcn++;
                        }
                    }
                }
            }
            cn = MAX(cn, tcn);
        }
    }

    printf("%d\n",cn + 1);
}

int main()
{
    solve();
    return 0;
}
