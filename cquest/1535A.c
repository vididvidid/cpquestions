/*
 * File: 1535A.c
 * Author: vididvidid 
 * Created: 2026-04-13 12:36:17
 */

// we have four numbers 
// max(a1 and a2)     max(a3 and a4)
//     |                 |
//     \                /
//      if last to max num == result i got from top than FAIR other wise no
//
//  i think if i sort it and create a two variable to store max two elements
//  and just simple if check
//  if (a1 == max1 || a1 == max2 && a2==max1 || a2 == max2) not fair
//  if (a3 == max1 || a3 == max2 && a4 == max1 || a4 == max2) not fair
//  else fair

#include <stdio.h>

void quick_sort(int *start, int *end)
{
    if (start >= end) return;
    int pivot = *(start + (end - start) / 2);
    int *low = start, *high = end;
    while (low <= high)
    {
        while (*low < pivot) low++;
        while (*high > pivot) high--;
        if (low <= high){
            int tmp = *low; *low = *high; *high = tmp;
            low++; high--;
        }
    }
    quick_sort(start, high);
    quick_sort(low, end);
}

void solve()
{
    int n = 4;
    int arr[4], tmp[4];
    for (int i = 0; i < 4; i++) scanf("%d",&arr[i]),tmp[i] = arr[i];
    
    quick_sort(tmp, tmp+3);
    /* printf("--- array ---\n"); */
    /* for (int i = 0; i < n ;i++) printf("%d ", arr[i]); */
    /* printf("\n"); */
    /* printf("--- sort ----\n"); */
    /* for (int i = 0; i <n ;i++) printf("%d ", tmp[i]); */
    /* printf("\n"); */
    if (((arr[0] == tmp[n-1] || arr[0] == tmp[n-2]) && 
        (arr[1] == tmp[n-1] || arr[1] == tmp[n-2])) ||
        ((arr[2] == tmp[n-1] || arr[2] == tmp[n-2]) &&
        (arr[3] == tmp[n-1] || arr[3] == tmp[n-2]))){
        printf("NO\n");
    } else {
        printf("YES\n");
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
