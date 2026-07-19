/*
 * File: 385B.c
 * Author: vididvidid 
 * Created: 2026-07-19 11:11:30
 */

/*
 * count the number of pair that can contain bear as a substring in given string
 *
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    char s[5005];
    scanf("%s", s);
    int n = strlen(s);
    int arr[5000] = {0};
    int idx = 0;
    for (int i = 0; i <= n - 4; i++)
    {
        if (s[i] == 'b' && s[i + 1] == 'e' && s[i + 2] == 'a' && s[i + 3] == 'r')
        {
            arr[idx++] = i + 1;
        }
    }
    
    int ans = 0;
    int prev = 0;
    for (int i = 0; i < idx; i++)
    {
        int start = arr[i] - prev;
        int end = n - (arr[i] + 3) + 1;
        ans += start * end;
        prev = arr[i];
    }

    printf("%d\n",ans);
}

signed main()
{
    solve();
    return 0;
}
