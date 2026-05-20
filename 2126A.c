/*
 * File: 2126A.c
 * Author: vididvidid 
 * Created: 2026-04-13 12:57:01
 */

#include <stdio.h>
#include <limits.h>
#define MIN(A,B) ((A) < (B) ? (A) : (B))
void solve()
{
    int n;
    scanf("%d",&n);
    int num = INT_MAX;
    while (n > 0){
        int t = n %10;
        num = MIN(num, t);
        n /= 10;
    }
    printf("%d\n",num);
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
