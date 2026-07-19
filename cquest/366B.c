/*
 * File: 366B.c
 * Author: vididvidid 
 * Created: 2026-07-19 11:55:56
 */

/*
 * you are given an array of n numbers. you need to choose a starting index from
 * 1 to k such that is you jump forward by k steps repeatedly (wrapping aroudn
 * to the beginning when you reach the end), the sum of all numbers you land on
 * is as small as possible.
 */

#include <stdio.h>
#include <stdlib.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int *sum = (int *)calloc(k, sizeof(int));
    if (!sum) return;

    for (int i = 0; i < n; i++)
    {
        int power;
        scanf("%d", &power);
        sum[i % k] += power;
    }

    int mn = sum[0];
    int bt = 1;

    for (int i = 1; i < k; i++)
    {
        if (sum[i] < mn)
        {
            mn = sum[i];
            bt = i + 1;
        }
    }

    printf("%d\n", bt);
    free(sum);
}

int main()
{
    solve();
    return 0;
}
