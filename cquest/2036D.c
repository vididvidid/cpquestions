/*
 * File: 2036D.c
 * Author: vididvidid 
 * Created: 2026-08-13 11:59:33
 */

/*
 * given an 2d array of n, m (n and m are even)
 * you have to traverese layer by layer outer layers
 * and check if we can make 1543 as a number and return counts.
 *
 */

#include <stdio.h>

#define MIN(a,b) (a)<(b)?(a):(b);

void process(int* a, int* b, int* c, int* d, int* isfill, int* cnt, char* val)
{
    int num = (int) (*val - '0');

    if (*isfill)
    {
        *a = *b;
        *b = *c;
        *c = *d;
        *d = num;

        if (*a == 1 && *b == 5 && *c == 4 && *d == 3) *cnt = *cnt +1;
    }
    else
    {
        if (*a == -1)
        {
            *a = num;
        }
        else if (*b == -1)
        {
            *b = num; 
        }
        else if (*c == -1)
        {
            *c = num; 
        }
        else if (*d == -1)
        {
            *d = num; 
        }
    }

    if(*d != -1 && *isfill == 0)
    {
        if (*a == 1 && *b == 5 && *c == 4 && *d == 3) *cnt = *cnt +1;
        *isfill = 1;
    }
    /* printf("D:\t a: %d b: %d c: %d d: %d and cnt: %d\n",*a,*b,*c,*d,*cnt); */
}

void solve()
{
    int n, m;
    scanf("%d %d", &n, &m);
    char arr[n+1][m+1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", arr[i]);
    }
    int a = -1, b = -1, c = -1, d = -1;
    int cnt = 0, isfill = 0;
    int layers = MIN(n,m);


    for (int i = 0; i < (layers / 2); i++)
    {
        int steps = 2 * ((n - (2*i)) + (m - (2*i)) - 2);
        steps += 3;
        a = -1, b = -1, c = -1, d = -1, isfill = 0;

        while (steps > 0)
        {

            for (int j = 0 + i; j < m - i  && steps > 0 ; j++, steps--)
            { 
                process( &a, &b, &c, &d, &isfill, &cnt, &arr[i][j]);
            }
            for (int j = 1 + i; j < n - i && steps > 0; j++, steps--)
            {
                process( &a, &b, &c, &d, &isfill, &cnt, &arr[j][m - i - 1]);
            }
            for (int j = m - 2 - i; j >= 0 + i && steps > 0; j--, steps--)
            {
                process( &a, &b, &c, &d, &isfill, &cnt, &arr[n - i- 1][j]);
            }
            for (int j = n - 2 - i; j > 0 + i && steps > 0; j--, steps--)
            {
                process( &a, &b, &c, &d, &isfill, &cnt, &arr[j][i]);
            }

        }
    }



    printf("%d\n",cnt);
}

signed main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
