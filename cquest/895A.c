/*
 * File: 895A.c
 * Author: vididvidid 
 * Created: 2026-07-17 06:30:43
 */

/*
 * pizza in n pieces.
 * ith piece -> sector of an angle equal to ai.
 * divide all pieces -> two continous sectors -> diff(angle of sectors) -> min
 * sector angle is sum of angles of all piece in it.
 * one sectors can be empty
 *
 */
#include <stdio.h>
#include <limits.h>

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define ABS(a) ((a)>0?(a):-1*(a))


void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }

    int ans = 360;
    for (int i = 0; i < n; i++)
    {
       int sum = 0;
       for (int j = 0; j < n; j++)
       {
           sum += arr[(i + j) % n];
           ans = MIN(ans, ABS(360 - 2 * sum));
       }
    }

    ans = MIN(ans, 360);
    printf("%d\n", ans);
}

int main()
{
    solve();
    return 0;
}
