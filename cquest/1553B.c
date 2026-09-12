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
    char s[510], t[1010];
    scanf("%s %s", s, t);
    int sl = strlen(s);
    int tl = strlen(t);

    for (int start = 0; start < sl; start++)
    {
        for (int len_right = 0; len_right < tl; len_right++)
        {
            int curr = start;
            bool possible = true;

            for (int i = 0; i <= len_right; i++)
            {
                if (i == 0)
                {
                    if (s[curr] != t[0])
                    {
                        possible = false;
                        break;
                    }
                }
                else {
                    curr++;
                    if (curr >= sl || s[curr] != t[i]) 
                    {
                        possible = false;
                        break;
                    }
                }
            }

            if (!possible) continue;

            for (int i = len_right + 1; i < tl; i++)
            {
                curr--;
                if (curr < 0 || s[curr] != t[i]) {
                    possible = false;
                    break;
                }
            }

            if (possible) {
                printf("YES\n");
                return;
            }
        }
    }

    printf("NO\n");
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
