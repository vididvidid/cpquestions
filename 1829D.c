/*
 * File: 1829D.c
 * Author: vididvidid 
 * Created: 2026-05-19 16:08:01
 */

/*
 * a number can be divided into a x and its 2x.. i.e x + 2x = number..
 * tell that if y will appear or not..
 *
 * 3x = number .. x/3.. 
 *
 *
 * 27 -> 9 and 27 
 * 9 -> 3 and 6 
 * 6 -> 2 and 4
 * 5 -> not possible
 * 4 -> not possible
 * 3 -> not possible
 * 2 -> not possible
 * 1 -> not possible
 *
 * n < m  => N/A
 * n == m => YES
 */

#include <stdio.h>
#include <string.h>

/* #define MAXN 10000001 */
/* int arr[MAXN]; */
/* int cn = 0; */
int flag = 0;

void  check (int n, int m)
{
    if ( flag == 1 || n <= 0 || n%3 != 0)
    {
        return;
    }
    
    int t = n / 3; 
        check(t,m);

    if (t == m) {
        printf("YES\n");
        flag = 1;
        return;
    }
        check(2 * t,m);

    if ((2 * t) == m) {
        printf("YES\n");
        flag = 1;
        return;
    }
}

void solve()
{
    flag = 0;
    int n, m;
    scanf("%d %d",&n, &m);

    if (n == m)
    {
        printf("YES\n");
        return;
    }

    if (n < m)
    {
        printf("NO\n");
        return;
    }
   
    check(n,m);
    if (flag == 0)
    {
        printf("NO\n");
    }
}

int main()
{
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
