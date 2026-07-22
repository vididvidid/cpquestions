/*
 * File: 1255B.c
 * Author: vididvidid 
 * Created: 2026-07-22 23:02:35
 */

/*
 * Every fridge must be connected to at least 2 chains; if a fridge
 * has only 1 chain, the person on the other end cna open it alone.
 * 
 * To give all n fridges a degree of at least 2, you need at least
 * n chains ( m >= n ) and at least 3 fridges (n >= 3); otherwise,
 * it is impossible and you should print -1
 *
 * Since the problem constraints specify m <= n, the only valid case
 * is m == n, where the optimal configuration is connecting all 
 * fridges in a simple cirlce (1 - 2, 2 - 3,.. , n- 1);
 *
 * each fridge's weight is counted twice in a cirlce, making the 
 * minimum cost 2 x sum of ai.
 *
 */
#include <stdio.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n ,&m);

    int sum = 0;
    for (int i = 1; i <= n; i++)
    {
        int a;
        scanf("%d", &a);
        sum += a;

    }

    if (n <= 2 || m < n)
    {
        printf("-1\n");
        return;
    }        

    printf("%d\n", 2 * sum);

    for (int i = 1; i < n; i++)
    {
        printf("%d %d\n", i, i + 1);
    }

    printf("%d 1\n", n);
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
