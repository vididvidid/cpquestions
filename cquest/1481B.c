/*
 * File: 1481B.c
 * Author: vididvidid 
 * Created: 2026-06-22 16:26:14
 */

/*
 * Given an array h of size n, simulate k operations where each position
 * increments the first h[i] that is strictly less than h[i + 1]; return the
 * index i on the k-th operation, or -1 if no such i exists".
 *
 *
 * i can't simulate 10^9 times.. 
 * n <= 100 , h[i] <= 100.. 
 * what is the absolute max number of times you can increment elmeents before
 * the array become flat/descending and everything falls off the edge?
 * if you have 100 elements, and the maximum height is 100, the array can only
 * absorb a maximum of 100x100= incrementes.. 
 *
 * so k > 10,000 return -1
 *
 */
#include <stdio.h>

void solve()
{
    int n;
    long long k;
    scanf("%d %lld", &n, &k);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }


    if (k > 10000) {
        printf("-1\n");
        return;
    }

    for (int i = 1; i <= k; i++)
    {
        int j;
        for (j = 0; j < n - 1; j++)
        {
            if (arr[j] < arr[j + 1]){
                arr[j]++;

                if (i == k)
                {
                    printf("%d\n",j + 1);
                    return;
                }

                break;
            }
        }
        if (j == n - 1)
        {
            printf("-1\n");
            return;
        }
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
