/*
 * File: 1728A.c
 * Author: vididvidid 
 * Created: 2026-04-24 02:15:05
 */

/*
 * there is the array with frequency of each index.. determine..
 * if we remove the two pairs different what index will be left at the end..
 *
 * return the max num i think
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n+1];
    int max = INT_MIN,ans=-1;
    for (int i = 1; i <= n; i++) {
        scanf("%d",&arr[i]);
        int t = max;
        max = MAX(max,arr[i]);
        if (t != max)
        {
            ans = i;
        }
    }
    printf("%d\n",ans);
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
