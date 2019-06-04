
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <queue>
#include <map>
#include <set>

#pragma GCC optimize("03,unroll-loops")
#pragma GCC target("sse4")

#define pii pair<ll, ll>
#define x first
#define y second
#define ll long long
#define ld long double

using namespace std;
const int MN = 1e5 + 17;
struct node{
    ll a = 0, c = 1e13;
    int l = 0, r = 0;
    int cl = 0, cr = 0;
    node() {};
    node(int l, int r, int a = 0, ll c = (ll)1e13) : l(l), r(r), a(a), c(c){};
};


int treeit = 0;
int root;
node tree[40 * MN];

int build(int l, int r){
    int root = treeit++;
    tree[root] = node(l, r);
    
    if(r - l == 1) {
        return root;
    }
    tree[root].cl = build(l, (l + r) / 2);
    tree[root].cr = build((l + r) / 2, r);
    return root;
}

inline ll val(ll a, ll c, int x) {
    return a * x + c;
}

void addline(ll a, ll c, int root) {
    int m = (tree[root].l + tree[root].r) >> 1;
    ll &ra = tree[root].a, &rc = tree[root].c;
    if(val(ra, rc, m) > val(a, c, m)){
        swap(ra, a);
        swap(rc, c);
    }
    if(tree[root].r - tree[root].l == 1) {
        return;
    }
    
    int rr = tree[root].r;
    if(val(a, c, rr) < val(ra, rc, rr)) {
        addline(a, c, tree[root].cr);
    }
    
    int rl = tree[root].l;
    if(val(a, c, rl) < val(ra, rc, rl)) {
        addline(a, c, tree[root].cl);
    }
}

ll get(int root, ll pos) {
    int m = (tree[root].r + tree[root].l) >> 1;
    ll a = tree[root].a, c = tree[root].c;
    ll v = val(a, c, pos);
    if(tree[root].r - tree[root].l == 1) {
        return v;
    }
    
    if(pos >= m) {
        return min(v, get(tree[root].cr, pos));
    } else {
        return min(v, get(tree[root].cl, pos));
    }
}
inline ll sq(ll a) {
    return a * a;
}

ll h[MN], w[MN];
ll f[MN];


int main() {
    //        freopen("input.txt", "r", stdin);
    //        freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n = readInt();
    for(int i = 0; i < n; ++i) {
        h[i] = readInt();
    }
    ll sum = 0;
    for(int i = 0; i < n; ++i) {
        w[i] = readInt();
        sum += w[i];
    }
    
    root = build(0, 2 * 1e6 + 7);
    f[0] = sq(h[0]) - w[0];
    addline(-2 * h[0], f[0], root);
    for(int i = 1; i < n; ++i) {
        ll k = get(root, h[i]);
        f[i] = k + sq(h[i]) - w[i];
        addline(-2 * h[i], f[i] + sq(h[i]), root);
    }
    
    
    writeInt<ll>(f[n - 1] + sum);
    return 0;
}
