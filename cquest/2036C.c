/*
 * File: 2036C.c
 * Author: vididvidid 
 * Created: 2026-06-18 18:32:52
 */

/*
 * find if the substring 1100 is present after q queries performed on the given
 * string
 *
 * len(s) < 4 => NO
 * s & q queries contains 2 ones and 2 zeros
 *
 */

#include <stdio.h>
#include <string.h>


void solve()
{
    char s[200005];
    int  k[200005] = {0};
    int two = 0;
    s[0] = '0';
    scanf("%s",&s[1]);
    int len = strlen(s);
    int le = 0;
    if (len < 4) le = -1;
    if (le != -1)
    {
        for (int i = 1; i < len - 3; i++)
        {
            if (s[i] == '1' && s[i + 1] == '1' &&
                s[i + 2] == '0' && s[i + 3] == '0')
            {
                k[i] = 1;
                two++;
            }
            else
            {
                k[i] = 0;
            }
        }
    }


/*     // debug */
/*     for (int i = 1; i < len - 3; i++) */
/*     { */
/*         printf("%d ",k[i]); */
/*     } */
/*     printf("\n---\n"); */


    int n;
    scanf("%d",&n);
    while (n--)
    {
        int p;
        char v;
        scanf("%d %c", &p, &v);

        if (le == -1){
            printf("NO\n");
        }
        else {

            if (s[p] != v)
            {
                for (int j = p - 3; j <= p; j++)
                {
                    if (j > 0 && j <= len - 3)
                    {
                        if (k[j] == 1)
                        {
                            two--;
                            k[j] = 0;
                        }
                    }
                }
                
                s[p] = v;

                for (int j = p - 3; j <= p; j++)
                {
                    if (j > 0 && j <= len - 3)
                    {
                        if (s[j] == '1' && s[j + 1] == '1' &&
                            s[j + 2] == '0' && s[j + 3] == '0')
                        {
                            k[j] = 1;
                            two++;
                        }
                    }
                }
            }
            /* // debug */
            /* for (int i = 1; i <= len; i++) */
            /* { */
            /*     printf("%d ",k[i]); */

            /* } */

            /* printf("\n"); */
            
            if (two > 0)
            {
                printf("YES\n");
            }
            else
            {
                printf("NO\n");

            }
        }
    }
}

signed main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
