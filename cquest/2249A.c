/*
 * File: 2249A.c
 * Author: vididvidid 
 * Created: 2026-08-08 21:11:11
 */

/*
 * elements [1 .. n]
 * find max length of the subsequence such that ith element left rank and right
 * rank are not in range that is given.
 */

#include <stdio.h>

void solve()
{
    int lele = 0, n;
    scanf("%d", &n);
    int arr[n][4];
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d %d %d", &arr[i][0], &arr[i][1], &arr[i][2], &arr[i][3]);
    }

    int val = 0, idx = 0, ans = 0;
    // all length of subsegment
    for (int i = n; i > 0; i--)
    {
        int cn = 0, idx = 0;
        // all values that can be in subsegment
        for (int j = 1; j <=i; j++)
        {

           int lr = j;
           int rr = i - j + 1;
            while (idx < n)
            {

                if ((idx < n) &&
                        (lr < arr[idx][0] || lr > arr[idx][1] ) &&
                        (rr < arr[idx][2] || rr > arr[idx][3]))
                {
                    cn++;
                    idx++;
                    break;
                }

                idx++;
            }
        }

        if (cn == i)
        {
            ans = cn;
            break;
        }
    }
    
    printf("%d\n", ans);
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
