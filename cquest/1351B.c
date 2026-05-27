/*
 * File: 1351B.c
 * Author: vididvidid 
 * Created: 2026-05-11 02:41:36
 */

#include <stdio.h>

void solve()
{
    int a,b,c,d;
    scanf("%d %d %d %d",&a,&b,&c,&d);
    int arr[101] = {0},brr[101] = {0};
    arr[a]++;
    arr[b]++;
    brr[c]++;
    brr[d]++;

    int sum = 0, mark = 0;
    for (int i = 101; i >= 0; i--)
    {
        if (arr[i] == 1  && brr[i] == 1 && !mark)
        {
            mark = i;
        }
        else if ( !mark && ( (arr[i] == 1 && brr[i] == 0)||
                 (arr[i] == 0 && brr[i] == 1))) {
            /* printf("%d %d %d\n",arr[i],brr[i],mark); */
            printf("NO\n");
            return;
        }
        if (mark != i  && (arr[i] == 1 || brr[i] == 1))
        {
            if (arr[i] == 1 && brr[i] == 1) sum = i + i;
            else sum += i;
        }
    }
    /* printf("DEBUG: mark = %d and sum = %d\n",mark,sum); */
    if (sum == mark && mark != 0 && sum != 0) printf("YES\n");
    else printf("NO\n");
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
