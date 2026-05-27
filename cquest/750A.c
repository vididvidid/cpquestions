/*
 * File: 750A.c
 * Author: vididvidid 
 * Created: 2026-04-11 07:26:43
 */
#include <stdio.h>

int main()
{
    int n , k;
    scanf("%d %d", &n, &k);
    int totalTime = (4 * 60 - k) / 5;
    int res = 0;
    int i = 1;
    for (; i <= n; i++)
    {
        int temp = totalTime - i;
        if (temp < 0){
           res = i - 1;
           break;
        } else if (temp == 0){
            res = i;
            break;
        }
        totalTime = temp;
    }
    if (res == 0) res = i-1;
    printf("%d\n",res);
    return 0;
}
