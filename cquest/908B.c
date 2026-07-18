/*
 * File: 908B.c
 * Author: vididvidid 
 * Created: 2026-07-17 06:24:28
 */

/*
 * nxm 2d maze .(empty cells) #(obstacles)
 * robot -> S(starting position) -> E(exit position)
 * robot -> move -> left, right, up and down
 * string of digits -> [0,3] -> distinct direction -
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    char grid[55][55];
    int start_r = -1, start_c = -1;

    for (int i = 0; i < n; i++)
    {
        scanf("%s", grid[i]);
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 'S')
            {
                start_r = i;
                start_c = j;
            }
        }
    }

    char s[105];
    scanf("%s", s);
    int len = strlen(s);
    
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = {0, 0, -1, 1};

    int ans = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++) {
            if (i == j) continue;

            for (int p = 0; p < 4; p++)
            {
                if (p == i || p == j) continue;

                for (int q = 0; q < 4; q++)
                {
                    if (q == i || q == j || q == p) continue;

                    int map[4] = {i, j, p, q};
                    int r = start_r, c = start_c;
                    int success = 0;

                    for (int x = 0; x < len; x++)
                    {
                        int move = map[s[x] - '0'];
                        r += dr[move];
                        c += dc[move];

                        if (r < 0 || r >= n || c < 0 || c >= m)
                        {
                            break;
                        }

                        if (grid[r][c] == '#') {
                            break;
                        }

                        if (grid[r][c] == 'E') {
                            success = 1;
                            break;
                        }
                    }

                    if (success) 
                    {
                        ans++;
                    }
                }
            }
        }
    }

    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}
