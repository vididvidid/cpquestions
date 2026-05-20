/*
 * File: 1788A.c
 * Author: vididvidid 
 * Created: 2026-04-13 09:35:11
 */

// given a[n] where n is 1 or 2
// find the index + 1 (k) so that muliple of {0 to k} = {k+1 to n}
// if not there print -1
//  2 2 1 2 1 2
// [2 4 4 8 8 16 ] -> prefix multiple
//[16 8 4 4 2 2 ]  -> suffix multiple
//    ^ ^          -> index 1 == index 2 so answer is index 1 print index+1 = 2
//
// 
//    1  2  1
//  [ 1  2  2  ]
//  [ 2  2  1  ]
//    ^  ^       
//
//    1  1  1  1
//  [ 1  1  1  1 ]
//  [ 1  1  1  1 ]
//    ^  ^
//    move right pointer till we have the same element and its not index 0
//    b/c we have to compare the index before that and present one..
//

#include <stdio.h>
#define int long long
void solve()
{
   int n;
   scanf("%lld",&n);
   int arr[n];
   for (int i = 0; i < n ; i++) scanf("%lld", &arr[i]);

   int parr[n],sarr[n];
   parr[0] = arr[0]==2 ? 1: 0;
   sarr[n-1] = arr[n-1]==2 ? 1: 0;
   for (int i = 1 ; i < n ; i++) parr[i] = parr[i-1] + (arr[i]==2? 1: 0);
   for (int i = n - 2; i >= 0; i--) sarr[i] = sarr[i + 1] + (arr[i]==2?1:0);

   /* printf("--- prefix Multiple Array --- \n"); */
   /* for (int i = 0; i < n ; i++ ) printf("%d ",parr[i]); */
   /* printf("\n"); */
   /* printf("---- suffix Multiple Array --- \n"); */
   /* for (int i = 0; i < n; i++ ) printf("%d ",sarr[i]); */
   /* printf("\n"); */

   /* int ptr = n - 1; */
   /* int split = -1; */

   /* while (ptr > 0) */
   /* { */
   /*    if (ptr > 0 && parr[ptr - 1] == sarr[ptr]) { */
   /*       split = ptr; */
   /*    } */
   /*    ptr--; */
   /* } */

   /* /1* printf("pointer is at %d  and split is %d \n", ptr, split); *1/ */

   /* printf("%lld\n",split); */
   int ptr = n - 1;
   while (parr[ptr - 1] != sarr[ptr]) ptr--;
   while (ptr > 0 && parr[ptr - 1] == sarr[ptr]) ptr--;

   /* printf("pointer is at %d \n", ptr); */

   if (parr[ptr] == sarr[ptr+1]) {
       printf("%lld\n",ptr+1);
   } else {
       printf("-1\n");
   }

}


signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }
    return 0;
}
