/*
 * File: 2275D.c
 * Author: vididvidid 
 * Created: 2026-10-29 03:54:34
 */

/*
 * Each lab's sum changes by -1, 0, or +1 per action. Spend at most k actions
 * in total so that the smallest lab sum is as large as possible
 * -> order is fixed: (a,b,c) and each rules uses "earlier -later"
 * -> an action can make the sum go down (sgn = -1)
 * -> sgn(0) = 0
 * -> At most k
 * -> k <= 10^18 and sums up to 3.10^9
 *
 */

#include <stdio.h>

typedef long long ll;

#define MAXN 200005

static ll sum_[MAXN];
static ll extra[MAXN];
static int frozen[MAXN];
static int n;
static ll k;

static int feasible(ll S) {
    ll total = 0;
    for (int i = 0; i < n; i++)
    {
        ll d = S - sum_[i];
        if (d <= 0) continue;
        if (frozen[i]) return 0;
        total += d + extra[i];
        if (total > k) return 0;
    }

    return 1;
}

void solve() {
    scanf("%d %lld", &n, &k);
    ll lo = 0;
    for (int i = 0; i < n; i++)
    {
        ll a, b, c;
        scanf("%lld %lld %lld", &a, &b, &c);
        sum_[i] = a + b + c;
        frozen[i] = 0;
        extra[i] = 0;
        if (a <= b && b <= c)
        {
            if (a == c) 
            {
                frozen[i] = 1;
            } else {
                ll g = (b - a < c - b ? b - a: c - b) + 1;
                extra[i] = 2 *g;
            }
        }

        if (i == 0 || sum_[i] < lo) lo = sum_[i];
    }

    ll hi = lo + k;
    while (lo < hi) {
        ll mid = lo + (hi - lo + 1) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid - 1;
    }

    printf("%lld\n", lo);
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
