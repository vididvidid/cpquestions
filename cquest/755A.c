/*
 * File: 755A.c
 * Author: vididvidid 
 * Created: 2026-07-19 16:21:12
 */

/*
 * n * m + 1 = prime number prove it wrong by output any value of m
 */
#include <stdio.h>

void solve()
{   
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= 1000; i++)
    {
        int x = (n * i) + 1;
        for (int j = 2; j * j <= x; j++)
        {
            if (x % j == 0)
            {
                printf("%d\n", i);
                return;
            }
        }
    }


}

int main()
{
    solve();
    return 0;
}
