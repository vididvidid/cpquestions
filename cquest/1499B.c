/*
 * File: 1499B.c
 * Author: vididvidid 
 * Created: 2026-05-31 17:02:45
 */

#include <stdio.h>
#include <string.h>

int sorted(char *s, int n)
{
    for (int i = 1; i < n; i++){
        if (s[i] < s[i - 1]){
            return 0;
        }
    }
    return 1;
}

void solve()
{
    char s[101];
    scanf("%s",s);
    int n = strlen(s);
    
    if(sorted(s,n)) {
        printf("YES\n");
        return;
    }

    int cnt1 = 0, cnt0 = 0, flag = 0;
    for (int i = 0; i < n; i++)
    {
       if ( i > 0 && s[i - 1] == '1' && s[i] == '1') cnt1++;
       else  if (i > 0 && s[i - 1] == '0' && s[i] == '0') 
       {
           if (cnt1 > 1) {
               cnt0++;
           }
       }
       else { 
           if (s[i] == '1'){
          if (cnt1 <= 1) 
           cnt1 = 1;
       } 
       else  if (s[i] == '0') {
           if (cnt1 > 1) 
           cnt0 = 1;
           
        }
       }
        
       if (cnt1 > 1 && cnt0 > 1) {
           printf("NO\n");
           return;
       }
       /* printf("\t%d %d\n",cnt0,cnt1); */
    }
     printf("YES\n");
    /* printf("%d %d %d\n",cnt1, cnt0, flag); */
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
