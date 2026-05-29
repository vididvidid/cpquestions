/*
 * File: 1506C.c
 * Author: vididvidid 
 * Created: 2026-05-29 16:24:01
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    char a[25], b[25];
    scanf("%s",a);
    scanf("%s",b);

    int lena = strlen(a);
    int lenb = strlen(b);
    int mx = 0;

    for (int i = 0; i < lena; i++) {
        for (int j = i; j < lena; j++)
        {
            char temp = a[j + 1];
            a[j + 1] = '\0';

            if (strstr(b, &a[i]) != NULL)
            {
                int len = j - i + 1;
                if (len > mx) 
                {
                    mx = len;
                }
            }

            a[j + 1] = temp;
        }
    }

    int mn = (lena - mx) + (lenb - mx);
    printf("%d\n",mn);
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
