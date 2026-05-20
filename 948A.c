/*
 * File: 948A.c
 * Author: vididvidid 
 * Created: 2026-05-12 05:13:02
 */

#include <stdio.h>

int main()
{
    int n,m;
    scanf("%d %d",&n,&m);
    char s[n][m+1];
    for (int i = 0; i < n; i++) scanf("%s",s[i]);

    int flag = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i < 0 || i >= n || j < 0 || j >= m) continue;
            int left = j - 1;
            int lf = 0;
            if (left < 0 || left >= m) lf = 1;
            int right = j + 1;
            int rf = 0;
            if (right < 0 || right >= m) rf = 1;;
            int up = i - 1;
            int ru = 0;
            if (up < 0 || up >= n) ru = 1;;
            int down = i + 1;
            int du = 0;
            if (down < 0 || down >= n) du = 1;;

            if (!lf && s[i][j] == 'S' && s[i][left] == 'W'){ flag = 1; break;}
            if (!rf && s[i][j] == 'S' && s[i][right] == 'W'){ flag = 1; break;}
            if (!ru && s[i][j] == 'S' && s[up][j] == 'W'){ flag = 1; break;}
            if (!du && s[i][j] == 'S' && s[down][j] == 'W'){ flag = 1; break;}

            if (!lf && s[i][j] == 'S' && s[i][left] == '.') s[i][left] = 'D';
            if (!rf && s[i][j] == 'S' && s[i][right] == '.') s[i][right] = 'D';
            if (!ru && s[i][j] == 'S' && s[up][j] == '.') s[up][j] = 'D';
            if (!du && s[i][j] == 'S' && s[down][j] == '.') s[down][j] = 'D';
        }
    }

    if (flag){
        printf("NO\n");
    } 
    else 
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            printf("%s",s[i]);
            printf("\n");
        }
    }
}
