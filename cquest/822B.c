/*
 * File: 822B.c
 * Author: vididvidid 
 * Created: 2026-06-03 10:21:29
 */

#include <stdio.h>

#define MAX(a,b) (a)>(b)?(a):(b)

int main()
{
    int n, m;
    scanf("%d %d",&n, &m);
    char s[n], t[m];
    scanf("%s %s",s, t);

    int ans = 0, cn = 0, idx = -1;
    for (int i = 0; i <= m - n; i++)
    {
        cn = 0;
        int pos = 0;
        for (int j = i; j < i + n; j++)
        {
            /* printf("%c-%c\t",s[pos],t[j]); */
            if (s[pos++] == t[j]) cn++;
        }
        
        /* printf("\n%d\n",cn); */
        int tans = ans;
        ans = MAX(ans, cn);
        if (tans != ans)
        {
            idx = i;
        }
        
    }
    /* printf("DEBUG: index = %d\n",idx); */
    if (idx == -1) idx = 0;
    int pos = 0;
    printf("%d\n",n - ans);
    for (int i = idx; i < idx + n; i++)
    {
        if ( i < m && s[pos] != t[i])
        {
            printf("%d ",pos + 1);
        }
        pos++;
    }
    printf("\n");
}
