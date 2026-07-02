/*
 * File: 869A.c
 * Author: vididvidid 
 * Created: 2026-07-02 15:12:33
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n], prr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    for (int i = 0; i < n; i++) scanf("%d", &prr[i]);

    if (n  == 1)
    {
        if (arr[0] != 0 && arr[0] % 2 == 0) 
        {
            printf("Koyomi\n");
        }
        else {
            printf("Karen\n");
        }
        return;
    }

    int ca = 0, cb = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            int num = arr[i] ^ prr[j];
            for (int k = 0; k < n; k++)
            {
                if (num == arr[k])
                {
                    ca++;
                    break;
                }
                if (num == prr[k])
                {
                    cb++;
                    break;
                }        
            }
        }
    }
    
    /* printf("%d %d\n",ca,cb); */
   
    if (ca != 0 && ca % 2 == 0)
    {
        printf("Koyomi\n");
    }
    if (cb != 0 && cb % 2 == 0)
    {
        printf("Karen\n");
    }
}

int main()
{
    solve();
    return 0;
}
