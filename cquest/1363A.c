/*
 * File: 1363A.c
 * Author: vididvidid 
 * Created: 2026-07-16 14:42:18
 */

/*
 * given an array and x number find if there are x numbers whose sum is odd
 * n < 1000 can go bruteforce O(n^2)
 *
 * even + even = even
 * even + odd = odd (2 + 3 = 5)
 * odd + odd = even (5 + 5 = 10)
 *
 * so in x we need x/2 even and x/2 odd numbers.
 * x = 4
 * odd + even + odd + even = even
 * odd + odd + odd + odd = +
 * x = 5
 *
 * we can say total number odd numbers should be odd than it will be odd only.
 *
 */

#include <stdio.h>

void solve()
{
    int n, x;
    scanf("%d %d", &n, &x);
    int arr[n];
    int odd =0 ;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
        if (arr[i] % 2 != 0)
        {
            odd++;
        }
    }

    int even = n - odd;

    for (int k = 1; k <= x; k += 2)
    {
        if (k <= odd && x - k <= even)
        {
            printf("Yes\n");
            return;
        }
    }

    printf("No\n");
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
