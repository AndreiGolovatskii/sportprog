#include <set>
#include <cstdio>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <math.h>
#include <random>
#include <algorithm>
#include <cassert>
#include <cstring>
#include <list>
#include <bitset>
#include <deque>
#include <complex>
#include <cmath>


using namespace std;
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>
const int MN = 1e5 + 33;
const ll INF = 1e8 * 1e8 + 100;
pii s[MN], a[MN], r[MN];
pii s2[MN], a2[MN];

bool operator<(const pii &a, const pii &b) {
    return a.y == b.y ? a.x < b.x : a.y < b.y;
}

istream &operator>>(istream &cin, pii &a) {
    cin >> a.x >> a.y;
    return cin;
}

ll cr(const pii &a, const  pii &b) {
    ll r = a.x * (ll)b.y - a.y  * (ll)b.x;
    return r;
}
pii operator-(pii a, pii b) {
    return {a.x - b.x, a.y - b.y};
}
pii operator+(pii a, pii b) {
    return {a.x + b.x, a.y + b.y};
}

pii buff[MN];
void nrm(pii in[], int n) {
    int mp = 0;
    for (int i = 0; i < n; ++i) {
        if(in[i] < in[mp]) {
            mp = i;
        }
    }
    
    rotate(in, in + mp, in + n);
    in[n] = in[0];
}

ll lq(pii a) {
    return a.x * (ll)a.x + a.y * (ll)a.y;
}

ld gv(pii a, pii b) {
    if(lq(a) + lq(a - b) > lq(b) && lq(b) + lq(a - b) > lq(a)) {
        return abs((ld)cr(a, b)) / hypot(a.x - b.x, a.y - b.y);
    }
    return min(hypot(a.x, a.y), hypot(b.x, b.y));
}

bool cmp(const pii &a, const pii &b) {
    return cr(a, b) > 0;
}

int32_t main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    nrm(s, n);
    pii s1 = s[0];
    for(int i = 0; i < n; ++i) {
        s2[i] = s[i + 1] - s[i];
    }
    
    for(int i = 0; i < m; ++i) {
        cin >> a[i];
        a[i] = make_pair(0, 0) - a[i];
    }
    nrm(a, m);
    
    pii a1 = a[0];
    for(int i = 0; i < m; ++i) {
        a2[i] = a[i + 1] - a[i];
    }
    
    pii r2 = s1 + a1;
    merge(s2, s2 + n, a2, a2 + m, r, cmp);
    
    ld ans = INF;
    for(int i = 0; i < n + m; ++i) {
        //        cerr << r2.x << " " << r2.y << "\n";
        ans = min(ans, gv(r2, r2 + r[i]));
        r2 = r2 + r[i];
    }
    cout.precision(10);
    cout << fixed;
    cout << max(ans - 60, (ld)0);
}
