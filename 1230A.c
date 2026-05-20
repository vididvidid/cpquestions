/*
 * File: 1230A.c
 * Author: vididvidid 
 * Created: 2026-04-25 13:28:54
 */

#include <stdio.h>

int main()
{
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    if ((a+b==c+d) ||
            (a+c == b + d) ||
            (a + d == b + c) ||
            (a + b + c == d) ||
            (a + b + d == c) ||
            (a + c + d == b) ||
            (b + c + d == a)){
        printf("YES\n");
        return 0;
    } else{
        printf("NO\n");
        return 0;
    }
    return 0;
}
