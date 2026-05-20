/*
 * File: 918A.c
 * Author: vididvidid 
 * Created: 2026-04-29 08:20:55
 */

/*
 * create a string where if ith character is fibonacci sequence it is 'o'
 * otherwise it is 'O'
 *
 * fibonacci -> 987 digit at 16th position..
 *
 * fib1 = 1, fib2 = 1
 * for (i : 1 to n):
 *      if (i == fib2) :
 *              s[i-1] = 'o'
 *              int temp = fib1
 *              fib1 = fib2;
 *              fib2 = temp+fib1;
 *      else
 *          s[i-1] = 'O'
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d",&n);
    char s[n+1];
    int fib1 = 1, fib2 = 1;
    for (int i = 1; i <= n; i++)
    {
        if (i == fib2)
        {
            s[i-1] = 'O';
            int temp = fib1;
            fib1 = fib2;
            fib2 = temp+fib1;
        }
        else
        {
            s[i-1] = 'o';
        }
    }

    s[n] = '\0';
    printf("%s\n",s);
    return 0;
}
