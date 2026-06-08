/*
 * File: 357A.c
 * Author: vididvidid 
 * Created: 2026-06-08 14:54:03
 */

/*
 * divide the student in groups [x,y] based on marks
 */
#include <stdio.h>

int main()
{
    int m;
    scanf("%d",&m);
    int arr[m + 1];
    int total = 0;
    for (int i = 1; i <= m; i++)
    {
        scanf("%d",&arr[i]);
        total += arr[i];
    }
    int x, y;
    scanf("%d %d",&x ,&y);

    int ans = 0, sum = 0;
    for (int i = 2; i <= m; i++)
    {
        sum += arr[i - 1];
        int ys = total - sum;
        if (sum >= x && sum <= y && ys <= y && ys >= x)
        {
            printf("%d\n",i);
            return 0;
        }
    }

    printf("%d\n",ans);
    return 0;
}

