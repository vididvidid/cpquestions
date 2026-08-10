/*
 * File: T1668.c
 * Author: vididvidid 
 * Created: 2026-08-10 13:22:00
 */

/*
 * Bipartite Checking:
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXNODE 100005

struct Node 
{
    int vertex;
    struct Node* next;
};

struct Node* adj[MAXNODE];
int visited[MAXNODE];
int total_nodes = 0, total_edges = 0;

void initialize();
void add_edge();
void input();
bool dfs(int u, int current_color);
bool check_bipartite();

void solve()
{
    initialize();
    input();
    if(check_bipartite())
    {
        for (int i = 0; i < total_nodes; i++)
        {
            if (visited[i] == 0)
            {
                printf("1 ");
            }
            else
            {
                printf("2 ");
            }
        }
        printf("\n");
    }
    else
    {
        printf("IMPOSSIBLE\n");
    }
}

int main()
{
    solve();
    return 0;
}

void initialize()
{
    for (int i = 0; i < MAXNODE; i++)
    {
        adj[i] = NULL;
        visited[i] = -1;
    }
}

void add_edge(int u, int v)
{
    struct Node* addNodeu = (struct Node*)malloc(sizeof(struct Node));
    addNodeu->vertex = v;
    addNodeu->next = adj[u];
    adj[u] = addNodeu;

    struct Node* addNodev = (struct Node*)malloc(sizeof(struct Node));
    addNodev->vertex = u;
    addNodev->next = adj[v];
    adj[v] = addNodev;
}

void input()
{

    scanf("%d %d",&total_nodes, &total_edges);
    for (int i = 0; i < total_edges; i++)
    {
        int x, y;
        scanf("%d %d", &x, &y);

        add_edge(x - 1, y - 1);
    }

}

bool dfs(int u, int current_color)
{
    visited[u] = current_color;

    struct Node* temp = adj[u];
    while (temp != NULL)
    {
        int v = temp->vertex;

        if (visited[v] == -1)
        {
            if (!dfs(v, 1 - current_color))
            {
                return false;
            }
        }

        else if (visited[v] == current_color)
        {
            return false;
        }

        temp = temp->next;
    }

    return true;
}

bool check_bipartite()
{
    for (int i = 0; i < total_nodes; i++)
    {
        if (visited[i] == -1)
        {
            if (!dfs(i, 0))
            {
                return false;
            }
        }
    }

    return true;
}


