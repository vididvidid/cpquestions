/*
 * File: 2132A.c
 * Author: vididvidid 
 * Created: 2026-04-14 10:29:45
 */

#include <stdio.h>
#include <string.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char org[n];
    scanf("%s",org);
    int m;
    scanf("%d",&m);
    char add[m],play[m];
    int l=0,r=0;
    for (int i =0; i < m; i++) scanf(" %c",&add[i]);
    for (int i =0; i < m; i++) {
        scanf(" %c",&play[i]);
        if (play[i] == 'D') r++;
        else l++;
    }
    /* printf("\n---DEBUG ----\n"); */
    /* printf("org : %s\n",org); */
    /* printf("add : %s\n",add); */
    /* printf("play: %s\n",play); */

    char res[n+m+1];
    int idx =0;
    for (int i = 0; i < n+m; i++){
        if (i < l) res[i] = 'V';
        if (i >= n+l) res[i] = 'D';
        if (i >= l && i < n+l) res[i] = org[idx++];
    }
    res[n+m] = '\0';
    /* printf("res : %s\n",res); */
    /* printf("-------\n"); */
    for (int i = 0; i < m; i++){
        if (play[i] == 'D'){
            res[n+m-r] = add[i];
            r--;
        } else {
            res[--l] = add[i];
        }
    }
    printf("%s\n",res);
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
