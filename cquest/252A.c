/*
 * File: 252A.c
 * Author: vididvidid 
 * Created: 2026-06-11 14:02:58
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int ans = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int tans = arr[i];
            for (int k = i + 1; k <= j; k++)
            {
                tans ^= arr[k];
            }

            ans = MAX(tans, ans);
        }
    }
    
    printf("%d\n",ans);
    return 0;
}
