/*
 * File: 602A.c
 * Author: vididvidid 
 * Created: 2026-07-03 15:07:50
 */

#include <stdio.h>

long long convert (int len, int base)
{
    long long num = 0;
    for (int i = 0; i < len; i++)
    {
        int d;
        scanf("%d", &d);

        num = num * base + d;
    }

    return num;
}

void solve()
{
    int n, bx;
    scanf("%d %d", &n, &bx);

    long long x = convert(n, bx);

    int m, by;
    scanf("%d %d", &m, &by);

    long long y = convert(m, by);


    if (x < y)
    {
        printf("<\n");
    }
    else if (x > y)
    {
        printf(">\n");
    }
    else
    {
        printf("=\n");
    }
}

int main()
{
    solve();
    return 0;
}
