/*
 * File: 289A.c
 * Author: vididvidid 
 * Created: 2026-07-07 20:10:30
 */

#include <stdio.h>

void solve()
{
    int n, k;
    scanf("%d %d",&n, &k);
    int cnt = 0;
    int arr[n][2];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &arr[i][0], &arr[i][1]);
        cnt += (arr[i][1] - arr[i][0] + 1);
    }

    if (cnt % k == 0)
    {
        printf("0\n");
    }
    else {
        int a = cnt % k;
        int ans = (k - a) % k;
        printf("%d\n", ans);
    }
}

int main()
{
    solve();
    return 0;
}
