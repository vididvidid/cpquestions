/*
 * File: 1549B.c
 * Author: vididvidid 
 * Created: 2026-07-19 15:40:39
 */

/*
 * n x n chess board.
 * pawns at nth row.
 * enemy pawns at 1st row.
 * same pawn movement -> no pawn near -> move staright other wise diagonal
 * max pawn that reach row 1 -> output
 * enemy pawns never move and after at row 1 it can't make any move.
 *
 * n => 2 * 10^5 -> max O(n)
 * input in string form 1 means pawn at that index and 0 means empty cell
 *
 *
 *
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    char g[n + 2], e[n + 2];
    g[0] = '0'; e[0] = '0';
    scanf("%s %s", &e[1], &g[1]);
    int cnt = 0;
    for (int i = 1; i <=n; i++)
    {
        if (g[i] == '1' && e[i] == '0') 
        {
            /* printf("K: %d x %d \n",i,i); */
            cnt++;
        }
        else if (g[i] == '1' && i - 1 >= 1 && e[i - 1] == '1')
        {
            /* printf("K: %d x %d \n",i, i - 1); */
            cnt++;
            e[i - 1] = '0';
        }
        else if (g[i] == '1' && i + 1 <= n && e[i + 1] == '1')
        {
            /* printf("K: %d x %d \n", i, i + 1); */
            cnt++;
            e[i + 1] = '0';
        }

    }
    /* printf("D: g:%d cn:%d\n",g0,cnt); */
    printf("%d\n",cnt);
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

