/*
 * File: 2049B.c
 * Author: vididvidid 
 * Created: 2026-08-12 19:52:10
 */

/*
 * given an string s with p,s,.
 * check is at index i of that string..
 * if p is there than [1,i] should form permutation
 * if s is there than [i, n] sould form permutation of n - i + 1
 * if . can be anything.
 *
 * n < 500 
 */


#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char s[n + 1];
    scanf("%s", s);
    int cp = 0, cs = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (s[i] == 'p')
        {
            cp = 1;
            break;
        }
    }

    for (int i = 1; i < n ; i++)
    {
        if (s[i] == 's')
        {
            cs = 1;
            break;
        }
    }

    if (cp && cs)
    {
        printf("NO\n");
    }
    else
    {
        printf("YES\n");
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve(); 
    }

    return 0;
}
