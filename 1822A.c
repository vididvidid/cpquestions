/*
 * File: 1822A.c
 * Author: vididvidid 
 * Created: 2026-04-22 14:47:00
 */

/*
 * given two arrays lets say a and b.. find the a that fits in the k and 
 * have max b value..
 * and for every index of a value of a will be subtracted by -1
 *
 * so first do the -1 to all index from 2 to n 
 * than iterate over all a and check if all are inside the k limit.. if not 
 * mark them as -1.. and there b value to be -1..
 * than iterate over the b and find the max value..
 *
 */

#include <stdio.h>
#include <limits.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n,k;
    scanf("%d %d",&n,&k);
    int arr[n],brr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d",&arr[i]);
        /* if (i > 0) arr[i] -= i; */
        if (arr[i] > (k-i)) arr[i] = -1;
    }
    for (int i = 0; i < n; i++)
    {
        int c;
        scanf("%d",&c);
        if (arr[i] != -1)
            brr[i] = c;
        else 
            brr[i] = -1;
    }
    /* printf("---DEBUG---\n"); */ /* for (int i = 0; i < n; i++) printf("%d ",arr[i]); */
    /* printf("\n"); */
    /* for (int i = 0; i < n; i++) printf("%d ",brr[i]); */
    /* printf("\n"); */

    int w = INT_MIN;
    int ans = -2;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != -1){
            w = MAX(w, brr[i]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (brr[i] == w) {
            ans = i;
            break;
        }
    }
    printf("%d\n",ans+1);


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
