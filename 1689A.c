/*
 * File: 1689A.c
 * Author: vididvidid 
 * Created: 2026-04-24 02:23:57
 */

/*
 * create a lexicographically string by taking k characters at a time from
 * either of the strings.. and do that until any of the string becomes empty..
 * you can't take k characters same the next time.. it should be alternate..
 * 
 *
 * s1 -> 97 98 99 100 101 102 ...
 *      a  b  c  d   e   f
 *      6
 *
 * s2 -> 97 98 99 100 101 102 ..
 *       a  b  c  d   e   f
 *       0  4
 *
 * c1 -> 0        
 * c2 -> 0
 * while (s1[c1]==-1) c1++; // in case when there is frequency..
 * c1-=k;
 *
 * while ((c1 != 25 && s1[c1]!=-1)  || (c2 != 25 && s2[c2] != -1))
 *
 * ans[m+n] 
 * while (tk--) ans[m+n] <- insert the character ; s1[c1]--; 
 */
/*
 * File: 1689A.c
 * Author: vididvidid 
 * Created: 2026-04-24 02:23:57
 */

/*
 * create a lexicographically string by taking k characters at a time from
 * either of the strings.. and do that until any of the string becomes empty..
 * you can't take k characters same the next time.. it should be alternate..
 * 
 *
 * s1 -> 97 98 99 100 101 102 ...
 *      a  b  c  d   e   f
 *      6
 *
 * s2 -> 97 98 99 100 101 102 ..
 *       a  b  c  d   e   f
 *       0  4
 *
 * c1 -> 0        
 * c2 -> 0
 * while (s1[c1]==-1) c1++; // in case when there is frequency..
 * c1-=k;
 *
 * while ((c1 != 25 && s1[c1]!=-1)  || (c2 != 25 && s2[c2] != -1))
 *
 * ans[m+n] 
 * while (tk--) ans[m+n] <- insert the character ; s1[c1]--; 
 */

#include <stdio.h>

void solve()
{
    int n, m, k;
    scanf("%d %d %d",&n, &m, &k);
    int nrr[26] , mrr[26];
    char ans[n+m+1];
    int c1 = 0, c2 = 0;
    for (int i = 0; i < 26; i++) nrr[i] = -1, mrr[i] = -1;
    for (int i = 0; i < n; i++)
    {
        char ti;
        scanf(" %c",&ti);
        nrr[ti-'a']++;
    }
    for (int i = 0; i < m; i++)
    {
        char ti;
        scanf(" %c",&ti);
        mrr[ti-'a']++;
    }
    /* printf("--- DEBUG ---- \n"); */
    /* for (int i = 0; i < 26; i++) printf("%d ",nrr[i]); */
    /* printf("\n"); */
    /* for (int i = 0; i < 26; i++) printf("%d ",mrr[i]); */
    /* printf("\n"); */


    while (nrr[c1] == -1) c1++;
    while (mrr[c2] == -1) c2++;
    int  an = 0, mv = 0;
    mv = (c1 <= c2);

    while (c1 < 26 && c2 < 26)
    {

        while (nrr[c1] == -1) c1++;
        while (mrr[c2] == -1) c2++;
        if (c1 >= 26) break;
        if (c2 >= 26) break;
        /* printf("DEBUG: move: %d c1: %d c2 : %d\n",mv,c1,c2); */

        if (mv)
        {
            /* printf("\tDEBUG: F ---------------------- F\n"); */
            int lup = k;
            while (c1 < 26 && lup > 0)
            {
                if (lup < k)
                {
                    if (c2 < c1 && mrr[c2] > -1) break;
                }
                while (nrr[c1] == -1) c1++;
                if (c1 >= 26) break;
                /* printf("\tDEBUG: F=> c1 : %d lup: %d an: %d nrr[c1]: %d\n", */
                          /* c1,lup,an,nrr[c1]); */
                ans[an++] = (char) c1 + 'a';
                nrr[c1]--;
                lup--;
                while (nrr[c1] == -1) c1++;
            }
            mv  = !mv;
        }
        else 
        {
            /* printf("\t DEBUG: S --------------------------- S\n"); */
            int lup = k;
            while (c2 < 26 && lup > 0)
            {
                if (lup < k)
                {
                    if (c1 < c2 && nrr[c1] > -1) break;
                }
                while (mrr[c2] == -1) c2++;
                if (c2 >= 26) break;

                /* printf("\tDEBUG: S=> c2 : %d lup: %d an: %d mrr[c2]: %d\n", */
                          /* c2,lup,an,mrr[c2]); */
                ans[an++] = (char) c2 + 'a';
                mrr[c2]--;
                lup--;
                while (mrr[c2] == -1) c2++;
            }
            mv = !mv;
        }
    }
    ans[an] = '\0';
    printf("%s\n",ans);
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
