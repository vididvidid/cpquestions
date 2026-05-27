/*
 * File: 776A.c
 * Author: vididvidid 
 * Created: 2026-05-13 08:09:44
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char a[11],b[11];
    scanf("%s %s",a,b);
    int n;
    scanf("%d",&n);
    printf("%s %s\n",a,b);
    while (n--)
    {
        char s[11],t[11];
        scanf("%s %s",s,t);
        if (strcmp(a,s) == 0) 
        {
            strcpy(a,t);
        }
        else {
            strcpy(b,t);
        }
        printf("%s %s\n",a,b);
    }
    return 0;
}
