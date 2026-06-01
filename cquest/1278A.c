/*
 * File: 1278A.c
 * Author: vididvidid 
 * Created: 2026-06-01 12:30:26
 */

/*
 * find if the string s exists in any permuation in the string h.
 *
 * if len(s) > len(h) => NO
 * if len(s) == len(h) => freq(s) == freq(h) => YES
 * else => NO
 *
 * if len(s) > len(h) =>
 * extra is 4.. 40 04 13 22 31 .. 
 *
 *       -------------
 * 1 2 3 4 5 6 7 8 9 10 11 12 13
 * z y x a a b c a a b  k  j  h
 *             ^                  ext = 6: i = 0, ext - i = 6, 13 - 6 = 7
 * ^-------------^                i = 1 ,  ext - i = 5 , 13 - 5 = 8
 *   ^-------------^              i = 2 ,  ext - i = 4 , 13 - 4 = 9
 *     ^-------------^            i = 3 ,  ext - i = 3 , 13 - 3 = 10
 *       ^--------------^         i = 4 ,  ext - i = 2 , 13 - 2 = 11
 *         ^---------------^      i = 5 ,  ext - i = 1 , 13 - 1 = 12
 *           ^---------------^    i = 6 ,  ext - i = 0 , 13 - 0 = 13
 *
 *
 */
#include <stdio.h>
#include <string.h>

int chk (char *s, char *h, int ns, int sh)
{
    int arr[26] = {0}, brr[26] = {0};
    for (int i = 1; i <= ns; i++) {
        arr[s[i] - 'a']++;
    }
    for (int i = sh; i < sh + ns; i++) {
        brr[h[i] - 'a']++;
    }
    for (int i = 0; i < 26; i++)
    {
        if (arr[i] != brr[i]) {
            return 0;
        }
    }

    return 1;
}

void solve() 
{
    char s[102], h[102];
    scanf("%s",&s[1]);
    scanf("%s",&h[1]);
    /* scanf("%s %s", &s[1], &h[1]); */
    int ns = strlen(&s[1]);
    int nh = strlen(&h[1]);

    if (ns > nh) {
        printf("NO\n");
        return;
    }

    int ext = nh - ns;
    /* printf("s: %s \nh: %s\n",&s[1], &h[1]); */
    /* printf("s: %d and h: %d\n",ns, nh); */
    for (int i = 1; i <= ext + 1; i++)
    {
        /* tem = [from start remove ith char] + [from end remove nh - ext - i char]; */

        if (chk(s, h, ns, i))
        {
            printf("YES\n");
            return;
        }
    }

    printf("NO\n");
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
