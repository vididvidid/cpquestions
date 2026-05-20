/*
 * File: 1534A.c
 * Author: vididvidid 
 * Created: 2026-04-25 04:44:43
 */

/*
 * Fill the grid with R and W wherever the . is present such that.. no Two
 * characters are same at there ajdacent.. (no diagonals)
 *
 * find the character with R or W on the grid while iterating
 * than put the alternate of that in the following spaces..
 * if (row - 1 >= 0 ) s[row-1][col] = 'R/W'
 * if (col + 1 < n) s[row][col+1] = 'R/W'
 * if (col - 1 >= 0) s[row][col-1] = 'R/W'
 * if (row + 1 < n) s[row+1][col] = 'R/W'
 *
 * in between while putting check 
 * if (at that location is equal to current character in the grid)
 *  flag = 1;
 *  break;
 *
 * i think i got the case if all are just blank ....
 * so what..
 * i think here comes the recursion because with loops i can't do it
 *
 * but how to apply the recursion here.. 
 * base case : if i > n && j > m : check and return
 * truning case : if i < 0 or j < 0 or i > n or j > m return;
 * if . try putting R or W.. 
 * start with R and than remove it than go with W..
 *
 * but there can be many solutions how to stop at one solutions.. 
 *
 * recur: (arr, i, j, n, m)
 * bc: i>n && j>m =>
 *      return
 * if (arr[i][j] == '.') 
 * {
 *  arr[i][j] = 'R'
 *  check(arr,i,j);
 *  recur(arr,i++,j++,n,m);
 *  arr[i-1][j-1] = 'W'
 *  check(arr,i,j);
 *  recur(arr,i,j,n,m);
 * } else {
 *  recur(arr,i++,j++,n,m);
 * }
 */
#include <stdio.h>
int count = 0;

int check ( int n, int m, char  arr[n + 1][m + 1])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            char ch,cr;
            if (arr[i][j] == 'R') ch= 'W',cr='R';
            else ch = 'R', cr = 'W';
            if (arr[i][j] == '.') continue;
            if (i - 1 >= 0) {
                if (arr[i-1][j] == cr) return 0;
            }
            if (i + 1 <  n) {
                if (arr[i+1][j] == cr) return 0;
            }
            if (j - 1 >= 0) {
                if (arr[i][j-1] == cr) return 0;
            }
            if (j + 1 < m ) {
                if (arr[i][j + 1] == cr) return 0;
            }
        }        
    }

    return 1;
}

void recur ( int i, int j, int n, int m, char  arr[n+1][m+1])
{
    if (count == 1) return;
    if (i == n) {
        if (check(n,m,arr)){
            count++;
            return;
        }
        return;
    }

    int nxt_i = i;
    int nxt_j = j + 1;
    if (nxt_j == m) {
        nxt_i = i + 1;
        nxt_j = 0;
    }

    if (arr[i][j] == '.')
    {
        arr[i][j] = 'R';
        if (check(n, m,arr)){
            recur(nxt_i, nxt_j, n, m, arr);
        } 
        if (count == 1) return;
        arr[i][j] = 'W';
        if (check(n, m, arr)) {
            recur(nxt_i, nxt_j, n, m,arr);
        }
        if (count == 1) return;
        arr[i][j] = '.';
    }
     else {
         if (check(n, m, arr)){
             recur(nxt_i, nxt_j, n, m, arr);
         }
    }
}

void solve()
{
    int n,m;
    scanf("%d %d",&n ,&m);
    char arr[n+1][m+1];
    for (int i = 0; i < n; i++)
            scanf("%s", arr[i]);
    
    int flag1 = 1, flag2 = 1;
    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < m; j++)
        {
            if (arr[i][j] != '.')
            {
                char exp1 = ((i + j) % 2 == 0) ? 'R' : 'W';
                char exp2 = ((i + j) % 2 == 0) ? 'W' : 'R';

                if (arr[i][j] != exp1) flag1 = 0;
                if (arr[i][j] != exp2) flag2 = 0;
            }            
        }

    }

    if (flag1) 
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%c",((i + j) % 2 == 0) ? 'R' : 'W');
            }
            printf("\n");

        }
    }
    else if (flag2)
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                printf("%c",((i + j) % 2 == 0) ? 'W' : 'R');
            }
            printf("\n");
        }
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
