/*
 * File: 1520A.c
 * Author: vididvidid 
 * Created: 2026-04-13 09:10:59
 */

// input <- {string}n
// no character in a string can appear again.. it can appears in only continous
// order.. 
// DDBBCCCBBEZ
//    ^    ^  -> no return NO and break;
// ABC -> after the loop get out and print YES
// loop s[0] --> s[n]
//    pointer1 = while (s[i] == s[i+1]) i++;
//    loop s[n]--> s[i+1]
//        if same character --> flag = True and break;
// if flag => print(NO)
// else print(YES)
//
//  AAAA
//  0123 [4]
//    *
//     ^

#include <stdio.h>

void solve()
{
    int n;
    scanf("%d",&n);
    char s[n];
    for (int i = 0; i < n ;i++) scanf(" %c", &s[i]);
    
    int flag = 0;

    for (int i = 0; i < n ;)
    {
       while (i <= n - 2 && s[i] == s[i+1]) i++; 
       if (i < n)
       for (int j = n - 1; j > i; j-- )
       {
           if (s[j] == s[i])
           {
            flag = 1;
            break;
           }
       }
       if ( i < n )
       i++;
    }

    if (flag)
    {
        printf("NO\n");
    } else 
    {
        printf("YES\n");
    }
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
