/*
 * File: 1826A.c
 * Author: vididvidid 
 * Created: 2026-07-13 19:11:26
 */

/*
 *
 *
 * if all same and > 0 => -1
 * if all same and == 0 => 0
 * if all not same return minimum 
 *
 */

#include <stdio.h>

#define MIN(a,b) (a)<(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    int same = 0, mn = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        if (i > 0)
        {
            if (arr[i] == arr[i - 1])
            {
                same = 1;
            }
            else
            {
                same = 0;
            }
            mn = MIN(mn, arr[i]);
        }
        else
        {
            mn = arr[0];
        }
    }

    if (same || n == 1)
    {
        if (arr[0] == 0)
        {
            printf("0\n");
        }
        else
        {
            printf("-1\n");
        }
    }
    else
    {
        printf("%d\n",mn);
    }
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
