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
    int freq[200004] = {0};
    int cn = 0;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            freq[arr[i] + arr[j]]++;
        }
    }
    
    for (int i = 0; i < 200004; i++)
    {
        cn = MAX(cn, freq[i]);
    }
    printf("%d\n",cn );
}

int main()
{
    solve();
    return 0;
}
