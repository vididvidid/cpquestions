/*
 * File: 1419B.c
 * Author: vididvidid 
 * Created: 2026-07-18 00:36:47
 */

/*
 * you are given x cells (square) to build "nice" staircases.
 * -> A staircase with n stairs requires 1 + 2 + .. + n = n (n + 1) / 2 cells.
 * -> A staircase is defined as nice if and only if its height n is one less
 *  than a power of 2:
 *  n = 2^k - 1 for k > 1 => n belogs to (1, 3, 5, 7, 15, 31..)
 * Goal: find the maximum number of different nice staircase you can build such
 * that the total number of cells is used at most x. Each nice staircase size
 * can be built at most once.
 *
 * x < 10^18 long long 
 * stair case growth by k = 32, a single stair case exceeds ~ 1.5 * 10^18 cells
 * therefore answer will never exceed 31 
 */
#include <stdio.h>

void solve()
{
    long long x;
    scanf("%lld", &x);
    int cnt = 0;
    long long k = 1;

    while (1)
    {
        long long need = (1LL << (k - 1)) * ((1LL << k) - 1);

        if (x >= need)
        {
            x -= need;
            cnt++;
            k++;
        }
        else
        {
            break;
        }
    }

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
