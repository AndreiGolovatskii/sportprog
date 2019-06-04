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

const int MN = 4 * 100 * 1000 + 17;
int globr = 0;
struct node{
    int o, c;
    int cl, cr;
    node(){cl = cr = 0; o = c = 0;};
};
node ve[30 * MN];

int build(int l, int r){
    int root = globr++;
    ve[root].o = ve[root].c = 0;
    if(l == r) return root;
    ve[root].cl = build(l, (l + r) / 2);
    ve[root].cr = build((l + r) / 2 + 1, r);
    
    return root;
}

int ch(int root, int l, int r, int pos, int no, int nc) {
    if(pos < l || pos > r) {
        return root;
    }
    if(l == r){
        int nroot = globr++;
        ve[nroot].o = ve[root].o + no;
        ve[nroot].c = ve[root].c + nc;
        return nroot;
    }
    int nroot = globr++;
    ve[nroot].cl = ch(ve[root].cl, l, (l + r) / 2, pos, no, nc);
    ve[nroot].cr = ch(ve[root].cr, (l + r) / 2 + 1, r, pos, no, nc);
    ve[nroot].c = ve[ve[nroot].cl].c + ve[ve[nroot].cr].c;
    ve[nroot].o = ve[ve[nroot].cl].o + ve[ve[nroot].cr].o;
    return nroot;
}

int ver[MN];

vector<pii> ev;
void prep(){
    sort(ev.begin(), ev.end());
    ver[0] = build(1, MN);
    for(int i = 0; i < ev.size(); ++i) {
        if(ev[i].y > 0){
            ver[i + 1] = ch(ver[i], 1, MN, abs(ev[i].y), 1, 0);
        } else {
            ver[i + 1] = ch(ver[i], 1, MN, abs(ev[i].y), 0, 1);
        }
    }
}

int que(int x, int y) {
    int l = lower_bound(ev.begin(), ev.end(), make_pair(x, (int)0)) - ev.begin();
    int r = lower_bound(ev.begin(), ev.end(), make_pair(y, (int)-1e9 - 1000)) - ev.begin();
    int lg = 1, rg = MN;
    int rl = ver[l], rr = ver[r];
    while(lg != rg) {
        int k = ve[ve[rr].cl].o - ve[ve[rl].cl].o;
        int t = ve[ve[rl].cl].o - ve[ve[rl].cl].c;
        int sz = (rg + lg) / 2 - lg + 1;
        if(k + t < sz) {
            rr = ve[rr].cl;
            rl = ve[rl].cl;
            rg = (lg + rg) / 2;
        } else {
            rr = ve[rr].cr;
            rl = ve[rl].cr;
            lg = (lg + rg) / 2 + 1;
        }
    }
    return rg;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //    freopen("intercity.in", "r", stdin);
    //    freopen("intercity.out", "w", stdout);
    
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, s, m;
    cin >> n >> s >> m;
    for(int i = 0; i < m; ++i) {
        int c, a, b;
        cin >> c >> a >> b;
        
        ev.push_back({a, c});
        ev.push_back({b, -c});
    }
    prep();
    
    int p = 0, q;
    cin >> q;
    for(int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        x += p;
        y += p;
        
        p = que(x, y);
        if(p > s) {
            p = 0;
        }
        cout << p << "\n";
    }
}
