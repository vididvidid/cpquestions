/*
 * File: 1191B.c
 * Author: vididvidid 
 * Created: 2026-07-16 15:53:15
 */

/*
 * m -> 0 -> [1,9]
 * p -> 1 -> [1,9]
 * s -> 2 -> [1,9]
 * 
 * if i get frequ of arr[0][x] == 3 than print 0
 * if i get seqence of arr[0][x], arr[0][x + 1], arr[0][x+2] == 1 than print 0
 *
 * start by check if i have any of 2 in both cases
 *
 * if all one than print 2 
 */
#include <stdio.h>

void solve()
{
    int arr[3][10] = {0};
    int k;
    char c;
    for (int i = 0; i < 3; i++)
    {
        scanf("%d%c",&k, &c);
        if (c == 'm')
        {
            arr[0][k]++;
        }
        else if (c == 'p')
        {
            arr[1][k]++;
        }
        else if (c == 's')
        {
            arr[2][k]++;
        }
    }
    
    int f3 = 0, s3 = 0, f2 = 0, s2 = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            /* printf("%d ", arr[i][j]); */
            if (arr[i][j] == 3)
            {
                printf("0\n");
                return;
            }
            if (arr[i][j] == 2)
            {
                f2 = 1;
            }
            for (int k = j; k < j + 3 && k + 2 < 10; k++)
            {
                if (arr[i][k] && arr[i][k + 1] && arr[i][k + 2])
                {
                    printf("0\n");
                    return;
                }
                if ((arr[i][k] && arr[i][k + 1]) ||
                    (arr[i][k + 1] && arr[i][k + 2]) ||
                    (arr[i][k] && arr[i][k + 2])){
                    s2 = 1;
                }
            }
        }
    }

    if (f2 ||s2)
    {
        printf("1\n");
    }
    else
    {
        printf("2\n");
    }
}

int main()
{
    solve();
    return 0;
}
