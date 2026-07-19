/*
 * File: 1944A.c
 * Author: vididvidid 
 * Created: 2026-07-19 15:21:38
 */

/*
 * there are n bridges and each bridges are connected with each other k bridges
 * are destroyed minimum number of bridegs that we can use to reach the island
 * every bridges is connected with each other..
 *
 * n = 5
 *
 * 1 -> {2, 3, 4, 5}
 * 2 -> {1, 2, 3, 4}
 * 3 -> {1 ,2 ,4 ,5}
 * 4 -> {1, 2, 3, 5}
 * 5 -> {1, 2, 3, 4}
 * 
 * every node is connected with n - 1 edges.. so which mean if k > n - 1
 * we can't reach any other node.. so if k < n- 1 that means we can reach all
 * the nodes.
 *
 */

#include <stdio.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n , &k);

    if (k >= n - 1)
    {
        printf("1\n");
    }
    else
    {
        printf("%d\n", n);
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
