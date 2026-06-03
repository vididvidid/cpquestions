/*
 * File: 864B.c
 * Author: vididvidid 
 * Created: 2026-06-03 09:27:36
 */

#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    int arr[26] = {0};
    int n;
    scanf("%d",&n);
    char s[n];
    scanf("%s",s);

    int ans = 0, cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if ((s[i] - 'a') >= 0 && (s[i] - 'a') < 26)
        {
            if (!arr[s[i]-'a'])
            {
                cnt++;
                arr[s[i] - 'a']++;
            }
        } else 
        {
            /* printf("%d ",cnt); */
            ans = MAX(ans, cnt);
            cnt = 0;
            for (int i = 0; i < 26; i++) arr[i] = 0;
        }
   }
    /* printf("\n-----------\n"); */
    ans = MAX(ans, cnt);
    printf("%d\n",ans);
    return 0;
}
