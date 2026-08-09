/*
 * File: T1669.c
 * Author: vididvidid 
 * Created: 2026-08-09 07:39:37
 */

/*
 * Finding Cycles
 *
 */

#include <stdio.h>
#include <stdlib.h>

void solve_list()
{
    const int MAXNODE = 100005;
    struct Node{
        int val;
        struct Node* next;
    };

    struct Node* adj[MAXNODE];
    int visited[MAXNODE];
    int store[MAXNODE];
    int num_nodes, num_edges;

    void add_edge(int u, int v)
    {
        struct Node* nodeu = (struct Node*)malloc(sizeof(struct Node));
        nodeu->val = v;
        nodeu->next = adj[u];
        adj[u] = nodeu;

        struct Node* nodev = (struct Node*)malloc(sizeof(struct Node));
        nodev->val = u;
        nodev->next = adj[v];
        adj[v] = nodev;
    }

    int parent_map[MAXNODE];
    int cycle_start = -1;
    int cycle_end = -1;
    int idx = 0;
    int dfs(int node, int parent)
    {
        visited[node] = 1;
        parent_map[node] = parent;

        struct Node* temp = adj[node];
        while (temp != NULL)
        {
            int neighbor = temp->val;
            if (!visited[neighbor])
            {
                store[idx++] = neighbor + 1;
                if (dfs(neighbor, node)) {
                    return 1;
                }
            }

            else if (neighbor != parent)
            {
                cycle_start = neighbor;
                cycle_end = node;
                return 1;
            }

            temp = temp->next;
        }

        return 0;
    }

    scanf("%d %d", &num_nodes, &num_edges);
    for (int i = 0; i < num_nodes; i++)
    {
        adj[i] = NULL;
        visited[i] = 0;
    }

    for (int i = 0; i < num_edges; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        add_edge(x - 1, y - 1);
    }

    for (int i = 0; i < num_nodes; i++)
    {
        if (!visited[i])
        {
            if (dfs(i, i))
            {
                idx = 0;

                store[idx++] = cycle_start + 1;

                int curr = cycle_end;

                while (curr != cycle_start)
                {
                    store[idx++] = curr + 1;
                    curr = parent_map[curr];
                }

                store[idx++] = cycle_start + 1;

                printf("%d\n", idx);

                for (int j = 0; j < idx; j++)
                {
                    printf("%d ", store[j]);
                }

                printf("\n");
                return;
            }
        }
    }

    printf("IMPOSSIBLE");
    
}

signed main()
{
    solve_list();
    return 0;
}
