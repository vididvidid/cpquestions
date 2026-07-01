/*
 * File: 919B.c
 * Author: vididvidid 
 * Created: 2026-07-01 18:29:43
 */

#include <stdio.h>

#define int unsigned long long
int arr[10001];
int idx = 0;

void solve()
{
    int n;
    scanf("%llu", &n);

    n--;
    for (int i = 0; i < idx; i++)
    {
        if (n == i){
            printf("%llu\n",arr[i]);
            break;
        }
    }

    printf("\n");
}

signed main()
{
    int i = 19;
    while (idx < 10001)
    {
        int t = i;
        int sum = 0;
        while (t >= 1)
        {
            sum += (t % 10);
            t /= 10;
        }

        if (sum == 10)
        {
            arr[idx++] = i;
        }
        i++;
    }

    solve();
    return 0;
}
