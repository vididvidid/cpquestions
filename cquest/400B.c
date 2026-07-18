/*
 * File: 400B.c
 * Author: vididvidid 
 * Created: 2026-07-18 21:38:08
 */

/*
 * nxm matrix each line have G and S tell the min moves that player will make to
 * move all the G to S cell if he can't print -1
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    char s[n+1][m + 1];
    int arr[1005] = {0};
    for (int i = 0; i < 1005; i++) arr[i] = 0;
    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
        int gi = 0, si = 0;
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == 'G') gi = j + 1;
            if (s[i][j] == 'S') si = j + 1;
        }

        if (si < gi) flag = 1;
        else
        {
            arr[si-gi]++;
        }
    }

    if (flag)
    {
        printf("-1\n");
    }
    else
    {
        int cnt = 0;
        for (int i = 0; i < 1005; i++)
        {
            if (arr[i])
            {
                cnt++;
            }
        }

        printf("%d\n",cnt);
    }
}

int main()
{
    solve();
    return 0;
}
