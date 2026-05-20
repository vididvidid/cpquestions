/*
 * File: 1846B.c
 * Author: vididvidid 
 * Created: 2026-04-22 14:08:49
 */

#include <stdio.h>

void solve()
{
    char s[3][3];
    for (int i = 0; i < 3; i++) scanf("%s",s[i]);

    int flag = 0;
    //diagonal 
    
        if (s[0][0] == s[1][1] &&
            s[1][1] == s[2][2])
        {
            flag = (int)s[0][0];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }
        if (s[0][2] == s[1][1] &&
            s[1][1] == s[2][0])
        {
            flag = (int)s[0][2];

            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }
    //horizontal
        if (s[0][0] == s[0][1] &&
            s[0][1] == s[0][2])
        {
            flag = (int)s[0][0];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }

        if (s[1][0] == s[1][1] &&
            s[1][1] == s[1][2])
        {
            flag = (int)s[1][0];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }
        if (s[2][0] == s[2][1] &&
            s[2][1] == s[2][2])
        {
            flag = (int)s[2][0];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }
    //vertical
        if (s[0][0] == s[1][0] &&
            s[1][0] == s[2][0])
        {
            flag = (int)s[0][0];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }

        if (s[0][1] == s[1][1] &&
            s[1][1] == s[2][1])
        {
            flag = (int)s[0][1];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }

        if (s[0][2] == s[1][2] &&
            s[1][2] == s[2][2])
        {
            flag = (int)s[0][2];
            if ((char)flag != '.') {
                printf("%c\n",(char)flag);
                return;
            }
        }

    if (flag && (char)flag != '.') {
        printf("%c\n",(char)flag);
    } else {
        printf("DRAW\n");
    } 
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
