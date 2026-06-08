/*
 * File: 109A.c
 * Author: vididvidid 
 * Created: 2026-06-08 16:49:01
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    int c4 = 0, c7 = 0;

    while (n >= 0)
    {
        if (n % 7 == 0){
            c7 = n / 7;
            n = 0;
            break;
        }
        c4++;
        n -= 4;
    }


    if (n < 0 )
    {
        printf("-1\n");
    } else{
        for (int i = 0; i < c4; i++) {
            printf("4");
        }
        for (int i = 0; i < c7; i++) {
            printf("7");
        }
        printf("\n");
    }
    return 0;
}
