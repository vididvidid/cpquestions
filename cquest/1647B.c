/*
 * File: 1647B.c
 * Author: vididvidid 
 * Created: 2026-07-14 13:45:51
 */

/*
 * Table -> rectangle (n, m) filled with (0,1)
 * Facts: 
 * A is in B, if every cell of A is also a cell of B
 * A and B interest if there is a cell common/contained between them
 * Subrectangle -> black -> if no cell have value 0
 * Subrectangle -> nice -> black and not contained in another black subrectangle
 * Table -> Elegant -> no two intersecting -> nice rectangle
 *
 * Two black rectangles that don't intersect themselves.
 *
 * n,m <= 100 , t < 200 => brute force will work O(n^2) we can go
 *
 * -------------------------------------------------------------------------
 * Problem Simplification
 *
 * Given n x m binary matrix, determine if all connected components of 1s form
 * disjoint, non-overlapping rectangles
 * Formally: Output YES if no two distinct maximal subrectangles of 1s share any
 * cells. Output NO otherwise.
 *
 * n x m ~ 10^4
 *
 * --------------------------------------------------------------------------
 * 1x1
 * 0 1
 *
 * 2x2
 * 00 11 10 01 01 10 11 
 * 00 11 10 01 10 01 10
 *
 * 1x2
 * 00 01 10 11
 *
 * 2x1
 * 0 1 0 1
 * 0 1 1 0
 *
 * Q. In all above cases what will be the output because there is only one
 * disjoint 1's rectangle ?
 * --> you overcomplicated it problem just read there should be no intersection.
 *     is there any no. Than YES
 *
 * Q. Only in 2x2 diagonal case we see the 2 disjoint rectangles otherwise
 * there is only one.
 * --> In all 2x2 cases it will be YES except for where 3 1's are there and 1'0
 *     than it will be NO
 *
 * Q. Also in scenerios of 1 x n or n x 1 what will be the output if all are
 * 0's if all are 1's or starting is 0's and ending is 1's or vice versa because
 * if there is in between 0 than 2 disjoint will be formed?
 * --> Same as first Question.. 
 *
 * Q. Also do we consider all rectangles to be disjoint or any 2 rectangles?
 * --> I just need to only check if there is any overlapping.
 *
 * Q. How we will detect that this rectangle is not intersecting with other?
 * Q. How we count how many rectangles we have?
 * --> we don't need to do that. This is the point where i am overcomplicating
 *  things.
 *
 * Just observe one pattern wherever there is the intersection there is 2 x 2
 * grid with 3 1's and 1 0. So all i have to check if this exist or not.
 *
 * 110 111 
 * 111 110
 * 110 111
 *
 * --------------------------------------------------------------------------
 */

#include <stdio.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    int arr[n][m];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char ch;
            scanf(" %c", &ch);
            arr[i][j] = ch - '0';
        }
    }

    if (n == 1 || m == 1)
    {
        printf("YES\n");
    }
    else
    {
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < m - 1; j++)
            {
               int sum = arr[i][j] + arr[i + 1][j] +
                         arr[i][j + 1] + arr[i + 1][j + 1];
               if (sum == 3)
               {
                   printf("NO\n");
                   return;
               }
            }
        }
        printf("YES\n");
    }
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
