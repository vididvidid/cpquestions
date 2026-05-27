/*
 * File: 1703A.c
 * Author: vididvidid 
 * Created: 2026-04-11 04:55:32
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void solve()
{
    char s[4];
    scanf("%s",s);
    for (char *p = s; *p != '\0'; p++)
    {
        *p = toupper((unsigned char)*p);
    
    }

    if (strcmp(s,"YES") == 0)
    {
        printf("YES\n");
    }
    else {
        printf("NO\n"); 
    }
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
