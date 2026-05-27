/*
 * File: 1097A.c
 * Author: vididvidid 
 * Created: 2026-04-14 10:13:53
 */

#include <stdio.h>
#include <string.h>

int main()
{
    char table[3],hand[5][3];
    scanf("%s",table);
    int flag =0;
    for (int i = 0; i < 5; i++){
        scanf("%s",hand[i]);
        if (hand[i][0] == table[0]) flag =1;
        if (hand[i][1] == table[1]) flag =1;
    }
    if (flag){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}
