/*
 * File: 134A.c
 * Author: vididvidid 
 * Created: 2026-07-18 00:26:30
 */

/*
 * print the indices whose value is the mean of the whole array (exclude the
 * current indice)
 */
#include <stdio.h>

#define int long long

void solve()
{
    int n;
    scanf("%lld", &n);
    int sum = 0;
    int arr[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
        sum += arr[i];
    }
    int cn = 0, prr[n];
    for (int i = 0; i < n; i++)
    {
        int tsum = sum - arr[i];
        tsum /= (n - 1);
        if (tsum == arr[i])
        {
            prr[cn++] = i;
        }
    }
    printf("%lld\n",cn);
    for (int i = 0; i < cn; i++)
    {
        printf("%lld ",prr[i] + 1);
    }
    printf("\n");
}

signed main()
{
    solve();
    return 0;
}
