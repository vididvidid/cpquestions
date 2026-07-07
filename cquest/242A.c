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

    int arr[100000];
    int idx = 0;
    int s = (a > b) ? (a) : a + 1;
    for (int i = s; i <= x; i++)
    {
        for (int j = b; j <= y; j++)
        {
            if (i != j && i > j)
            {
                arr[idx++] = i * 10 + j;
            }
        }
    }

    printf("%d\n",idx);
    for (int i = 0; i < idx; i++)
    {
        int l = arr[i] % 10;
        int r = arr[i] / 10;
        printf("%d %d\n",r, l);
    }
}

int main()
{
    solve();
    return 0;
}

