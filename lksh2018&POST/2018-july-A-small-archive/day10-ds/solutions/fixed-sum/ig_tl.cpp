#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <list>
#include <time.h>
#include <math.h>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <iomanip>

using namespace std;

typedef long long ll;

mt19937 rnd(228);

const int N = 1e5 + 7;

int x[N], y[N], ind[N];
int cnt[N];

ll ans = 0;

void add_l(int i)
{
    if (y[i] != -1)
    {
        ans += cnt[y[i]];
    }
    cnt[ind[i]]++;
}

void del_l(int i)
{
    cnt[ind[i]]--;
    if (y[i] != -1)
    {
        ans -= cnt[y[i]];
    }
}

void add_r(int i)
{
    if (x[i] != -1)
    {
        ans += cnt[x[i]];
    }
    cnt[ind[i]]++;
}

void del_r(int i)
{
    cnt[ind[i]]--;
    if (x[i] != -1)
    {
        ans -= cnt[x[i]];
    }
}

int main()
{
#ifdef ONPC
    freopen("a.in", "r", stdin);
#endif
    int n, k;
    scanf("%d%d", &n, &k);
    vector <int> t(n);
    vector <int> a(n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &t[i]);
    }
    vector <ll> p(n + 1);
    ll sum = 0;
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
        sum += (t[i] == 1 ? a[i] : -a[i]);
        p[i + 1] = sum;
    }
    auto e = p;
    sort(e.begin(), e.end());
    e.resize(unique(e.begin(), e.end()) - e.begin());
    for (int i = 0; i <= n; i++)
    {
        ind[i] = lower_bound(e.begin(), e.end(), p[i]) - e.begin();
        x[i] = -1, y[i] = -1;
        int it = lower_bound(e.begin(), e.end(), p[i] + k) - e.begin();
        if (it != (int) e.size() && e[it] == p[i] + k)
        {
            y[i] = it;
        }
        it = lower_bound(e.begin(), e.end(), p[i] - k) - e.begin();
        if (it != (int) e.size() && e[it] == p[i] - k)
        {
            x[i] = it;
        }
    }
    int vl = 0, vr = 0;
    add_l(0);
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int l, r;
        scanf("%d%d", &l, &r);
        l--;
        while (vl > l)
        {
            vl--;
            add_l(vl);
        }
        while (vr < r)
        {
            vr++;
            add_r(vr);
        }
        while (vl < l)
        {
            del_l(vl);
            vl++;
        }
        while (vr > r)
        {
            del_r(vr);
            vr--;
        }
        printf("%lld\n", ans);
    }
}
