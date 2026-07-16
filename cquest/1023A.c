/*
 * File: 1023A.c
 * Author: vididvidid 
 * Created: 2026-07-16 22:56:21
 */

/*
 * given string s and t
 * s -> lowercase alphabets and * -> length n
 * t -> lowercase alphabets -> length m
 * at most one * will be there..
 * you can add as many character or leave empty in place of *
 * your task is to check if it can be made similar to t or not..
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n, m;
    scanf("%d %d", &n ,&m);
    char s[n + 1], t[m + 1];
    scanf("%s", s);
    scanf("%s", t);

    if ( n > m + 1 )
    {
        printf("NO\n");
        return;
    }
    if( n == m )
    {
        int temp = 0;
        for (int i = 0; i < n; i++)
        {
            if (s[i] == t[i])
            {
                temp++;
            }
        }
        if (temp == n)
        {
            printf("YES\n");
            return;
        }
    }
    int i = 0, j = n - 1;
    for (; i < n; i++)
    {
        if (s[i] == '*') break;
        if (s[i] != t[i])
        {
            printf("NO\n");
            return;
        }
    }
    int k = m -1;
    for (; j >= 0; j--,k--)
    {
        if (s[j] == '*') break;
        if (s[j] != t[k]) {
            printf("NO\n");
            return;
        }
    }

    if (i > j) 
    {
        printf("NO\n");
        return;
    }

    printf("YES\n");

}

signed main()
{
    solve();
    return 0;
}
