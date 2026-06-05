/*
 * File: 626A.c
 * Author: vididvidid 
 * Created: 2026-06-05 13:38:03
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char s[205];
    scanf("%s",s);

    int vs = 0;

    for (int i = 0; i < n; i++)
    {
        int u = 0, d = 0, l = 0, r = 0;

        for (int j = i; j < n; j++) {
            if (s[j] == 'U') u++;
            else if (s[j] == 'D') d++;
            else if (s[j] == 'L') l++;
            else if (s[j] == 'R') r++;

            if (u == d && l == r) {
                vs++;
            }
        }
    }

    printf("%d\n",vs);
}

int main()
{
    solve();
}
