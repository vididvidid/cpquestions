/*
 * File: 939A.c
 * Author: vididvidid 
 * Created: 2026-07-19 15:13:17
 */

/*
 * find if there any triangle is formed arr[i] => arr[arr[i]] => arr[arr[arr[i]]]
 *
 * n < 5000
 * 1 2 3 4 5
 * 2 4 5 1 3
 * 
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n + 1];
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }

    int tri = 0;
    for (int i = 1; i <= n; i++)
    {
        /*
         * i -> arr[i] -> arr[arr[i]] -> arr[arr[i]] = i
         */
        if (arr[arr[arr[i]]] == i)
        {
            tri = 1;
        }
    }

    if (tri)
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
    solve();
    return 0;
}
