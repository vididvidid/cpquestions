/*
 * File: 1598A.c
 * Author: vididvidid 
 * Created: 2026-04-25 01:54:31
 */

/*
 * grid traversal reach to the end..
 *
 * diagonal
 * 01 10  
 * 10 01
 * if (row,col+1) == 1 && (ro1+1, col) == 1 => than lower diagonal (row+1,col+1)
 * if (row-1,col) == 1 && (row, col+1) == 1 => than upper diagonal (row-1,col+1)
 *
 * move right
 * => majority of time we have to move right only.. because if we reach the end
 *    boundary we can just move down only.. 
 * while (row,col+1) == 0 than move left (row, col+1)
 *
 * move down
 * => only move down when you hit the boundary
 * 0X
 * 0X
 * if (row == 1 && col == n) => than row+1,col
 *
 * move up 
 * => only when you hit the boundary
 * X0
 * X0
 * if (row == 2 && col == 0) => than row-1,col
 *
 * break if 
 * 01
 * 11
 * if (row,col+1 == 1 && row+1,col+1 == 1 && row+1,col == 1) break;
 */
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char s[3][n+2];
    for (int i = 1; i < 3; i++) scanf("%s",&s[i][1]);
    int flag = 0;
    int row = 1,col = 1;
    /* printf("START: %d %d\n",row,col); */
    while (row != 2 || col != n)
    {
        // breaking..
        if ( (row + 1 < 3 && col + 1 < n + 1) &&
            s[row][col+1] == '1' && 
            s[row+1][col] == '1' &&
            s[row+1][col+1] == '1')
        {
            /* printf("\tBREAK: %d %d\n",row,col); */
            break;
        }

        if ((row + 1 < 3 && col + 1 < n + 1) &&
            s[row][col+1] == '1' &&
            s[row+1][col+1] == '1')
        {
            /* printf("\tBREAK2: %d %d\n",row,col); */
            break;
        }


        if (s[2][n] == '1') 
        {
            /* printf("\tBREAK3: %d %d\n",row,col); */
            break;
        }

        if (s[1][1] == '1')
        {
            /* printf("\tBREAK4: %d %d\n",row,col); */
            break;
        }

        if (row > 2 || col > n) 
        {
            /* printf("\tBREAK5: %d %d\n",row,col); */
            break;
        }

        if (row < 1 || col < 1)
        {
            /* printf("\tBREAK6: %d %d\n",row, col); */
            break;
        }

        if ((row - 1 > 0 && col +1 < n + 1) &&
            s[row][col+1] == '1' &&
            s[row-1][col+1] == '1')
        {
            /* printf("\tBREAK7: %d %d\n",row, col); */
            break;
        }

        // move right
        while (col+1 < n+1  && s[row][col+1] == '0')
        {
            col++;
            /* printf("\tRIGHT: %d %d\n",row,col); */
        }

        // move diagonal
        if  ((row+1 < 3) &&
               (col+1 < n+1) &&
               (s[row+1][col+1] == '0'))
        {
            row++,col++;
            /* printf("\tD-DIAG: %d %d\n",row, col); */
        }

        // move up diagonal
        if  ((row-1 > 0) &&
               (col+1 < n+1) &&
               (s[row-1][col+1] == '0'))
        {
            row--,col++;
            /* printf("\tU-DIAG: %d %d\n",row,col); */
        }

        // move down
        if ((row == 1) &&
            (col == n)) 
        {
            row++;
            /* printf("\tDOWN: %d %d\n",row,col); */
        }

        // move up
        if ((row == 2) &&
            (col == 0))
        {
            row--;
            /* printf("\tUP: %d %d\n",row,col); */
        }

    }
    /* printf("END: %d %d\n",row, col); */
    if (row == 2 && col == n) {
        flag = 1;
    }

    if (flag)
    {
        printf("YES\n");
    } 
    else 
    {
        printf("NO\n");
    }
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

