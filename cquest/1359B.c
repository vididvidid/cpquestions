/*
 * File: 1359B.c
 * Author: vididvidid 
 * Created: 2026-06-01 06:18:46
 */

/*
 * count the minium price that we have to pay to cover 1x1 and 1x2 tiles.. 
 *
 */

#include <stdio.h>
#define MIN(a,b) (a)<(b)?(a):(b)
void solve()
{
    int n,m,x,y;
    scanf("%d %d %d %d",&n, &m, &x, &y);
    char s[n+1][m+1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s",s[i]);
    }

    int d = 0, dd = 0;
    for (int i = 0; i < n; i++)
    {
        int flag = -1;
        for (int j = 0; j < m; j++)
        {
            if (s[i][j] == '.') d++;

            if (j)
            {
                if (flag != j - 1 && s[i][j-1] == '.' && s[i][j] == '.'){
                    dd++;
                    flag = j;
                }
            }
        }
    }

    int ld = d - 2*dd;
    /* printf("DEBUG: %d %d %d\n",d,ld,dd); */

    int tans = y*dd + x*ld;
    int ans = MIN(x*d , tans);
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
