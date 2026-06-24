/*
 * File: 1105B.c
 * Author: vididvidid 
 * Created: 2026-06-25 01:26:55
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n, k;
    scanf("%d %d", &n, &k);

    char s[200005];
    scanf("%s", s);

    int counts[26] = {0};

    int curr = 0;
    char currc = '\0';

    for (int i = 0; i < n; i++)
    {
        if (s[i] == currc) {
            curr++;
        }
        else
        {
            currc = s[i];
            curr = 1;
        }

        if (curr == k) {
            counts[s[i] - 'a']++;
            curr = 0;
        }
    }

    int max = 0;
    for (int i = 0; i < 26; i++) {
        if (counts[i] > max) {
            max = counts[i];
        }
    }

    printf("%d\n", max);
}

int main()
{
    solve();
    return 0;
}
