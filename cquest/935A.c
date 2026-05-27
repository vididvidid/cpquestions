/*
 * File: 935A.c
 * Author: vididvidid 
 * Created: 2026-04-14 08:24:20
 */

// given n and tell ways to divide so it in group so that evenly people can
// be put there
// my thought is to think for the factors of the number..
// like in case of
// 2 : 1 and 2 (we can't count 2 because we have to keep one employee) so only
//      1
// 3 : 1 and 3 so here also 1 option..
// 4 : {1, 2, 4} so here is 2 options.. 
//     either take 1 team leader and 3 eployees
//     either take 2 team leader and 1 employees in each
// 5 : {1, 5} 
// 10 : {1, 2, 5} 
//

#include <stdio.h>

int main()
{
    int count=0, n;
    scanf("%d",&n);
    for (int i = 1; i < n ;i++)
    {
        if (n % i == 0) count++;
    }

    printf("%d\n",count);
    return 0;
}
