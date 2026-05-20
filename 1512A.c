/*
 * File: 1512A.c
 * Author: vididvidid 
 * Created: 2026-04-12 07:41:46
 */

// there is only one element that is not same.
// while taking the input keep track of count which number appeared more than
// once.. 
// use the counting sort.. and the array it creates iterate over that
// and find which element have count = 1 and loop over the array and get the 
// index
//

#include <stdio.h>
#define MAX_VAL 101
int count_arr[MAX_VAL];

void solve()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    // count_arr
    for (int i = 0; i <= MAX_VAL; i++) count_arr[i] = 0;
    for (int i = 0; i < n; i++) count_arr[arr[i]]++;

    int unq = 0;
    for (int i = 0; i <= MAX_VAL; i++) if (count_arr[i]==1) unq = i;

    int idx = 0;
    for (int i = 0; i < n; i++) if (arr[i] == unq) idx = i;

    printf("%d\n",idx + 1);
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
