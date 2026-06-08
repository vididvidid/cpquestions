/*
 * File: 284B.c
 * Author: vididvidid 
 * Created: 2026-06-08 15:07:50
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    char s[n];
    scanf("%s",s);
    int ans = 0, k = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == 'A') ans++;
        else if (s[i] == 'I') k++;
    }
    if (k == 0) { printf("%d\n",ans); }
    else if (k == 1) { printf("1\n"); }
    else {
        printf("0\n");
    }
    return 0;
}
