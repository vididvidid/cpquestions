/*
 * File: 799A.c
 * Author: vididvidid 
 * Created: 2026-06-15 21:59:09
 */

#include <stdio.h>

void solve()
{
    int n, t, k, d;
    scanf("%d %d %d %d", &n, &t, &k, &d);

    int intrvl = (n - 1) / k;

    if (d < intrvl * t)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}

int main(){
    solve();
    return 0;
}
