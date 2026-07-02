/*
 * File: 869A.c
 * Author: vididvidid 
 * Created: 2026-07-02 15:12:33
 */

#include <stdio.h>
int trr[2000005];
void solve()
{
    int n;
    scanf("%d",&n);
    int arr[n], prr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]), trr[arr[i]] = 1;
    for (int i = 0; i < n; i++) scanf("%d", &prr[i]), trr[prr[i]] = 1;

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0 ;j < n; j++)
        {
            int val = arr[i] ^ prr[j];
            if (val <= 2000000 && trr[val])
            {
                cnt++;
            }
        }
    }

    printf(cnt % 2 ? "Koyomi\n" : "Karen\n");
}

int main()
{
    solve();
    return 0;
}
