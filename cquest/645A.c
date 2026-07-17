/*
 * File: 645A.c
 * Author: vididvidid 
 * Created: 2026-07-17 07:02:50
 */

/*
 * puzzle 2 * 2grid -> three tiles (A,B,C)
 * 2 person playing -> we have 2 grids -> find if we can make any of them
 * similar
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool check (char s[3][3], char t[3][3])
{
    if ((s[0][0] == t[0][0]) &&
        (s[0][1] == t[0][1]) &&
        (s[1][0] == t[1][0]) &&
        (s[1][1] == t[1][1]))
    {
        return true;
    }
    return false;
}

void rotate(char temp[3][3])
{

        if (temp[1][0] == 'X')
        {
            temp[1][0] = temp[1][1];
            temp[1][1] = 'X';
        }
        else if (temp[1][1] == 'X')
        {
            temp[1][1] = temp[0][1];
            temp[0][1] = 'X';
        }
        else if (temp[0][1] == 'X')
        {
            temp[0][1] = temp[0][0];
            temp[0][0] = 'X';
        }
        else if (temp[0][0] == 'X')
        {
            temp[0][0] = temp[1][0];
            temp[1][0] = 'X';
        }

        /* for (int i = 0; i < 2; i++) */
        /* { */
        /*     printf("D:%s\n",temp[i]); */
        /* } */
        /* printf("\n-----------------\n"); */
}
void solve()
{
    char s[3][3], t[3][3];
    scanf("%s %s %s %s", s[0], s[1], t[0], t[1]);
    
    char temp[3][3], temp2[3][3];
    for (int i = 0; i < 2; i++)
    {
        strcpy(temp[i], s[i]);
        strcpy(temp2[i], t[i]);
    }
    /* for (int i = 0; i < 2; i++) */
    /* { */
    /*     printf("D:%s\n",temp[i]); */
    /* } */

   int flag = 0; 
    do {
        if (check(temp, t))
        {
            flag = 1;
            break;
        }
        rotate(temp);
    } while (!check(s,temp));

    if (!flag)
    {
        do {
            if (check (temp2, s))
            {
                flag = 1;
                break;
            }
            rotate(temp2);
        } while (!check(t, temp2));
    }

    if (flag)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
}

int main()
{
    solve();
    return 0;
}
