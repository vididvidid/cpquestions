/*
 * File: 509A.c
 * Author: vididvidid 
 * Created: 2026-04-14 10:00:08
 */

// nxn (n <= 10)
// first row and col == 1...
// and reamaingin sum of top and left..
// which means.. a[0][1..n] = 1, a[1..n][0] = 1
// a[x][y] = a[x-1][y] + a[x][y-1]  and x > 1 and y > 1
//
#include <stdio.h>
int a[10][10];

int main(){
    for (int i = 0; i < 10; i++) a[0][i] = 1;
    for (int i = 0; i < 10; i++) a[i][0] = 1;
    for (int i = 1; i < 10; i++){
        for (int j = 1; j < 10; j++){
            a[i][j] = a[i-1][j] + a[i][j-1];
        }
    }

    int n;
    scanf("%d",&n);
    printf("%d\n",a[n-1][n-1]);
    return 0;
    
}
