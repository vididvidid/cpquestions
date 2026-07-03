/*
 * File: 754B.c
 * Author: vididvidid 
 * Created: 2026-07-03 11:42:36
 */

#include <stdio.h>

int valid (char a, char b, char c)
{
    int x = 0, dot = 0;

    x += (a == 'x');
    x += (b == 'x');
    x += (c == 'x');

    dot += (a == '.');
    dot += (b == '.');
    dot += (c == '.');

    return (x == 2 && dot == 1);
}

void solve()
{
    int n = 4;
    char s[4][4];
    for (int i = 0; i < 4; i++) scanf("%s", s[i]);

    int dx[] = {0, 1, 1, 1};
    int dy[] = {1, 0, 1, -1};

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int d = 0; d < n; d++)
            {
                int x1 = i;
                int y1 = j;

                int x2 = i + dx[d];
                int y2 = j + dy[d];

                int x3 = i + 2 * dx[d];
                int y3 = j  + 2 * dy[d];

                if (x3 < 0 || x3 >= 4 || y3 < 0 || y3 >= 4)
                {
                    continue;
                }

                if (valid(s[x1][y1], s[x2][y2], s[x3][y3]))
                {
                    printf("YES\n");
                    return ;
                }
            }
        }
    }        

    printf("NO\n");
}


int main()
{
    solve();

    return 0;
}
