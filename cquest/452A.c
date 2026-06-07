/*
 * File: 452A.c
 * Author: vididvidid 
 * Created: 2026-06-07 05:07:54
 */

#include <stdio.h>
#include <string.h>

int main()
{
    int n;
    char ptrn[10];

    scanf("%d", &n);
    scanf("%s", ptrn);

    const char *lst[] = {"vaporeon", "jolteon", "flareon", "espeon", "umbreon", "leafeon", "glaceon", "sylveon"};

    for (int i = 0; i < 8; i++)
    {
        if (strlen(lst[i]) == n) 
        {
            int match = 1;

            for (int j = 0; j < n ;j++)
            {
                if (ptrn[j] != '.' && ptrn[j] != lst[i][j]) {
                    match = 0;
                    break;
                }
            }

            if (match)
            {
                printf("%s\n",lst[i]);
                return 0;
            }
        }
    }

    return 0;
}
