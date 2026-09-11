/*
 * File: 1328B.c
 * Author: vididvidid 
 * Created: 2026-09-11 22:11:03
 */

/*
 * given string of length n ( n >= 3 && n <= 10^5 )
 * there are n - 2 character a's and other 2 character b
 * given all permuation possible with a and b in lexicographcially
 * you are given k and with that k you have to tell kth number of permutation
 *
 * ------------------------------------------------------------------
 *  Observation
 *  after 4th iter you can see.. no. of 'a' between b is the number of times we
 *  see the pattern.
 *  4 + 2 = 6 which means
 *  aaabaab(4) -> aaababa(5) -> aaabba(6)
 *  similary 7 + 3 = 10
 *  aaabaaab(5) -> aaabaaba(6) -> aaababaa(7) -> aaabbaaa(8)
 *
 *  so you will pattern 
 *  1-3 (0 'a' in between)
 *  4-6 (2 'a' in between)
 *  7-10 (3 'a' in between)
 *  11-15 (4 'a' in between)
 *  16-21 (5 'a' in between)
 *  ... 
 *  
 *  here with this if we are given n and k we can find 
 *  Number of a between b's (inside) = k - right boundary 
 *  Number of a after b's (outside) =
 *      right boundary - start value of that boundary - inside
 *  total length from first b to last char in string (lastLength) = 
 *      2 + inside + outside
 *  total length from start to first b (startLength)  =
 *      n - lastLength
 *
 *  so that table i have to precompute and store it
 *  1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21...
 *  3 3 3 6 6 6 10101010 15 15 15 15 15 21 21 21 21 21 21...
 *  so i thought to store all but constraint says k max can go 2 *10^9 which is
 *  too large..
 *
 *  so if you see 3, 6, 10, 15, 21 .. create a ap..
 *  which is n * (n + 1) /2.. 
 *
 *  so for given k we have to find the good n so that it can give us range the
 *  start boundary and right bounday like 4-6 this thing..
 *  so to find n we can do ceil(-1 + sqrt(1 + 8 * k)/2)
 *  than end is n * n+1/2 
 *  than start is n * n -1/2
 *
 */
#include <stdio.h>
#include <math.h>

#define int long long

void solve()
{
    char s[100010];

    int n, k;
    scanf("%lld %lld", &n, &k);
    int len = 0;

    if (k == 1)
    {
        for (int i = 0; i < n - 2; i++)
        {
            s[len++] = 'a';
        }
        s[len++] ='b';
        s[len++] = 'b';
        s[len++] = '\0';
        printf("%s\n",s);
        return;
    }

    if (k == 2)
    {

        for (int i = 0; i < n - 3; i++)
        {
            s[len++] = 'a';
        }
        s[len++] ='b';
        s[len++] = 'a';
        s[len++] = 'b';
        s[len++] = '\0';
        printf("%s\n",s);
        return;
    }

    if (k == 3)
    {

        for (int i = 0; i < n - 3; i++)
        {
            s[len++] = 'a';
        }
        s[len++] ='b';
        s[len++] = 'b';
        s[len++] = 'a';
        s[len++] = '\0';
        printf("%s\n",s);
        return;
    }

    if (k == ((n * (n - 1))/2)) 
    {
        s[len++] = 'b';
        s[len++] = 'b';
        for (int i = 0; i < n - 2; i++)
        {
            s[len++] = 'a';
        }
        s[len++] = '\0';
        printf("%s\n",s);
        return;
    }
    
    len = 0;
    int p = (int)ceil((sqrt(1.0 + 8.0 * k) - 1.0)/ 2.0);
    int end= (p * (p + 1)) / 2;
    int start = (p * (p - 1)) / 2 + 1;
    int inside = end - k;
    int outside = (end - start) - inside;
    int lastLength = 2 + inside + outside;
    int startLength = n - lastLength;
    /* printf("p:%d\n",p); */
    /* printf("start: %d\t end:%d\t inside:%d\t outside:%d\n",start,end,inside,outside); */

    for (int i = 0; i < startLength; i++)
    {
        s[len++] = 'a';
    }
    s[len++] = 'b';
    for (int i = 0; i < inside; i++)
    {
        s[len++] = 'a';
    }
    s[len++] = 'b';
    for (int i = 0; i < outside; i++)
    {
        s[len++] = 'a';
    }
    s[len++] = '\0';

    printf("%s\n",s);
}

signed main()
{
    int t;
    scanf("%lld",&t);
    while (t--)
    {
        solve();
    }

    return 0;
}
