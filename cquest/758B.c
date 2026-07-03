/*
 * File: 758B.c
 * Author: vididvidid 
 * Created: 2026-07-02 16:29:34
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    char s[101];
    scanf("%s", s);

    int ch[4][5] = {0};
    for (int i = 0; i < strlen(s); i++)
    {
        int pos = i % 4;
        if (s[i] == 'R') ch[pos][0]++;
        if (s[i] == 'B') ch[pos][1]++;
        if (s[i] == 'Y') ch[pos][2]++;
        if (s[i] == 'G') ch[pos][3]++;
        if (s[i] == '!') ch[pos][4]++;
    }
   
    int ans[4] = {0};
    /* printf("G\tR\tB\tY\t!\n"); */
    for (int i = 0; i < 4; i++)
    {
        int mx = 0;
        for (int j = 0; j < 4; j++)
        {
            if (ch[i][j] > ch[i][mx])
            {
               mx = j; 
            }
            /* printf("%d\t",ch[i][j]); */
        }
        if (ch[i][4] > 0) {
            ans[mx] = ch[i][4];
        }
        /* printf("\n"); */
    }

    for (int i = 0; i < 4; i++)
    {
        printf("%d ",ans[i]);
    }
    printf("\n");
}

int main()
{
    solve();
    return 0;
}
