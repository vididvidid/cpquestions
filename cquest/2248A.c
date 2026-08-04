/*
 * File: 2248A.c
 * Author: vididvidid 
 * Created: 2026-08-04 20:42:38
 */

#include <stdio.h>

int main() {
    int t, i, z, o;
    char s[105];
    scanf("%d", &t);
    while (t--) {
        scanf("%s", s);
        z = o = 0;
        for (i = 0; s[i]; i++) {
            if (!z && s[i] == '0') z = 1;
            else if (!o && s[i] == '1') o = 1;
            else putchar(s[i]);
        }
        putchar('\n');
    }
    return 0;
}
