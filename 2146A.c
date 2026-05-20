/*
 * File: 2146A.c
 * Author: vididvidid 
 * Created: 2026-04-22 11:39:15
 */

/*
 * count the occurences of numbers in the array and return the minimum 
 * num such that all number have the same frequency 
 */

#include <stdio.h>
#include <limits.h>

#define MIN(a,b) (a)<(b) ? (a) : (b)
#define MAX(a,b) (a)>(b) ? (a) : (b)
void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n+1];
    for (int i = 0; i <= n; i++) arr[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int val;
        scanf("%d",&val);
        if (arr[val] == -1) {
            arr[val] = 0;
            arr[val]++;
        } else
        {
            arr[val]++;
        }
    }
    int mn = INT_MAX;
    int mx = INT_MIN;
    int cnt = 0;
    /* printf("---DEBUG---\n"); */
    /* for (int i = 1; i <=n; i++) */
    /*     printf("%d ",arr[i]); */
    /* printf("\n"); */
    for (int i = 1; i <= n; i++)
    {
        if (arr[i] != -1)
        {
            cnt++;
            mn = MIN(mn, arr[i]);
            mx = MAX(mx, arr[i]);
        }
    }
    /* printf("%d %d %d\n",mn,mx, cnt); */
    int ans = -1;
    for (int i = mx; i >= mn; i--)
    {
        int cn = 0;
        int tans = 0;
        for (int j = 1; j <= n; j++) 
        {
            if (arr[j] != -1)
            {
                if (arr[j] >= i) cn++;
            }
        }
        tans = cn * i;
        ans = MAX(ans, tans); 
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
