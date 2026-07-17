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

int arr[200005], prr[200005];

void solve()
{
    int n;
    scanf("%lld", &n);
    int sum = 0;
    for(int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
        sum += arr[i];
    }
    int cn = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] * n == sum)
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
