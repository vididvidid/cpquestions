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

#define MAX(a,b) (a)>(b)?(a):(b)
void solve()
{
    int n;
    scanf("%d", &n);
    char s[n];
    scanf("%s", s);
    int k;
    scanf("%d", &k);
    char sp[k];
    for (int i = 0; i < k; i++)
    {
        scanf(" %c", &sp[i]);
    }
    
    int last_idx = 0, ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < k; j++)
        {
            if (s[i] == sp[j])
            {
                int idx = i - last_idx;
                ans = MAX(ans, idx);
                last_idx = i;
            }
        }
    }
    printf("%d\n",ans);
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
