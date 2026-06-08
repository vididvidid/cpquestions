/*
 * File: 120A.c
 * Author: vididvidid 
 * Created: 2026-06-08 15:28:00
 */

/*
 *      BACK DOOR 
 * left     |    right
 *  1       |      2
 *     FRONT DOOR
 *
 * if "front" : 1 -> L and 2 -> R
 * if "back"  : 1 -> R and 2 -> L
 *
 */

#include <stdio.h>
#include <string.h>

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    char s[6];
    scanf("%s",s);

    int k;
    scanf("%d",&k);

    if (strcmp(s, "front") == 0)
    {
        if (k == 1) 
        {
            printf("L\n");
        }
        else
        {
            printf("R\n");
        }
    }
    else
    {
        if (k == 1)
        {
            printf("R\n");
        }
        else 
        {
            printf("L\n");
        }
    }

    return 0;
}
