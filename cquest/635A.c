/*
 * File: 635A.c
 * Author: vididvidid 
 * Created: 2026-06-11 12:22:12
 */
/*
 * *#
 * **
 *
 * ->  * | *#  | *# | * |
 * ->  * |     | ** |   | 
 *
 * ->  # | #
 * ->    | *
 *
 * ->  * | * *
 * 
 * ->  *
 *
 * so there are total (r - i + 1) * (c - j + 1) patterns possible at i, j
 *
 */
#include <stdio.h>
#include <string.h>

int main()
{
    int r, c, n, m;
    scanf("%d %d %d %d", &r, &c, &n, &m );

    char s[r+2][c+2];
    for (int i = 0; i < r + 2; i++)
    {
        for (int j = 0; j < c + 2; j++)
        {
            s[i][j] = '*';
        }
    }

    for (int i = 0; i < n; i++)
    {
        int tr, tc;
        scanf("%d %d", &tr, &tc);
        s[tr][tc] = '#';
    }
    int ans = 0; 
    for (int i = 1; i <= r; i++)
    {
        for (int j = 1; j <= c; j++)
        {
            // on each coordinate..
            for (int end_r = i; end_r <= r; end_r++)
            {
                for (int end_c = j; end_c <= c; end_c++)
                {
                    int count = 0;
                    // on every possible subgrid combination..
                    for (int p = i; p <= end_r; p++)
                    {
                        for (int q = j; q <= end_c; q++)
                        {
                            /* printf("%c", s[p][q]); */
                            if (s[p][q] == '#') count++;
                        }
                        /* printf("\n"); */
                    }
                    if (count >= m)
                    {
                        ans++;
                    }
                    /* printf("\n---------------------\n"); */
                }
            }
            /* printf("\n\n+++++++++++++++++\n\n"); */
        }        
    }

    printf("%d\n",ans);
    return 0;
}
