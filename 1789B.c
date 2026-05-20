/*
 * File: 1789B.c
 * Author: vididvidid 
 * Created: 2026-04-23 04:22:33
 */

/*
 * check we can make the string palindrome with one operation.. 
 * selecting the range and changing there values from 0 to 1 and 1 to 0..
 *
 * so what i think is..
 * we should take the half of the string.. 
 * and check how many elements are same to the other half or not
 * which means..
 *
 * if there is a
 * same... not same... like this than print yes
 * not same.. same... print yes..
 * same... not same... same.. print yes
 * same... not same... same.. not same.. print no
 * not same.. same.. not same... print no..
 *
 * so we have to check if how many times we get same and not same..
 * 11->yes
 * 21->yes
 * 22->no
 * 12->no..
 *
 * if same == nosame == 1 than only yes
 * if same == 2 && nosame = 1 than only yes..
 * other wise all case no..
 */
#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    int l=0,r=0,mid=0;
    if (n%2 == 0) {
        l = n/2;
        r = n/2;
        mid = n/2;
    } else
    {
        l = (n-1)/2;
        r = (n-1)/2;
        mid = (n-1)/2+1;
    }
    char s[n+1],a[l+1],b[r+1];
    scanf("%s",s);
    for (int i = 0; i < l; i++)
    {
        a[i] = s[i];
    }
    a[l] = '\0';
    int y = n-1;
    for (int i = 0; i < r; i++)
    {
        b[i] = s[y--];
    }
    b[r] = '\0';

    /* printf("strings:\na: %s\nb: %s\n-----------\n",a,b); */
    int same = 0, notsame = 0;
    for (int i = 0,j = 0; i < l && j < r;)
    {
        int fs = 0, fns = 0;
        while (i< l && j < r && a[i] == b[j]) {
            fs = 1;
            i++;
            j++;
        }
        while (i < l && j < r && a[i] != b[j]) {
            fns = 1;
            i++;
            j++;
        }
        if (fs) same++;
        if (fns) notsame++;
    }
    /* printf("same: %d\nnotsame: %d\nxxxxxxxxxxxx\n",same, notsame); */

    if ((same == 0 && notsame == 1) ||
        (same == 1 && notsame == 0) ||
        (same == 1 && notsame == 1) ||
        (same > 1 && notsame <= 1))
    {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    /* printf("\n\n"); */
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
