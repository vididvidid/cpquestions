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

    long long sum_x = 0, sum_y = 0;
    int x, y;

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        sum_x += x;
        sum_y += y;
    }

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &x, &y);
        sum_x += x;
        sum_y += y;
    }

    printf("%lld %lld\n", sum_x/n, sum_y/n);
}

int main()
{
    solve();
    return 0;
}
