/*
 * File: 1428B.c
 * Author: vididvidid 
 * Created: 2026-07-21 22:43:36
 */

/*
 * there are n rooms [0, n-1) arranged in circle
 * rooms are connected with n conveyor belt
 * ith room connects (i + 1) mod n room
 * converyor belt-> clockwise >
 *                  anticlockwise <
 *                  off (can travel in any direction) - 
 *
 * every snake want to leave its room and come back
 * room -> returnable : snake leave and can come back
 * output: how many returnable rooms
 *
 * so if < : 0 && > : N ||
 *       < : N && > : N ||
 *       < : 0 && > : 0
 *       ===== true for all..
 * 
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n;
    scanf("%d", &n);
    char s[n + 1];
    scanf("%s", s);

    int has_left = 0, has_right = 0;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '<') has_left = 1;
        if (s[i] == '>') has_right = 1;
    }

    if (!has_left || !has_right)
    {
        printf("%d\n", n);
        return;
    }

    int ans = 0;

    for (int i = 0; i < n; i++)
    {
        int prev_belt = (i - 1 + n) % n;

        if (s[i] == '-' || s[prev_belt] == '-')
        {
            ans++;
        }
    }

    printf("%d\n", ans);
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
