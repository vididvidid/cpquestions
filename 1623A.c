/*
 * File: 1623A.c
 * Author: vididvidid 
 * Created: 2026-04-24 05:54:54
 */

/*
 * robot moves (r+dr) (c+dc)
 * if it touches vertical wall than (r+dr)(c-dc)
 * if it touches horizontal wall than (r-dr)(c-dc)
 *
 * 4x4...
 * robot.. 3x3 -> (3-dr)(3-dc) -> (2,2)
 * robot.. 3x2 -> (3-dr)(3+dc) -> (2,3)
 * robot.. 2x3 -> (3+dr)(3-dc) -> (3,2)
 *
 * if (r == n-1 || r == 0) -dr
 * if (c == n-1 || c == 0) -dc 
 *
 */

#include <stdio.h>

void solve()
{
    int n, m, rr, rc, dr, dc;
    scanf("%d %d %d %d %d %d", &n, &m, &rr, &rc, &dr, &dc);
    int count = 0;
    /* printf("get it\n"); */
    if (dr > n || dc > m ){ 
        printf("0\n");
        return;
    }
    int mr = 1, mc = 1;
    while (rr !=dr && rc != dc)
    {
        /* printf("\tinside the loop\n"); */

        if (rr == n) mr = -1;
        if (rr == 1) mr = 1;

        if (rc == m) mc = -1;
        if (rc == 1) mc = 1;
        rr += mr;
        rc += mc;

        /* printf("\trr: %d and rc: %d\n",rr,rc); */
        count++;
    }
    printf("%d\n",count);
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
