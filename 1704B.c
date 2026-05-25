/*
 * File: 1704B.c
 * Author: vididvidid 
 * Created: 2026-05-24 00:20:09
 */

/*
 * 17, 11, 9, 17
 *
 * 2 4 6 8 6 4 12 14
 * 4 4 4 6 6 6 12 12
 * ------x-----x----
 *
 * 25   3   3   17  8   6   1   15    25  17  23
 * 17   11  11  11  11  11  9   9     17  17  17
 * 8    8   8   6   3   5   8   7     8   0   6
 * -----x-------------------x---------x----------
 * 33   11  11  25  15  14  9   23    33  25  31
 * 17   -5  -5  9   0   -2  -7  7     17  9   15
 * ---------------------------------------------
 *  17  9   9   9   9   9   9   9     17  17  17
 *  ----x-----------------------------x--------
 *
 *  11  4   13  23  7   10  5   21  20  11  17  5   29  16  11
 *  6   6   8   18  12  12  10  22  22  6   22  10  24  27  6
 *  --------x---x---x-------x----x------x----x---x--x----x--x
 *
 *  |v-ai| <= x
 *  |v-ai| + |v - ai| + |v - ai| <= x + x + x
 *  | 3v - (ai + ai + ai) | <= 3x
 *
 */
#include <stdio.h>

#define int long long
#define MIN(a, b) (a)<(b)?(a):(b)
#define MAX(a, b) (a)>(b)?(a):(b)


void solve()
{
    int n, x;
    scanf("%lld %lld",&n, &x);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld",&a[i]);
    }
    int chngs = 0;
    int l = a[0] - x;
    int r = a[0] + x;

    for (int i = 1; i < n; i++)
    {
        int nl = a[i] - x;
        int nr = a[i] + x;

        int nul = MAX(l, nl);
        int nur = MIN(r, nr);

        if (nul > nur) 
        {
            chngs++;
            l = nl;
            r = nr;
        } else
        {
            l = nul;
            r = nur;
        }
    }
    printf("%lld\n",chngs);
}

int main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
