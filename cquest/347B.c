/*
 * File: 347B.c
 * Author: vididvidid 
 * Created: 2026-07-07 19:17:56
 */


/*
 *
 * 0 1 2 3 4
 * 0 1 3 4 2
 *
 *   
 */

#include <stdio.h>

#define MAX(a,b) (a) > (b) ? (a) : (b)
void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    int cn = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        if (i == arr[i]) cn++;
    }


    if (cn == n)
    {
        printf("%d\n",n);
        return ;
    }

    int mv = 0;
    for (int i = 0; i < n; i++)
    {
        
        if (i != arr[i])
        {
            if (arr[arr[i]] == i)
            {
                mv = 1;
                break;
            }
        }
    }

    if (mv)
    {
        printf("%d\n", cn + 2);
    }
    else 
    {
        printf("%d\n", cn + 1);
    }

}

int main()
{
    solve();
    return 0;
}
