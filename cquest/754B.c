/*
 * File: 754B.c
 * Author: vididvidid 
 * Created: 2026-07-03 11:42:36
 */

#include <stdio.h>

void solve()
{
    int n = 4;
    char s[4][4];
    for (int i = 0; i < 4; i++) scanf("%s", s[i]);
    
    int flag = 0;
    // left diagonal, right diagonal, horizontal, vertical
    // horizontal
    if (!flag)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n - 2; j++)
            {
                if ((s[i][j] == 'x' && s[i][j+1] == 'x' && s[i][j+2] == '.') ||
                    (s[i][j] == 'x' && s[i][j+1] == '.' && s[i][j+2] == 'x') ||
                    (s[i][j] == '.' && s[i][j+1] == 'x' && s[i][j+2] == 'x') 
                    )
                {
                    flag = 1;
                    break;
                }
            }
        }
    }

    // vertical
    if (!flag)
    {
        for (int i = 0; i < n - 2; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((s[i][j] == 'x' && s[i+1][j] == 'x' && s[i + 2][j] == '.') ||
                    (s[i][j] == '.' && s[i+1][j] == 'x' && s[i + 2][j] == 'x') ||
                    (s[i][j] == 'x' && s[i+1][j] == '.' && s[i + 2][j] == 'x')
                   )
                {
                    flag = 2;
                    break;
                }
            }
        }
    }

    // left diagonal
    if (!flag)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = n - 1; j >= 0; j--)
            {
                if ((i + 1) < n && (i + 2) < n && (j - 1) >= 0 && (j- 2) >= 0 && 
                    ((s[i][j] == 'x' && s[i + 1][j - 1] == 'x' && s[i + 2][j - 2] == '.') ||
                     (s[i][j] == 'x' && s[i + 1][j - 1] == '.' && s[i + 2][j - 2] == 'x') ||
                     (s[i][j] == '.' && s[i + 1][j - 1] == 'x' && s[i + 2][j - 2] == 'x'))
                    )
                {
                    flag = 3;
                    break;
                }
            }
        }
    }

    // right diagonal
    if (!flag)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if ((i + 1) < n && (i + 2) < n && (j + 1) < n && (j+ 2) < n && 
                    ((s[i][j] == 'x' && s[i + 1][j + 1] == 'x' && s[i + 2][j + 2] == '.') ||
                     (s[i][j] == 'x' && s[i + 1][j + 1] == '.' && s[i + 2][j + 2] == 'x') ||
                     (s[i][j] == '.' && s[i + 1][j + 1] == 'x' && s[i + 2][j + 2] == 'x'))
                    )
                {
                    flag = 4;
                    break;
                }
            }
        }
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
    solve();

    return 0;
}
