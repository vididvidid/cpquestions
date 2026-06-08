/*
 * File: 385A.c
 * Author: vididvidid 
 * Created: 2026-06-08 14:31:17
 */

/*
 * get the biggest consequtive difference
 *
 */

#include <stdio.h>

int main()
{
    int n, m;
    scanf("%d %d",&n, &m);

    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

    int ans = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int diff = arr[i] - arr[i + 1];
        if (ans < diff)
        {
            ans = diff;
        }
    }

    if (ans == 0 || (ans - m) <= 0)
    {
        printf("0\n");
    }
    else
    {
        printf("%d\n",ans - m);
    }
}
