/*
 * File: 1676D.c
 * Author: vididvidid 
 * Created: 2026-05-26 05:47:41
 */

/*
 * find the max X(diagonal) sum in the matrix. 
 *
 * if you were given i,j and were told to find the digonal ends.
 * -> bottom right.. (i + d, j + d) n-i, m- i
 * -> top left ..    (i - d, j - d) i - 1, j - 1
 * -> bottom left..  (i + d, j - d) n - i, j - 1
 * -> top right ..   (i - d, j + d) i - 1, m - j  
 *
 *  here d is the distance ( min (n - i, m - j) )
 *
 *
 *  we will create two matrix one with sum of digonal to the right..
 *  and other to the sum of diagonals to the left.
 * 
 * than we will iterate over all the indexs and check for 
 * MAX(ans, prr[i'][j'] + srr[i''][j''] - arr[i][j])
 *
 */

#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)

int prr[201][201], srr[201][201], arr[201][201];

void solve()
{
    memset(prr, 0, sizeof(prr));
    memset(srr, 0, sizeof(srr));
    memset(arr, 0, sizeof(arr));

    int n, m;
    scanf("%d %d",&n, &m);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            scanf("%d",&arr[i][j]);
            prr[i][j] = arr[i][j];
            if (i > 1 && j > 1) {
                prr[i][j] += prr[i - 1][j - 1];
            }

            srr[i][j] = arr[i][j];
            if (i > 1 && j < m) {
                srr[i][j] += srr[i - 1][j + 1];
            }
        }
    }

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            int d1 = MIN(n - i, m - j);
            int val1 = prr[i + d1][j + d1];

            int d2 = MIN(n - i, j - 1);
            int val2 = srr[i + d2][j - d2];
            
            int tans = val1 + val2 - arr[i][j];
            ans = MAX(ans, tans);
        }
    }

    printf("%d\n",ans);
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
