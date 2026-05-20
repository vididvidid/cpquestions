/*
 * File: 299B.c
 * Author: vididvidid 
 * Created: 2026-05-13 07:04:15
 */

#include <stdio.h>

int main()
{
    int n,k;
    scanf("%d %d",&n, &k);
    char s[n+1];
    scanf("%s",s);
    int flag = 0;
    if (s[n-1] == '#') {
        printf("NO\n");
        return 0;
    }
    for (int i = 0; i < n; )
    {
        if (s[i] == '.') i++;
        else {
            i--;
            int t = k;
            /* printf("BEFORE: %d\n",i); */
            while (t > 0)
            {
                if (i+t < n  && s[i+t] == '.'){
                    break;
                }
                else {
                    /* printf("got int\n"); */
                    t--;

                }
            }

            /* printf("AFTER: %d t is %d\n",i,t); */
            if (t == 0) break;
            i += t;
        }
        if ( i == n-1 ) flag = 1;
    }
    if (flag) printf("YES\n");
    else printf("NO\n");
    return 0;
}
