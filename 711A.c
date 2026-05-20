/*
 * File: 711A.c
 * Author: vididvidid 
 * Created: 2026-04-22 05:54:07
 */

// find two characters consectuive to each other that are 'OO'
// store in s[n][5] and s[0][1] is divided by a bar in between.. 
// so check if s[0][0] == 'O' && s[0][1] == 'O' || 
//             s[0][3] == 'O' && s[0][4] == 'O'
// no s[0][2] because it will be separator '|'


#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    char s[n][5];
    int flag = 0;
    for (int i = 0; i < n; i++) {
        scanf("%s",s[i]);
        if ( (flag == 0) && (
            (s[i][0] == 'O' && s[i][1] == 'O') ||
            (s[i][3] == 'O' && s[i][4] == 'O')))
        {
            if (s[i][0] == 'O' && s[i][1] == 'O') 
            {
                s[i][0] = '+';
                s[i][1] = '+';
            } else {
                s[i][3] = '+';
                s[i][4] = '+';
            }
            flag = 1;
        }
    }

    if (flag)
    {
        printf("YES\n");
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                printf("%c",s[i][j]);
            }
            printf("\n");
        }
    } else
    {
        printf("NO\n");
    }
}
