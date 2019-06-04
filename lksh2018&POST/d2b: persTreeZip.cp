#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>

const int MN = 450 * 1000 + 17;
int globr = 0;
struct node{
    int v;
    int cl, cr;
    node(int v): v(v){}
    node(){cl = cr = 0; v = 0;};
};
node vertex[30 * MN];

int build(int l, int r){
    int root = globr++;
    if(l == r) return root;
    vertex[root].cl = build(l, (l + r) / 2);
    vertex[root].cr = build((l + r) / 2 + 1, r);
    
    return root;
}

int ch(int root, int l, int r, int pos, int nv) {
    if(pos < l || pos > r) {
        return root;
    }
    if(l == r){
        int nroot = globr++;
        vertex[nroot].v = nv;
        return nroot;
    }
    int nroot = globr++;
    vertex[nroot].cl = ch(vertex[root].cl, l, (l + r) / 2, pos, nv);
    vertex[nroot].cr = ch(vertex[root].cr, (l + r) / 2 + 1, r, pos, nv);
    vertex[nroot].v = vertex[vertex[nroot].cl].v + vertex[vertex[nroot].cr].v;
    return nroot;
}

vector<int> ver(MN);
int que(int i, int j, int k) {
    int l = ver[i - 1], r = ver[j];
    int lg = 1, rg = MN;
    while(lg != rg) {
        int lval = vertex[vertex[r].cl].v - vertex[vertex[l].cl].v;
        if(lval >= k) {
            r = vertex[r].cl;
            l = vertex[l].cl;
            rg = (rg + lg) / 2;
        } else {
            k -= lval;
            r = vertex[r].cr;
            l = vertex[l].cr;
            lg = (rg + lg) / 2 + 1;
        }
    }
    return rg;
}
const int INF = 1e9;
int newpos[MN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //    freopen("gyakkyou.in", "r", stdin);
    //    freopen("gyakkyou.out", "w", stdout);
    
    
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    int l, m;
    vector<pii> in(n);
    cin >> in[0].x >> l >> m;
    in[0].y = 0;
    for(int i = 1; i < n; ++i) {
        in[i].x = ((ll)in[i - 1].x * l + m) % INF;
        in[i].y = i;
    }
    sort(in.begin(), in.end());
    for(int i = 0; i < n; ++i) {
        newpos[in[i].y] = i + 1;
    }
    
    ver[0] = build(1, MN);
    for(int i = 0; i < n; ++i) {
        int k = newpos[i];
        ver[i + 1] = ch(ver[i], 1, MN, k, 1);
        if(globr > MN * 30) {
            for(;;){}
        }
    }
    int b;
    cin >> b;
    ll ans = 0;
    for(int o = 0; o < b; ++o) {
        ll g, x1, lx, mx;
        cin >> g >> x1 >> lx >> mx;
        ll y1, ly, my;
        cin >> y1 >> ly >> my;
        ll k1, lk, mk;
        cin >> k1 >> lk >> mk;
        int i = min(x1, y1), j = max(x1, y1);
        ans += in[que(i, j, k1) - 1].x;
        for(int u = 1; u < g; ++u) {
            x1 = ((i - 1) * lx + mx) % n + 1;
            y1 = ((j - 1) * ly + my) % n + 1;
            i = min(x1, y1); j = max(x1, y1);
            k1 = ((k1 - 1) * lk + mk) % (j - i + 1) + 1;
            ans += in[que(i, j, k1) - 1].x;
        }
    }
    cout << ans;
}
