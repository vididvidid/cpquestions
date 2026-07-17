/*
 * File: 911B.c
 * Author: vididvidid 
 * Created: 2026-07-17 06:04:15
 */

/*
 * first cake -> a peices | second cake -> b peices
 * n people (include himself) -> n plates
 * each plate one piece of cake, no plate should have 2 piece of both cake
 * find minimum number of piece plate can have
 *
 * so we can't have both cake on one plate
 * which mean question is what is the minimum number of people per cake can
 * serve
 * 4 7 10
 * 2 -> 7 -> 3 + 4
 * 2 -> 10 -> 5 + 5 
 * min (3, 4, 5, 5) => 3  
 *
 */
#include <stdio.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))

void solve()
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    int cn = -1;
    int arr[1000];
    int idx = 0;
    for (int i = 1; i <= a; i++)
    {
        for (int j = a - 1; j >= 1; j--)
        {
            if (i + j == a)
            {
               int t1 = MIN((b/i), (c/j));
               int t2 = MIN((b/j), (c/i));
               arr[idx++] = t1;
               arr[idx++] = t2;
            }
        }
    }

    for (int i = 0; i < idx; i++)
    {
        cn = MAX(cn, arr[i]);
    }

    printf("%d\n",cn);
}

signed main()
{
    solve();
    return 0;
}
