/*
 * File: 1559C.c
 * Author: vididvidid 
 * Created: 2026-07-21 20:13:58
 */

/*
 * n + 1 villages and 2n - 1 roads in the city
 * 2 types of roads
 * -> n - 1 roads are from village i to i + 1, for all 1 <= i <= n-1
 * -> n roads -> sequence -> a1 .. an
 *    if ai = 0 => ith road goes from village i -> village n + 1
 *       ai != 0 => village n + 1 to i
 *
 * visit every village once
 *
 */
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }

    if (arr[1] == 1)
    {
        printf("%d ", n + 1);
        for (int i = 1; i <= n; i++) printf("%d ", i);
        printf("\n");
        return;
    }

    if (arr[n] == 0)
    {
        for (int i = 1; i <= n; i++) printf("%d ", i);
        printf("%d\n", n + 1);
        return;
    }

    int mid = 0;
    for (int i = 1; i < n; i++)
    {
        if (arr[i] == 0 && arr[i + 1] == 1)
        {
            mid = i;
            break;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        printf("%d ", i);
        if (i == mid)
        {
            printf("%d ", n + 1);
        }


    }
    printf("\n");

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
