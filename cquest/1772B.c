/*
 * File: 1772B.c
 * Author: vididvidid 
 * Created: 2026-04-18 11:08:57
 */

// rotate matrix by 90 degree clockwise and check if
// 00 < 01 , 00 < 10 , 01 < 11 , 10 < 11
//
// 00 01 =>  10 00 => 11 10 => 01 11 => 00 01
// 10 11 =>  11 01 => 01 00 => 00 10 => 10 11
//
// iterate over rows 
// -> iterate over columns
//      if 00 -> 10 
//      if 01 -> 00
//      if 10 -> 11
//      if 11 -> 01
//
#include <stdio.h>

void solve()
{
    int arr[2][2];
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            scanf("%d",&arr[i][j]);
    int flag = 1;
    if (arr[0][0] < arr[0][1] && 
        arr[0][0] < arr[1][0] &&
        arr[0][1] < arr[1][1] &&
        arr[1][0] < arr[1][1])
    {
        flag = 0;
        printf("YES\n");
    } else {
        for (int i = 0; i < 3; i++)
        {
            int tmp[2][2];
            for (int j = 0; j < 2; j++)
            {
                for (int k = 0; k < 2; k++)
                {
                    if (j == 0 && k == 0) tmp[j][k] = arr[1][0];
                    if (j == 0 && k == 1) tmp[j][k] = arr[0][0];
                    if (j == 1 && k == 0) tmp[j][k] = arr[1][1];
                    if (j == 1 && k == 1) tmp[j][k] = arr[0][1];
                }        
            }

            for (int j = 0; j < 2; j++)
                for (int k = 0; k < 2; k++)
                    arr[j][k] = tmp[j][k];

            /* printf("\t %d %d \n\t %d %d\n",arr[0][0], arr[0][1], arr[1][0], arr[1][1]); */

            if (arr[0][0] < arr[0][1] &&
                arr[0][0] < arr[1][0] &&
                arr[0][1] < arr[1][1] &&
                arr[1][0] < arr[1][1]) {
                printf("YES\n");
                flag = 0;
                break;
            }
        }
    }

    if (flag)
    {
        printf("NO\n");
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
