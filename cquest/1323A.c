/*
 * File: 1323A.c
 * Author: vididvidid 
 * Created: 2026-04-25 12:31:43
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int idx1 = 0, idx2 = 0,edx = 0, flag = 1;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
        if (arr[i]%2 == 0){
            flag = 0;
            edx = i;
        }
        if (!idx1 && arr[i]%2 != 0) idx1 = i;
        if (!idx2 && idx1 && idx1 != i && arr[i]%2 != 0) idx2 = i;
    }
    if (n == 1) {
        if (arr[0] %2 == 0)
        {
            printf("1\n1\n");
            return;
        } else {
            printf("-1\n");
            return;
        }
    }
    if (!flag) {
        printf("1\n%d\n",edx+1);
    } else {
        printf("2\n");
        printf("%d %d\n",idx1+1, idx2+1);
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
