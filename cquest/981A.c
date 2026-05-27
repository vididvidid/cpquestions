/*
 * File: 981A.c
 * Author: vididvidid 
 * Created: 2026-05-12 04:07:04
 */

#include <stdio.h>
#include <string.h>

#define MAXLEN 51

int check (char *s, int t, int n)
{
    char k[t+1],p[t+1];
    int c = 0;
    for (int i = t; i >= 0; i--)
    {
        k[c++] = s[i];
    }
    k[t] = '\0';
    c = 0;
    for (int i = 0;i <= t; i++)
    {
        p[c++] = s[i];
    }
    p[t]  = '\0';
    /* printf("DEBUG:t:%d %s and %s\n",t,p,k); */ 
    if (strcmp(k,p) == 0) return 0;
    else return 1;
}

int main()
{
    char s[MAXLEN];
    scanf("%s",s);
    int ans = 0;
    int n = strlen(s);
    int t = n;
    t--;
    while (t >= 0)
    {
        /* printf("%d\n",check(s,t,n)); */
        if (check(s,t,n))
        {
            break;
        }
        t--;
    }
    printf("%d\n",t+1);
}
