/*
 * File: T1666.c
 * Author: vididvidid 
 * Created: 2026-08-08 19:50:03
 */

/*
 * Connecting component.. 
 *
 * Solving by Adjacency matrix.. 
 * n cities, m roads..
 *
 * n x m => matrix.. 
 * testcase:
 * 4 2
 * 1 2
 * 3 4
 *
 * 1 -> 2
 * 3 -> 4
 *
 * so matrix looks like this.. 
 *
 * 0 1 2 3 4  0 1 2 3 4
 * 1 0 0 0 0  1 0 1 0 0
 * 2 0 0 0 0  2 1 0 0 0
 * 3 0 0 0 0  3 0 0 0 1
 * 4 0 0 0 0  4 0 0 1 0
 *
 * So to find the number of connected components..
 * 1. we need to have something that checks if node is visited or not..
 * 2. whenever node is not visited that is some new component
 * 3. so we have to iterate over all the nodes and check if its visited or not
 * 4. if its not visited do dfs on that node and increase the number of
 * component by 1
 *
 * dfs looks like this..
 * dfs(node)
 *  make the node visited
 *  loop over all nodes
 *      find the neighbour of this node 
 *      check if its visited or not -> if not visited call the dfs
 *
 * 2. Adjaceny list
 * because MAXNODE 100005 x 100005 make 40Gb file which is not good
 * we will use adjaceny list
 *
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void solve_list()
{
    const int MAXNODE = 100005;

    struct Node {
        int vertex;
        struct Node* next;
    }
}

void solve_matrix()
{
    const int MAXNODE = 100;    
    int adj[MAXNODE][MAXNODE];
    int visited[MAXNODE];
    int newCompStart[MAXNODE];
    int num_nodes;

    void dfs(int node)
    {
        visited[node] = 1;

        for (int i = 0; i < num_nodes; i++)
        {
            if (adj[node][i] == 1 && !visited[i]) 
            {
                dfs(i);
            }
        }
    }

    memset(adj, 0, sizeof(adj));
    memset(visited, 0, sizeof(visited));
    memset(newCompStart, 0, sizeof(newCompStart));

    int  m;
    scanf("%d %d", &num_nodes, &m);

    for (int i = 0; i < m; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);
        adj[x - 1][y - 1] = 1;
        adj[y - 1][x - 1] = 1;
    }

    int ans = 0;
    int idx = 0;

    for (int i = 0; i < num_nodes; i++)
    {
        if (!visited[i])
        {
            ans++;
            newCompStart[idx++] = i + 1;
            dfs(i);
        }
    }

    printf("%d\n",ans - 1);
    for (int i = 1; i < ans; i++)
    {
        printf("%d %d\n", newCompStart[i - 1], newCompStart[i]);
    }
}

signed main()
{
    solve_list();
    return 0;
}
