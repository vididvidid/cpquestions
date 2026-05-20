/*
 * File: 888A.c
 * Author: vididvidid 
 * Created: 2026-04-29 08:11:25
 */

/* count the number of minimum and max points in the array 
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int ans = 0;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

    for (int i = 1; i < n-1; i++)
    {
        if ((arr[i] > arr[i-1] && arr[i] > arr[i+1]) ||
            (arr[i] < arr[i-1] && arr[i] < arr[i+1]))
        {
            ans++;
        }
    }

    printf("%d\n",ans);
    return 0;
}
