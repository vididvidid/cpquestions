/*
 * File: 2078B.c
 * Author: vididvidid 
 * Created: 2026-07-21 14:07:12
 */

/*
 * give two integers n and k, construct a 1-indexed array a of length
 * n such that :
 * 1 < ai < n and ai != i for 1 <= i <= n
 * let f(x) be the transition function where f(x) = ax, and let f^k(x
 * rpresent applying the function exactly k times starting from index
 * x.
 * the sum of distance form index n after k transitions
 * sum(1..n) (n - f^k(i)) is minimized
 */

#include <stdio.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);

    int target = (k % 2 != 0) ? n : (n - 1);

    for (int i = 1; i <= n - 2; i++)
    {
        printf("%d ", target);
    }

    printf("%d %d\n", n, n - 1);
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
