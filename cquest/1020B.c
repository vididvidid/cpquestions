/*
 * File: 1020B.c
 * Author: vididvidid 
 * Created: 2026-07-20 03:06:15
 */

/*
 * given n array where each index are pointing to some other index.. tell in
 * order how many will have 2nd time visit.. 
 *
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n + 1], vrr[n + 1];
    arr[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 1; i <= n; i++)
    {
        memset(vrr, 0, sizeof(vrr));

        int curr = i;
        while (vrr[curr] == 0)
        {
            vrr[curr] = 1;
            curr = arr[curr];
        }
        
        printf("%d ", curr);
    }
    printf("\n");
}

int main()
{
    solve();
    return 0;
}
