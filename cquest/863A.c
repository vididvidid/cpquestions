/*
 * File: 863A.c
 * Author: vididvidid 
 * Created: 2026-05-12 12:15:33
 */

#include <stdio.h>
#include <string.h>

int check (char *s, int n)
{
    char ch[n+1];
    int c = 0;
    for (int i = n-1; i >= 0; i--)
    {
        ch[c++] = s[i];
    }
    ch[n] = '\0';
    /* printf("DEBUG:n:%d ch:%s and s:%s\n",n,ch,s); */
    if (strcmp(ch,s) == 0) return 1;
    else return 0;
}

int main()
{
    char s[11];
    scanf("%s",s);
    for (int i = strlen(s)-1 ; i >= 0; i--)
    {
        if (s[i] == '0') s[i] = '\0';
        else break;
    }

    int n = strlen(s);
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '0') k++;
        else break;
    }
    n -= k;
    if (check(&s[k],n))
    {
        printf("YES\n");
    }
    else 
    {
        printf("NO\n");
    }
    return 0;
}
