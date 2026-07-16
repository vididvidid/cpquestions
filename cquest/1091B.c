/*
 * File: 1091B.c
 * Author: vididvidid 
 * Created: 2026-07-16 17:51:59
 */

/*
 * Treasure is located at T.
 * n obselik -> treasure locations.. 
 * ith obselik -> coordinate (xi, yi)
 * jth obselik -> clue (aj, bj)
 * T = (xi + aj, yi + bj)
 *
 * so find the matching of all clues with obselik so all point to the T.
 * and we don't need to find mapping we jsut need to find T coordinate.. 
 *
 * n < 1000 we can go with O(n^2) 
 * also because 10^6 we can create 4 different negx,posx,negy,posy and store
 * things
 *
 */

#include <stdio.h>

#define MAX(a,b) ((a)>(b)?(a):(b))

typedef struct
{
    int x;
    int y;
    int freq;
} cord;

void solve()
{
    int n;
    scanf("%d", &n);
    cord loc[n], clue[n];
    cord pair[n * n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &loc[i].x , &loc[i].y);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &clue[i].x, &clue[i].y);
    }

    int idx = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int tx = loc[i].x + clue[j].x;
            int ty = loc[i].y + clue[j].y;
            int flag = 0;
            for (int k = 0; k < idx; k++)
            {
                if (pair[k].x == tx && pair[k].y == ty)
                {
                    pair[k].freq++;
                    flag = 1;
                    break;
                }
            }
            if (!flag)
            {
                pair[idx].x = loc[i].x + clue[j].x;
                pair[idx].y = loc[i].y + clue[j].y;
                pair[idx].freq = 1;
                idx++;
            }
        }
    }

    int mx = -1;
    for (int i = 0; i < idx; i++)
    {
        mx = MAX(mx, pair[i].freq);
    }
    for (int i = 0; i < idx; i++)
    {
        if (pair[i].freq == mx)
        {
            printf("%d %d\n",pair[i].x, pair[i].y);
            return;
        }
    }
}

int main()
{
    solve();
    return 0;
}
