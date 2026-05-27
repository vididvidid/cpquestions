/*
 * File: 1732B.c
 * Author: vididvidid 
 * Created: 2026-05-09 06:43:05
 */

/*
 * make the string ascending by selecting i and than taking [i,n] and change if
 * it is 0 to 1 and viceversa
 *
 * 0    1   2   3   4   5   6
 * 0    1   0   1   0   1   0
 * .....^--------------------
 * 0    0   1   0   1   0   1
 * .........^----------------
 * 0    0   0   1   0   1   0
 * .............^------------
 * 0    0   0   0   1   0   1
 * .................^--------
 * 0    0   0   0   0   1   0
 * .....................^----
 * 0    0   0   0   0   0   1
 * XXXXXXXXXXXXXXXXXXXXXXXXXX => 5 operations
 *
 *
 * 0    1   2   3   4   5
 * 1    0   0   0   1   0
 * ^---------------------
 * 0    1   1   1   0   1
 * .....^----------------
 * 0    0   0   0   1   0
 * .................^----
 * 0    0   0   0   0   1
 * XXXXXXXXXXXXXXXXXXXXXX   => 3 opn
 *
 *
 * 0    1   2   3   4
 * 1    1   0   0   1
 * ^-----------------
 * 0    0   1   1   0
 * .........^--------
 * 0    0   0   0   1
 * XXXXXXXXXXXXXXXXXX   => 2 opn
 *
 * int ptr = 0, cnt = 0
 * while : ptr does not reach n-2
 *  => if (n == 1) print: 1; return
 *  => char k;
 *  => if (cnt % 2 == 0)
 *  => => k = s[ptr];
 *  => else 
 *  => => k = s[ptr] == '1' ? '0' : '1';
 *  => while (s[ptr] <= ch(ptr+1,s)) ptr++;
 *  => cnt++;
 */

#include <stdio.h>

char ch(int cn, char *s, int cnt)
{
    /* printf("DEBUG: cn-1: %d => %c && cn: %d => %c\n",cn-1,s[cn-1],cn,s[cn]); */
    if (cnt % 2  == 0) return s[cn];
    else return s[cn]=='1' ? '0' : '1';
}

void solve()
{
    int n;
    scanf("%d",&n);
    char s[n+1];
    scanf("%s",s);
    s[n] = '\0';

    int ptr = 0, cnt = 0;
    while (ptr < n - 1)
    {
        if ( n == 1 )
        {
            printf("1\n");
            return;
        }
        while ( (ptr + 1 ) < n && ch(ptr,s,cnt) <= ch(ptr+1,s,cnt))
            ptr++;
        /* printf("DEBUG: ptr: %d cnt: %d\n",ptr, cnt); */
        if (ptr >= n-1) break;
        cnt++;
    }
    /* if (s[n-2] > s[n-1]) cnt++; */

    printf("%d\n",cnt);
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
