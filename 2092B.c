/*
 * File: 2092B.c
 * Author: vididvidid 
 * Created: 2026-05-16 06:10:25
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char a[n+1], b[n+1];
    scanf("%s %s",a,b);

    int a1 = 0, b1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0){
            if (a[i] == '1') a1++;
        }
        else {
            if (b[i] == '1') b1++;
        }
    }
    if ((a1 + b1 ) > n/2) 
    {
        printf("NO\n");
        return;
    }
   
    int a2 = 0, b2 = 0;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0){
            if (b[i] == '1') b2++;
        }
        else {
            if (a[i] == '1') a2++;
        }
    }
    if ((a2 + b2 ) > (n+1)/2) 
    {
        printf("NO\n");
        return;
    }

    printf("YES\n");
    
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
