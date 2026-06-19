/*
 * File: 1948B.c
 * Author: vididvidid 
 * Created: 2026-06-19 19:42:55
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[105] = {0}, prr[105] = {0};
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < n - 1; i++)
    {
        /* printf("\n---------\n"); */
        /* printf("n: %d\n", n); */
        /* for (int k = 0; k < n; k++) */
        /* { */
        /*     printf("%d ",arr[k]); */
        /* } */
        /* printf("\n----------\n"); */


        if (arr[i] > arr[i + 1])
        {
            if (arr[i] < 10)
            {
                break;
            }
            int j;
            for (j = 0; j < i; j++)
            {
                prr[j] = arr[j];
            }
            prr[j+1] = arr[j] % 10;
            prr[j] = arr[j] / 10;
            for (int k = i + 1; k < n; k++)
            {
                prr[k + 1] = arr[k];
            }
            n += 1;

            if (i >= 1 && prr[i] < prr[i - 1])
            {
                i -= 2;
            }
            else
            {
                i -= 1;
            }
            for (j = 0; j < n; j++)
            {
                arr[j] = prr[j];
            }

            //debug
            /* printf("debug: i %d \n",i); */
            /* for (int k = 0; k < n; k++) */
            /* { */
            /*     printf("%d ",arr[k]); */
            /* } */
        }
        /* printf("\n"); */
    }

    int flag = 0;
    for (int i = 0;i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            flag = 1;
            break;
        }
    }

    if (flag == 0)
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }

}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
