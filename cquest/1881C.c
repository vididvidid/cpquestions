/*
 * File: 1881C.c
 * Author: vididvidid 
 * Created: 2026-07-12 11:42:23
 */

/*
 * find min charc to change to make that matrix 90 deg transform similar
 *
 * min 2 x matrix.. containing lowercase alphabets  always even n
 * max n is 10^3. 
 *
 * each outer shell should be same..    
 *
 * row      col
 * 0,n-1    0,n-1
 * 1,n-2    1,n-2
 * ...      ...
 * ...      ...
 * till the diff becomes betwen two number == 1. because its even. 
 *
 * 0,n-1(4-1) => 0,3
 * 1,n-2(4-2) => 1,2
 *
 * find majority.. in those.. 
 * if all character frequency is 1 than add 3 for each index. otherwise n - freq
 * that is the number. 
 *
 * what i was wrong about..
 * -> i can only increament it i was decrementing it by using cn..
 * -> target must be the largest character 
 */

#include <stdio.h>
#include <string.h>

#define MAX(a,b) (a)>(b)?(a):(b)

void solve()
{
    int n;
    scanf("%d", &n);
    char s[n][n + 1];
    for (int i = 0; i < n; i++)
    {
        scanf("%s", s[i]);
    }

    int ans = 0;
    // iterate to outer shells
    for (int i = 0, j = n - 1; i < n && i < j && j > i && j >= 0; i++, j--)
    {
       /* printf("\ni: %d j: %d\n",i,j); */ 

       int len = j - i + 1;
       char top[len + 1];
       char bottom[len + 1];
       char left[len + 1];
       char right[len + 1];

       for (int k = 0; k < len; k++)
       {
           top[k] = s[i][i + k];
           bottom[k] = s[j][j - k];
           left[k] = s[j - k][i];
           right[k] = s[i + k][j];

           /* printf("%c %c %c %c\n",top[k],bottom[k],left[k],right[k]); */
       }

       for (int k = 0; k < len - 1; k++)
       {

           char mxchar = top[k];
           if (bottom[k] > mxchar) mxchar = bottom[k];
           if (left[k] > mxchar) mxchar = left[k];
           if (right[k] > mxchar) mxchar = right[k];

           ans += (mxchar - top[k]);
           ans += (mxchar - bottom[k]);
           ans += (mxchar - left[k]);
           ans += (mxchar - right[k]);
       }
       
    }

    printf("%d\n",ans);
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
