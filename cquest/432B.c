/*
 * File: 432B.c
 * Author: vididvidid 
 * Created: 2026-07-17 14:56:54
 */

/*
 * n teams -> each team -> 2 football kit : for home and for international
 * kit-> home games -> ith team -> color xi
 *    -> away games -> ith team -> color yi  (xi != yi)
 * n * (n - 1) games -> each team play -> one home game and one away game
 * but if two teams kits -> same color -> plays in away kit
 * calculate how many games in home kit and away kit?
 *
 * n,x,y <= 10^5 => O(n) 
 *
 * -----------------------------------------------------------------------
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);

    int x[n], y[n];
    int freq[100001] = {0};

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x[i], &y[i]);
        freq[x[i]]++;
    }

    for (int i = 0; i < n; i++)
    {
        int h = (n - 1) + freq[y[i]];
        int a = (n - 1) - freq[y[i]];
        printf("%d %d\n",h, a);
    }

}

int main()
{
    solve();
    return 0;
}
