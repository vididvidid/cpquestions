/*
 * File: 796A.c
 * Author: vididvidid 
 * Created: 2026-04-28 13:08:01
 */

/*
 * find the minimum distance from the house x with the cost y he have..
 *
 * modify the array of houses.. with -1 which can not be bought..
 * and where he can bought replace it with i-x and return the smallest number
 */

#include <stdio.h>
#include <limits.h>

#define ABS(a) (a)<0?-1*(a):(a)
#define MIN(a,b) (a)<(b)?(a):(b)

int main()
{
    int n,m,k;
    scanf("%d %d %d",&n,&m,&k);
    int arr[n+1];
    for (int i = 1; i <= n ; i++)
    {
        scanf("%d",&arr[i]);
        if (arr[i] == 0 || arr[i] > k || i == m) arr[i] = -1;
        else arr[i] = ABS(i-m);
    }

    int ans = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        if (arr[i] != -1)
        {
            ans = MIN(ans,arr[i]);
        }
    }

    printf("%d\n",ans*10);
    
}
