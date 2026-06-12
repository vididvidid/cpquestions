/*
 * File: 192B.c
 * Author: vididvidid 
 * Created: 2026-06-12 19:09:35
 */

#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    int a[1005];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&a[i]);
    }

    if (n == 1) {
        printf("%d\n", a[0]);
        return 0;
    }

    int ans = a[0];
    if (a[n - 1] < ans) {
        ans = a[n - 1];
    }

    for (int i = 0; i < n - 1; i++)
    {
        int day = (a[i] > a[i + 1]) ? a[i] : a[i + 1];

        if (day < ans) {
            ans = day;
        }
    }

    printf("%d\n", ans);
    return 0;
}
