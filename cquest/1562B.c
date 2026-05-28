/*
 * File: 1562B.c
 * Author: vididvidid 
 * Created: 2026-05-28 12:57:26
 */

#include <stdio.h>
#include <string.h>

int is_prime(int num)
{
    if (num <= 1) return 0;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void solve()
{
    int n;
    scanf("%d",&n);
    char s[51];
    scanf("%s",s);

    char *m = strpbrk(s,"14689");
    if (m)
    {
        printf("1\n");
        printf("%c\n",*m);
    }
    else{
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++)
            {
                int num = (s[i] - '0') * 10 + (s[j] - '0');
                if (!is_prime(num))
                {
                    printf("2\n%d\n",num);
                    return;
                }
            }
        }
    }
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
