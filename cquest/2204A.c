/*
 * File: 2204A.c
 * Author: vididvidid 
 * Created: 2026-04-22 06:55:08
 */

/*
 * check if we covered all the indexes from [1 to n] or not.. 
 * print the number of indexs that have covered atleast once.
 */
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n+1];
    arr[0] = -1;
    for (int i = 1; i <= n; i++) arr[i] = 0;
    char s[n];
    scanf("%s",s);
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (s[i] != 'L'){
            ans++;
        } else {
            ans++;
            break;
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
