/*
 * File: 218A.c
 * Author: vididvidid 
 * Created: 2026-07-07 21:34:04
 */

#include <stdio.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int N = 2 * n + 1;
    int arr[N + 2];
    for (int i = 1; i < N + 1; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i < N + 1; i++)
    {
        if (i % 2 == 0 && k > 0)
        {
            if ( (arr[i] > (arr[i - 1] + 1)) && (arr[i] > (arr[i + 1] + 1))) {
                arr[i]--;
                k--;
            } 
        }
    }

    for (int i = 1; i < N + 1; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main()
{
    solve();
    return 0;
}
