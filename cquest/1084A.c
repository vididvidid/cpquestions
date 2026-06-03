/*
 * File: 1084A.c
 * Author: vididvidid 
 * Created: 2026-06-03 07:40:25
 */

/*
 * find the min elec it will take for lift to take passenger a from ith position 
 * to leave at 1st floor and 1st floor to ith position and everytime time lift
 * defaults to xth floor.. 
 *
 * 2 * (|x - i| + |i - 1| + |x - 1|) * number of passenger
 *
 */
#include <stdio.h>
#include <limits.h>

#define MOD(a) (a)<0?-1*(a):(a)
#define MIN(a,b) (a)<(b)?(a):(b)

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d",&arr[i]);
    }

    int ans = INT_MAX;
    for (int x = 1; x <= n; x++)
    {
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            int x2i = MOD(x - i);
            int i21 = MOD(i - 1);
            int x21 = MOD(x - 1);
            int tans = 2 * (x2i + i21 + x21);
            int cost = arr[i]  * tans;
            sum += cost;
            /* printf("\tDEBUG: %d,%d: %d %d %d\n",i, x, x2i,i21,x21); */
            /* printf("\tDEBUG: %d,%d: %d * %d = %d\n",i, x, tans, arr[i], cost); */
        }         

        /* printf("DEBUG: sum = %d\n",sum); */
        /* printf("--------------------------------\n"); */
        ans = MIN(ans, sum);
    }

    printf("%d\n",ans);
}
