/*
 * File: 129B.c
 * Author: vididvidid 
 * Created: 2026-07-19 12:59:40
 */

/*
 * you are given undirected graph representing students and their 
 * connections.
 * in each round, you must perform the following:
 * 1. find all nodes that currently have exactly 1 connections (deg 1)
 * 2. if there are no such nodes, stop the process
 * 3. if there are such nodes, remove all of them simultaneously, 
 * along with the edges attached to them. This counts as 1 round 
 * (one group kicked out)
 *
 */
#include <stdio.h>
#include <string.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int adj[105][105] = {0};
    int deg[105] = {0};

    for (int i = 0; i < m; i++)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
        adj[v][u] = 1;
        deg[u]++;
        deg[v]++;
    }

    int rounds = 0;

    while (1)
    {
        int to_remove[105];
        int count = 0;

        for (int i = 1; i <= n; i++)
        {
            if (deg[i] == 1)
            {
                to_remove[count++] = i;
            }
        }

        if (count == 0)
        {
            break;
        }

        rounds++;

        for (int i = 0; i < count; i++)
        {
            int u = to_remove[i];
            deg[u] = 0;

            for (int v = 1; v <= n; v++)
            {
                if (adj[u][v])
                {
                    adj[u][v] = 0;
                    adj[v][u] = 0;
                    deg[v]--;
                }
            }
        }
    }

    printf("%d\n", rounds);
}

int main()
{
    solve();
    return 0;
}
