/*
 * File: bf1.c
 * Author: vididvidid 
 * Created: 2026-11-03 12:05:09
 */

#include <stdio.h>
#include <stdbool.h>

void logic_bf1(int n, int m, char (*arr)[m])
{
    int rooms = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (arr[i][j] == '.')
            {
                rooms++;
                arr[i][j] = 'p';
                bool changed = true;
                while (changed)
                {
                    changed = false;
                    for (int a = 0; a < n; a++)
                    {
                        for (int b = 0; b < m; b++)
                        {
                            if (arr[a][b] == '.' && 
                                (arr[a-1][b] == 'p' || arr[a +1][b] == 'p' ||
                                 arr[a][b-1] == 'p' || arr[a][b + 1] == 'p'))
                            {
                                arr[a][b] = 'p';
                                changed = true;
                            }
                        }
                    }
                }
                for (int a = 0; a < n; a++)
                {
                    for (int b = 0; b < n; b++)
                    {
                        if (arr[a][b] == 'p')
                        {
                            arr[a][b] == '#';
                        }
                    }
                }
            }
        }
    }

    printf("%d\n", rooms);
}

void solve()
{
    int n = 5, m = 8;
    char arr[5][8] = {
        "########",
        "#..#...#",
        "####.#.#",
        "#..#...#",
        "########"
    };

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c ", arr[i][j]);
        }
        printf("\n");
    }

    logic_bf1(n, m, arr);
}

int main()
{
    solve();
    return 0;
}
