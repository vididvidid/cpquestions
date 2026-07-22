/*
 * File: 1327B.c
 * Author: vididvidid 
 * Created: 2026-07-22 20:26:41
 */

/*
 * There are N daughters and N kingdomws. Each daugther has a list of
 * preferred kingdoms.
 * Matching is greedy: going in order from daughter 1 to N, each 
 * daughter marries the first available kingdom on her list
 * you want to find it if adding exactly one kingdom to one daughter's
 * list can increase the total number of marriages.
 * if possible, print "IMPROVE" and the (daughter, kingdom) pair. If
 * everyone is already matched, print "OPTIMAL'"
 */
#include <stdio.h>
#include <string.h>

#define MAXN 100005

int dm[MAXN];
int kt[MAXN];

void solve()
{
    int n;
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) 
    {
        dm[i] = 0;
        kt[i] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        int k;
        scanf("%d", &k);
        for (int j = 0; j < k; j++)
        {
            int g;
            scanf("%d", &g);

            if (!dm[i] && !kt[g]) 
            {
                dm[i] = 1;
                kt[g] = 1;
            }
        }
    }

    int ud = -1;
    int uk = -1;

    for (int i = 1; i <= n; i++)
    {
        if (!dm[i])
        {
            ud = i;
            break;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        if (!kt[i])
        {
            uk = i;
            break;
        }
    }

    if (ud != -1 && uk != -1)
    {
        printf("IMPROVE\n%d %d\n", ud, uk);
    }
    else
    {
        printf("OPTIMAL\n");
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
