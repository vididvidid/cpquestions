/*
 * File: 580A.c
 * Author: vididvidid 
 * Created: 2026-05-13 06:51:47
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    int n;
    scanf("%d",&n);
    long long arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&arr[i]);
    }
    int ans = INT_MIN;
    int sl = 1;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] >= arr[i-1]) sl++;
        else {
            ans = MAX(ans,sl);
            sl = 1;
        }
    }
    ans = MAX(ans,sl);
    printf("%d\n",ans);
    return 0;
}
