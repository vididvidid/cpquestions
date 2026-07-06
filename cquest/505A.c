/*
 * File: 505A.c
 * Author: vididvidid 
 * Created: 2026-07-06 15:04:32
 */

#include <stdio.h>
#include <string.h>

int check (char *s, int start, int end)
{
    int cn = 0;
    while (start < end)
    {
        if (s[start] != s[end])
        {
            cn++;
        }
        start++;
        end--;
    }

    if (cn == 0)
    {
        return 0;
    }
    else {
        return cn;
    }
}
void solve()
{
    char s[12];
    scanf("%s", s);

    int n = strlen(s);
    /*
     * even and pallindrome -> print in middle any letter
     * even and not pallindrome -> ey -> eye
     * odd and pallindrome -> eye -> middle element repeat eyye
     * odd and not pallindrome -> aye -> 
     */
    
    int ck = check(s, 0, n - 1);
    if (!ck)
    {
        if (n % 2 == 0)
        {
            // add the char in between
            for (int i = 0; i < n/2; i++)
            {
                printf("%c",s[i]);
            }
            printf("y");
            for (int i = n/2; i < n; i++)
            {
                printf("%c",s[i]);
            }
            printf("\n");
        }
        else
        {
            // repeat the char in between
            for (int i = 0; i < n/2; i++)
            {
                printf("%c", s[i]);
            }
            printf("%c", s[n/2]);
            for (int i = n/2 ; i < n; i++)
            {
                printf("%c",s[i]);
            }
            printf("\n");
        }
    }
    else {
        //revive -> r at last
        //rviver -> e at second first
        //reiver -> v at third first
        //revivr -> e at second last
        //revier -> v at the third last
        //eviver -> r at the first

        for (int i = 0; i < n/2; i++)
        {
            if (s[i] != s[n - i - 1])
            {
                char opt1[13];
                char opt2[13];
                int idx;

                idx = 0;
                for (int j = 0; j < i; j++) opt1[idx++] = s[j];
                opt1[idx++] = s[n - i - 1];
                for (int j = i; j < n; j++) opt1[idx++] = s[j];
                opt1[idx] = '\0';

                idx = 0;
                for (int j = 0; j <= n - i - 1; j++) opt2[idx++] = s[j];
                opt2[idx++] = s[i];
                for (int j = n - i; j < n; j++) opt2[idx++] = s[j];
                opt2[idx] = '\0';

                if (check(opt1, 0, n) == 0)
                {
                    printf("%s\n",opt1);
                }
                else if (check(opt2, 0, n) == 0)
                {
                    printf("%s\n", opt2);
                }
                else
                {
                    printf("NA\n");
                }
                return;
            }
        }
    }

}

int main()
{
    solve();
    return 0;
}
