/*
 * File: 548A.c
 * Author: vididvidid 
 * Created: 2026-07-05 09:54:42
 */

#include <stdio.h>
#include <string.h>

int check(char *s, int start, int end)
{
    while (start < end)
    {
        if (s[start] != s[end])
        {
            return 0;
        }

        start++;
        end--;
    }

    return 1;
}

void solve()
{
    char s[1000];
    scanf("%s",s);

    int k;
    scanf("%d", &k);

    int len = strlen(s);

    if (len % k != 0)
    {
        printf("NO\n");
        return ;
    }

    int sublen = len / k;

    for (int i = 0; i < len; i += sublen)
    {
        if (!check(s, i, i + sublen - 1))
        {
            printf("NO\n");
            return;
        }
    }

    printf("YES\n");
}

int main()
{
    solve();
    return 0;
}
