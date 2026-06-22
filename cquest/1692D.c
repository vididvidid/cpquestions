/*
 * File: 1692D.c
 * Author: vididvidid 
 * Created: 2026-06-22 13:05:36
 */

#include <stdio.h>

void solve()
{
    int h, m, k;
    scanf("%d:%d %d",&h, &m, &k);

    int km, kh;
    kh = k / 60;
    km = k % 60;

    int sh = h, sm = m, frun = 1;

    int ans = 0;

    while (frun || h != sh || m != sm)
    {
        frun = 0;

        int tm = m + km;
        int eh = tm / 60;
        m = tm % 60;

        int th = h + kh + eh;
        h = th % 24;

        /* printf("%02d:%02d\t",h, m); */
        if (((h/10) == (m % 10)) && ((h%10) == (m/10))) {
            ans++;
        }
    }        
    printf("%d\n",ans);
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
