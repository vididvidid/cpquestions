/*
 * File: 914A.c
 * Author: vididvidid 
 * Created: 2026-05-12 09:38:56
 */

#include <stdio.h>
#include <limits.h>
#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    long long arr[1001];
    for (int i = 1; i < 1001; i++)
    {
        arr[i] = i * i;
    }
    long long ans = INT_MIN;
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d",&k);
        int flag = 0;
        for (int j = 0; j < 1001; j++)
        {
            if (k == arr[j]) flag = 1;
        }
        /* printf("flag:%d k:%d\n",flag,k); */
        if (flag == 0)
        {
            ans = MAX(ans, k);
        }
    }
    printf("%lld\n",ans);
    return 0;
}
