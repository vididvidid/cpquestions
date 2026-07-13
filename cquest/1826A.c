/*
 * File: 1826A.c
 * Author: vididvidid 
 * Created: 2026-07-13 19:11:26
 */

/*
 * you are given an array L of size n. Find any integer x belongs [0,n] 
 * such that exactly x elements are striclty greater than x:
 *      sum(i = 1... n)(li > x) = x
 *  if no such x exists, output -1. 
 *
 *  Because n <= 100, check all x in O(n^2) or O(nlogn) after sorting.
 *
 *
 */

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    for (int i = 0; i <= n; i++)
    {
        int liar = 0;

        for (int j = 0; j < n; j++)
        {
            if (arr[j] > i)
            {
                liar++;
            }
        }        

        if (liar == i)
        {
            printf("%d\n",i);
            return;
        }
    }

    printf("-1\n");
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
