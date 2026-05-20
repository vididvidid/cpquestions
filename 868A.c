/*
 * File: 868A.c
 * Author: vididvidid 
 * Created: 2026-05-12 12:00:05
 */

#include <stdio.h>

int main()
{
    char ch[3];
    int n;
    scanf("%s",ch);
    scanf("%d",&n);
    int flag = 0;
    int f1 = -1, f2 = -1;
    for (int i = 0; i < n; i++)
    {
        char t[3];
        scanf("%s",t);
        if ((t[0] == ch[0] && t[1] == ch[1]) ||
            (t[0] == ch[1] && t[1] == ch[0])) 
        {
            flag = 1;
        }
        if (t[0] == ch[1]) f1 = i;
        if (t[1] == ch[0]) f2 = i;
    }

    if (flag)
    {
        printf("YES\n");
    }
    else
    {
        if (f1 != -1 & f2 != -1)
        {
            printf("YES\n");
        } else
        {
            printf("NO\n");
        }
    }
    return 0;
}
