/*
 * File: 38B.c
 * Author: vididvidid 
 * Created: 2026-07-19 13:47:32
 */

/*
 * you are given 8 x 8 chessboard with one rook and one knight already
 * placed on it. Your task is to count how many empty squares remain
 * where you can place a second knight such that:
 * 1. the new knight does not land on the smae row or column as the 
 * rook (so the rook does not attack it).
 * 2. The new knight is not a L shaped knight- jump away from the rook
 * (so the new knight does not attack the rook). also it does not
 * attack the first knight.
 * 3. the new knight is not palced on the square already occupied by
 * the existing rook or knight.
 */
#include <stdio.h>
#include <stdlib.h>

void solve()
{
    char rook[5], knight[5];
    scanf("%s %s", rook, knight);

    int r1 = rook[0] - 'a';
    int c1 = rook[1] - '1';
    int r2 = knight[0] - 'a';
    int c2 = knight[1] - '1';

    int valid_square  = 0;

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if ((i == r1 && j == c1) || (i == r2 && j == c2))
                continue;

            if (i == r1  || j == c1)
                continue;

            if ((abs(i - r1) == 1 && abs(j- c1) == 2) ||
                (abs(i - r1) == 2 && abs(j- c1) == 1))
                continue;

            if ((abs(i - r2) == 1 && abs(j - c2) == 2) ||
                (abs(i - r2) == 2 && abs(j - c2) == 1))
                continue;

            valid_square++;
        }
    }

    printf("%d\n", valid_square);
}

int main()
{
    solve();
    return 0;
}
