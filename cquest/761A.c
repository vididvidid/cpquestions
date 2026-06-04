/*
 * File: 761A.c
 * Author: vididvidid 
 * Created: 2026-06-04 12:30:44
 */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, m;
    scanf("%d %d",&n, &m);
    if (n == 0 && m == 0)
    {
        printf("NO\n");
    }
    else if (abs(n - m) >=0 && abs(n - m) <=1) 
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

    return 0;
}
