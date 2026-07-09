/*
 * File: 259b.c
 * Author: vididvidid 
 * Created: 2026-07-09 15:36:44
 */

#include <stdio.h>

void solve()
{
    int arr[3][3];
    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            scanf("%d", &arr[i][j]);
            sum += arr[i][j];
        }
    }

    sum /= 2;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (arr[i][j] == 0)
            {
                int k = arr[i][0] + arr[i][1] + arr[i][2];
                int val = sum - k;
                printf("%d ",val);
            }
            else {
                printf("%d ",arr[i][j]);
            }
        }         
        printf("\n");
    }

}

int main()
{
    solve();
    return 0;
}
