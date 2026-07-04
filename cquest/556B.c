/*
 * File: 556B.c
 * Author: vididvidid 
 * Created: 2026-07-04 19:01:59
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);

    int arr[1005];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);

    }

    int step = (n - arr[0]) % n;

    for (int i = 0; i < n; i++)
    {
        int fp;
        if (i % 2 == 0)
        {
            fp = (arr[i] + step) % n;
        }
        else {
            fp = (arr[i] - step) % n;
            if (fp < 0){
                fp += n;
            }
        }

        if (fp != i) {
            printf("No\n");
            return;
        }
    }

    printf("Yes\n");
}

int main()
{
    solve();
    return 0;
}
