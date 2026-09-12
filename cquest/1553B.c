/*
 * File: 1553B.c
 * Author: vididvidid 
 * Created: 2026-09-12 13:37:03
 */

/*
 * simulate
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define int long long

bool checkRightTarget(int chip, int tl)
{
    if ((chip + 1) < tl)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkRightString(int curr, int sl)
{
    if ((curr + 1) < sl)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkLeftTarget(int chip, int tl)
{
    if ((chip - 1) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool checkLeftString(int curr, int sl)
{
    if ((curr - 1) >= 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void solve()
{
    char s[510], t[510];
    scanf("%s %s", s, t);
    int sl = strlen(s);
    int tl = strlen(t);

    for (int i = 0; i < sl; i++)
    {
        if (s[i] == t[0])
        {
            int chip = 0, first = 1, curr = i, flag = 1;
            while (chip != (tl - 1))
            {
                if (first)
                {
                    if (checkRightTarget(chip, tl) &&
                            checkRightString(curr, sl) &&
                            s[curr+1] == t[chip+1])
                    {
                        /* printf("%c:%c\t",s[curr+1],t[chip+1]); */
                        curr++;
                        first = 0;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }
                else
                {
                    if (checkRightTarget(chip, tl) &&
                            checkRightString(curr, sl) &&
                            s[curr+1] == t[chip+1])
                    {
                        /* printf("%c:%c\t",s[curr+1],t[chip+1]); */
                        curr++;
                    }
                    else if (checkLeftTarget(chip, tl) &&
                            checkLeftString(curr, sl) &&
                            s[curr-1] == t[chip+1])
                    {
                        /* printf("%c:%c\t",s[curr-1],t[chip+1]); */
                        curr--;
                    }
                    else
                    {
                        flag = 0;
                        break;
                    }
                }

                chip++;
            }

            if (flag)
            {
                printf("YES\n");
                return;
            }
        }
    }
    printf("NO\n");
    return;
}


signed main()
{
    int t;
    scanf("%lld", &t);
    while (t--)
    {
        solve();
    }

    return 0;
}
