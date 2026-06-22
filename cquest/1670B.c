/*
 * File: 1670B.c
 * Author: vididvidid 
 * Created: 2026-06-22 14:16:30
 */

/*
 * given string s, and special characters remove the letter just before the
 * appearance of special characters, tell how many times you can do it.
 *
 * find the last special character and second last special character position
 * and subtract it. 
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n;
    scanf("%d", &n);
    char s[n];
    scanf("%s", s);
    int k;
    scanf("%d", &k);
    int mx1 = 0, mx2 = -1;
    for (int i = 0; i < k; i++)
    {
        char c;
        scanf(" %c", &c);
        char *ptr = strrchr(s, c);
        printf("PRINT: idx = %td\n", ptr - s);
        if (ptr) {
            int idx = ptr - s ;
            if (mx1 < idx)
            {
                mx2 = mx1;
                mx1 = idx;
            }
            else if (mx2 < mx1 && mx2 < idx)
            {
                mx2 = idx;
            }
        }
        printf("PRINT: mx1 > %d and mx2 > %d\n",mx1, mx2);
    }
    
    if (mx1 > 0 && mx2 == 0)
    {
        printf("%d\n",mx1);
    }
    else if (mx1 > 0 && mx2 > 0 && mx1 - mx2 > 1)
    {
        printf("%d\n",mx1 - mx2 - 1);
    }
    else if (mx1 > 0 && mx2 > 0)
    {
        printf("%d\n",mx1 - mx2);
    }
    else
    {
        printf("0\n");
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
