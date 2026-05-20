/*
 * File: 1709A.c
 * Author: vididvidid 
 * Created: 2026-04-21 08:24:26
 */

// given a value to you, and your task is to go through all the gates 1,2,3
// if you can than print yes if not than print no
//
// 3
// 0 1 2
//
// so he goes to gate 3 -> find the 2
// than he goes to gate 2 -> find the 1
// than he goes to gate 1 -> find the 0.. all three gates..opened
//
//
// 1
// 0 3 2
// so he goes to gate 1 -> find the 0.. 
// now he don't know which gate to go.. 
//
// [ x, k, k, k ]
//   0  1  2  3    
// >          Y
// >       Y
// >    Y       

#include <stdio.h>

void solve()
{
    int x;
    scanf("%d", &x);
    int arr[4];
    for (int i = 1; i < 4; i++) scanf("%d",&arr[i]);

    int k = arr[x];
    arr[x] = -1;
    x = k;
    k = arr[x];
    arr[x] = -1;
    x = k;
    k = arr[x];
    arr[x] = -1;
    x = k;

    int sum = 0;
    for (int i = 1; i < 4; i++) sum += arr[i];

    if (sum == -3)
    {
        printf("YES\n");
    } else
    {
        printf("NO\n");
    }

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
