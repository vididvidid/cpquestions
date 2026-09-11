/*
 * File: 1249C1.c
 * Author: vididvidid 
 * Created: 2026-09-12 00:32:10
 */

/*
 * find the good number m >= n which is the unique sum of power of 3
 *
 *
 * so i took the hint for generating the combination which come out that use bit
 * mask but with this i got the idea why not use base3.
 *
 * so point is first revise the binary base 2
 * if x = 14 what we do
 * 14%2 = 0 (14/2 = 7)
 * 7 %2 = 1 (7 /2 = 3)
 * 3 %2 = 1 (3 /2 = 1)
 * 1 %2 = 1 (1 /2 = 0)
 *
 * (2^4) (2^3) (2^2) (2^1)
 *   1     1     1     0   = 8 + 4 + 2 + 0 = 14
 * so here you can see every power is unique and its sum of it..
 *
 * so similary we will do in base 3
 * if x = 14 what we do
 * 14%3 = 2 (14/3 = 4)
 * 4 %3 = 1 (4 /3 = 1)
 * 1 %3 = 1 (1 /3 = 0)
 *
 * (3^2) (3^1) (3^0)
 *   1     1     2   = 9 + 3 + (2 * 1) = 14 here 1 is repeated twice which we
 *                                          can identify by 2 in it
 *
 * so for any number in base 3 we just don't need to take the number who have
 * remaineder as 2, than we will get number who have unique power
 * like 40
 * 40%3 = 1 (40/3 = 13)
 * 13%3 = 1 (13/3 = 4)
 * 4 %3 = 1 (4 /3 = 1)
 * 1 %3 = 1 (1 /3 = 0)
 *
 * (3^3) (3^2) (3^1) (3^0)
 *   1     1     1     1   = 27 + 9 + 3 + 1 = 40 
 */
#include <stdio.h>
#include <string.h>

#define int long long
#define N 20000
int arr[N];

void precompute() 
{

    memset(arr, 0 , sizeof(arr));    

    for (int i = 1; i < N; i++)
    {
        int x = i;
        int flag = 0;
        while (x > 0)
        {
            if (x % 3 == 2)
            {
                flag = 1;
                break;
            }

            x /= 3;
        }

        if (!flag)
        {
            arr[i] = i;
        }
    }

    int hasValue = -1;
    for (int i = 0; i < N; i++)
    {
        hasValue = i;
        if (arr[i] == 0 && hasValue == i)
        {
            for (int j = i + 1; j < N; j++)
            {
                if (arr[j] != 0)
                {
                    hasValue = j;
                    arr[i] = j;
                    break;
                }
            }
        }
        else if (arr[i] == 0 && hasValue != i)
        {
            arr[i] = hasValue;
        }
    }

    /* for (int i = 0; i < 50; i++) */
    /* { */
    /*     printf("%lld ", arr[i]); */
    /* } */

}

void solve()
{
    int n;
    scanf("%lld", &n);
    printf("%lld\n",  arr[n]);
}


signed main()
{
    precompute();
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
