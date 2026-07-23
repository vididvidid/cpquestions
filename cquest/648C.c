/*
 * File: 648C.c
 * Author: vididvidid 
 * Created: 2026-07-23 11:36:48
 */

/*
 * There are N daughters and N kingdoms. Each daugher has a list of 
 * preferred kingdoms.
 *
 * Matching is greedy: going in order from daughter 1 to N, each 
 * daughter marries the first available kingdome on her list.
 *
 * You want to find if adding exactly one kingdeom to one daughter's 
 * list can increase the total number of marriages.
 *
 * If possible, print "IMPROVE" and the (daugher, kingdom) pair. If
 * everyone is already matched, print "OPTIMAL".
 *
 */
#include <stdio.h>

char grid[105][105];
int visited[105][105];

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);

    int start_r = -1, start_c = -1;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", grid[i]);
        for (int j = 0; j < m; j++)
        {
            visited[i][j] = 0;
            if (grid[i][j] == 'S')
            {
                start_r = i;
                start_c = j;
            }
        }
    }

    int dr[] = {-1, 1, 0 , 0};
    int dc[] = {0, 0, -1, 1};
    char dir_char[] = {'U', 'D', 'L', 'R'};

    int r = start_r;
    int c = start_c;
    visited[r][c] = 1;

    for (int i = 0; i < 4; i++)
    {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (nr >= 0 && nr < n && nc >= 0 && nc < m && grid[nr][nc] !='.')
        {
            putchar(dir_char[i]);
            r = nr;
            c = nc;
            visited[r][c] = 1;
            break;
        }

    }

    while (r != start_r || c != start_c)
    {
        int moved = 0;
        for (int i = 0; i < 4; i++)
        {
            int nr = r + dr[i];
            int nc = c + dc[i];
            if (nr >= 0 && nr < n && nc >= 0 && nc < m &&
                    !visited[nr][nc] && grid[nr][nc]!='.')
            {
                putchar(dir_char[i]);
                r = nr;
                c = nc;
                visited[r][c] = 1;
                moved = 1;
                break;
            }
        }

        if (!moved)
        {
            for (int i = 0; i < 4; i++)
            {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr == start_r && nc == start_c)
                {
                    putchar(dir_char[i]);
                    r = nr;
                    c = nc;
                    break;
                }
            }
        }
    }

    putchar('\n');
}

int main()
{
    solve();
    return 0;
}
