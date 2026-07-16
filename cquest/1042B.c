/*
 * File: 1042B.c
 * Author: vididvidid 
 * Created: 2026-07-16 19:05:54
 */

/*
 * n kind of juices
 * each juice price is ci
 * each juice contain vitamin (A or B or C)
 * return minimum price of juice wiht all three vitamins
 *
 * can i write a sort function for my custom struct that is based on string
 * length and price
 * the comparator
 * it was nice writing the sort function for my struct
 *
 * now question is to find min value..
 * so take all single character..
 * so take 2 character + one single character
 * so take all 3 character.. 
 *
 *
 */
#include <stdio.h>
#include <string.h>

#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct
{
    int price;
    char s[4];
} juice;

int compare( juice a, juice b )
{
    int len1 = strlen(a.s);
    int len2 = strlen(b.s);

    if (len1 != len2)
        return len1 - len2;

    if (a.price != b.price)
        return a.price - b.price;

    return strcmp(a.s, b.s);
}

void swap(juice *a, juice *b)
{
    juice temp = *a;
    *a = *b;
    *b = temp;
}

void sort(juice arr[], int start, int end)
{
    if (start >= end) return;
    juice  mid = arr[(start + (end - start) / 2)];
    int low = start, high = end;
    while (low <= high)
    {
        while (compare(arr[low], mid) < 0) low++;
        while (compare(arr[high], mid) > 0) high--;
        if (low <= high)
        {
            swap(&arr[low], &arr[high]);
            low++; high--;
        }
    }

    sort(arr, low, end);
    sort(arr, start, high);
}

void solve()
{
    int n;
    scanf("%d", &n);
    juice lst[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d%s", &lst[i].price, lst[i].s);
    }

    sort(lst, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d : %s\n", lst[i].price, lst[i].s);
    }
    
}

int main()
{
    solve();
    return 0;
}
