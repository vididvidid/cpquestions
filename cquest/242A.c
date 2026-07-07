/*
 * File: 242A.c
 * Author: vididvidid 
 * Created: 2026-07-07 20:49:34
 */

/*
 * vasys toses coin x times, atleast a times got head and won
 * petya toses coin y times, atleast b times got head and lose
 *
 * simulate the outcome
 *
 * print n series
 * vesaya and petya.. 
 *
 * calculate n : 
 * so vasya is wining every time and to win v > p
 * 3 2 1 1
 * 2 1, 3 1, 3 2
 *
 * (2, 3) and (1, 2) ignore (2, 2)
 *  2 * 2 - 1 = 3
 *
 * 2 4 2 2
 * (0) * (2, 3, 4) 
 *
 *  0
 */


#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)
#define MIN(a,b) (a)<(b)?(a):(b)


void solve()
{
    int x, y, a, b;
    scanf("%d %d %d %d", &x, &y, &a, &b);

    int v = (x - a);
    int p = (y - b + 1);
    int comm = MAX(0, (MIN(x,y)) - (MAX(a + 1, b)) + 1);

    int n = v * p - comm;
    printf("%d\n",n);

    for (int i = a + 1; i <= x; i++)
    {
        for (int j = b; j <= y; j++)
        {
            if (i != j)
            {
                printf("%d %d\n",i, j);
            }
        }
    }
}

int main()
{
    solve();
    return 0;
}

