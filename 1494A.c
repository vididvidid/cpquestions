/*
 * File: 1494A.c
 * Author: vididvidid 
 * Created: 2026-05-10 04:36:21
 */

/*
 * given a string of ABC.. replace ABC with '()' so that it creates a perfect
 * parantheses collection..
 */

#include <stdio.h>
#include <string.h>

int check(char *s, int n)
{
    int mn = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] == '(') mn++;
        else mn--;
        if (i == 0 && mn < 0){
            return 0;
        }
        if (mn < 0) 
        {
            return 0;
        }
    }
    if (mn > 0 || mn < 0) return 0;
    else return 1;
}

void solve()
{
    char s[51];
    scanf("%s",s);
    int n = strlen(s);
    
    char a[8] = "(((())))";
    char b[8] = "(())))((";
    char c[8] = "()())()(";
    
    for (int i = 0; i < 8; i++)
    {
        char cp[n+1];
        strcpy(cp,s);
        for (int j = 0; j < n; j++)
        {
            if (cp[j] == 'A') cp[j] = a[i];
            if (cp[j] == 'B') cp[j] = b[i];
            if (cp[j] == 'C') cp[j] = c[i];
        }
        if (check(cp,n))
        {
            printf("YES\n");
            return;
        }
    }
    printf("NO\n");
    return;
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
