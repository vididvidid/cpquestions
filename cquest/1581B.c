/*
 * File: 1581B.c
 * Author: vididvidid 
 * Created: 2026-07-21 19:39:06
 */

/*
 * undirected graph with n nodes and m edges
 * diameter of graph must be less than k - 1
 * graph don't contain self-loops or multiple edges
 * diameter of graph is max distance between any two nodes
 * distance b/w two nodes -> mininum number of edges at that path
 *
 * 1. a connected simple graph must have between (n-1) and 
 * n * (n + 1) / 2 edges
 *
 * 2. a single node has a diameter of exactly 0
 * 3. A complete graph has a diameter of exactly 1
 * 4. Any other valid connected graph can be built as a star graph 
 * with a diameter of exactly 2
 *
 */
#include <stdio.h>

void solve()
{
    long long n, m, k;
    scanf("%lld %lld %lld", &n, &m, &k);

    long long max_edges = n * ( n - 1 ) / 2;

    if ( m < n - 1 || m > max_edges )
    {
        printf("NO\n");
        return;
    }

    if (n == 1)
    {
        if (k > 1) printf("YES\n");
        else printf("NO\n");
        return;
    }

    if (m == max_edges)
    {
        if (k > 2) printf("YES\n");
        else printf("NO\n");
        return;
    }

    if (k > 3)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

}

int main()
{
    int t;
    scanf("%d", &t );
    while (t--)
    {
        solve();
    }

    return 0;
}
