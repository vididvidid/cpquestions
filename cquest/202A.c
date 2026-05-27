/*
 * File: 202A.c
 * Author: vididvidid 
 * Created: 2026-04-26 09:46:03
 */

#include <stdio.h>

int main()
{
    int arr[26] = {0};
    char s[11];
    scanf("%s",s);
    for (char *i = s; *i != '\0'; i++) {
        char c = *i;
        arr[(int)(c-'a')]++;
    }
    int r = 25;
    while (arr[r] == 0) r--;
    while (arr[r] != 0) {
        printf("%c",r+'a');
        arr[r]--;
    }
    printf("\n");
    return 0;
}
