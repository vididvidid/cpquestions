/*
 * File: 1797A.c
 * Author: vididvidid 
 * Created: 2026-07-19 16:30:27
 */

/*
 * n x m rectangular matrix.
 * path is the sequence of empty cells
 * put minimum obstacles so that you can't reach the destination cell
 *
 */

#include <stdio.h>

int neigh(int r, int c, int n, int m) {
    if ((r == 1 || r == n) && (c == 1 || c == m))
    {
        return 2;
    }
    else if (r == 1 || r == n || c == 1 || c == m) 
    {
        return 3;
    }
    else 
    {
        return 4;
    }
}

void solve()
{
    int n, m;
    int x1, y1, x2, y2;

    scanf("%d %d", &n, &m);
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    int sn = neigh(x1,y1,n,m);
    int en = neigh(x2,y2,n,m);

    if (sn < en)
    {
        printf("%d\n",sn);
    }
    else
    {
        printf("%d\n",en);
    }
}

int main()
{
    int t;
    scanf("%d", &t);

    while(t--)
    {
        solve();
    }

    return 0;
}
