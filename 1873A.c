/*
 * File: 1873A.c
 * Author: vididvidid 
 * Created: 2026-04-12 08:48:35
 */

// permuatation of 3 digit number 3x3x3 = 18
// only 'cab' and 'bca' are two conditions where we cant' make 'abc'
// otherwise abc, acb, bac, cba 

// other approach i am thinking is if we use quickSort and add the counter
// in the swap.. if the counter in the swap exceed the 1 answer is no other
// wise its yes

#include <stdio.h>
#include <string.h>
int count = 0;
void quick_sort(char *start, char *end)
{
    if (start >= end) return;
    char pivot = *(start + (end - start) / 2);
    char *low = start, *high = end;

    while (low <= high)
    {
        while (*low < pivot) low++;
        while (*high > pivot) high--;

        if (low <= high){
            if (low != high)
            count++;
            char tmp = *low; *low = *high; *high = tmp;
            low++, high--;
        }
    }
    quick_sort(start, high);
    quick_sort(low, end);
}

void solve()
{
    char s[4];
    scanf("%s",s);
    count = 0;
    quick_sort(s, s+2);
    if (count <= 1){
        printf("YES\n");
    } else {
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
