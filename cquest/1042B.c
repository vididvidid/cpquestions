/*
 * File: 1042B.c
 * Author: vididvidid 
 * Created: 2026-07-16 19:05:54
 */

/*
 * n kind of juices
 * each juice price is ci
 * each juice contain vitamin (A or B or C)
 * return minimum price of juice wiht all three vitamins
 *
 * can i write a sort function for my custom struct that is based on string
 * length and price
 * the comparator
 * it was nice writing the sort function for my struct
 *
 * now question is to find min value..
 * so take all single character..
 * so take 2 character + one single character
 * so take all 3 character.. 
 *
 * -----------------------------------------------------------------
 *  I was overcomplicating the problem we have use bitmask and its solvable
 *  easily
 *  * 1. BITMASK CREATION:
 *    Instead of strings, map vitamins to the first 3 bits of an integer:
 *    'A' -> 1 (001), 'B' -> 2 (010), 'C' -> 4 (100).
 *    Combine them using Bitwise OR (|). E.g., "BC" = 2 | 4 = 6 (binary 110).
 *    There are only 7 possible combinations (masks 1 to 7).
 *    We also use mask 0 (binary 000) with cost 0 to represent buying "nothing".
 *
 * 2. INPUT OPTIMIZATION (MIN CHECKING):
 *    We don't need to store all N juices. For any combination (e.g., "AB"),
 *    we only ever want to buy the cheapest one. During input, we continuously
 *    update `min_cost[mask] = MIN(min_cost[mask], price)` to discard expensive
 *    duplicates immediately.
 *
 * 3. THE 3 NESTED LOOPS:
 *    To get all vitamins, the combined bitmask must equal 7 (binary 111).
 *    We loop i, j, k from 0 to 7 to test combining up to 3 masks: (i | j | k) == 7.
 *    By including 0 (cost 0), this single loop cleanly handles:
 *    - Buying 3 juices: e.g., i="A", j="B", k="C"
 *    - Buying 2 juices: e.g., i="AB", j="C", k=0 (nothing)
 *    - Buying 1 juice : e.g., i="ABC", j=0, k=0
 *
 */
#include <stdio.h>

#define INF 3000000
#define MIN(a,b) ((a)<(b)?(a):(b))

void solve()
{
    int n;
    scanf("%d", &n);

    int mn[8];
    for (int i = 0; i < 8; i++) {
        mn[i] = INF;
    }
    mn[0] = 0;

    for (int i = 0; i < n; i++)
    {
        int price;
        char s[4];
        scanf("%d %s", &price, s);

        int mask = 0;
        for (int j = 0; s[j] != '\0'; j++)
        {
            if (s[j] == 'A') mask |= 1;
            if (s[j] == 'B') mask |= 2;
            if (s[j] == 'C') mask |= 4;
        }

        mn[mask] = MIN(mn[mask], price);
    }

    int ans = INF;
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            for (int k = 0; j <= 7 && k <= 7; k++)
            {
                if ((i | j | k) == 7) {
                    ans = MIN(ans, mn[i] + mn[j] + mn[k]);
                }
            }
        }
    }

    if (ans == INF)
    {
        printf("-1\n");
    }
    else {
        printf("%d\n", ans);
    }
}

int main()
{
    solve();
    return 0;
}
