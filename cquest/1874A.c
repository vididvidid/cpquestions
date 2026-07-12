/*
 * File: 1874A.c
 * Author: vididvidid 
 * Created: 2026-07-12 14:26:43
 */

/*
 * find the maximum sum after k swaps 
 *
 */

#include <stdio.h>

void qsort(int *start, int *end)
{
    if (start >= end) return;
    int mid = *(start + (end - start) / 2);
    int *low = start, *high = end;
    while (low <= high)
    {
        while (*low < mid) low++;
        while (*high > mid) high--;
        if (low <= high)
        {
            int tmp = *low; *low = *high; *high = tmp;
            low++; high--;
        }
    }

    qsort(start, high);
    qsort(low, end);
}

void solve(){
    int n, m, k;
    scanf("%lld %lld %lld", &n, &m , &k);
    int arr[n], prr[m];
    int suma = 0, sump = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", arr[i]);
        suma += arr[i];
    }

    for (int i = 0; i < m; i++)
    {
        scanf("%lld", prr[i]);
        sump += prr[i];
    }

    qsort(arr, arr + n - 1);
    qsort(prr, prr + m - 1);
    
    int sumak = 0, sumpk = 0, sumaak = 0;
    for (int i = 0; i < k; i++)
    {
        sumak += arr[i];
        sumpk += prr[i];
    }

    for (int i = k; i < n; i++)
    {
        sumaak += arr[i];
    }

    if (suma > sump)
    {
        printf("0\n");
        return;
    }
    else{
       printf("%lld\n", sumaak + sumpk); 
       return;
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

