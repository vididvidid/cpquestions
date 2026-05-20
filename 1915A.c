/*
 * File: 1915A.c
 * Author: vididvidid 
 * Created: 2026-04-13 13:06:26
 */

// find the char in place ? what it would be and the row and col is filled 
// with 'ABC' 
// A + B + C  = 65 + 66 + 67 = 198 
//

#include <stdio.h>

void solve()
{
    char s[3][4];
    int res = 0;
    for (int i = 0; i < 3; i++){
        scanf("%s",s[i]);
        int sum = 0;
        for (int j = 0; j < 4; j++) {
            if (s[i][j] != '?')
                sum += s[i][j];
        }
        if (sum != 198 ){
            res = 198 - sum;
        }
    }

    printf("%c\n",(char)res);
    /* printf("-- debug --"); */
    /* for (int i = 0; i < 3; i++) printf("%s\n",s[i]); */
    /* printf("\n---------\n"); */

    
}

int main(){
    int t;
    scanf("%d",&t);
    while (t--)
    {
        solve();
    }
    return 0;
}
