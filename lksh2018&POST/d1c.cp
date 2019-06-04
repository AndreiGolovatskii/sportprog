#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second
#define ll long long

const int E5 = 1e5 + 17, E6 = 1e6 + 17, LOGN = 22;

vector<pii> g[E5];
vector<int> el;
int first[E5], d[E5];
int st[2 * E5][LOGN], lg[2 * E5];

void dfs(int u, int di, int p) {
    d[u] = di;
    el.push_back(u);
    for(pii v : g[u]) {
        if(v.x == p) continue;
        dfs(v.x, di + 1, u);
        el.push_back(u);
    }
}

bool isup(int a, int b) {
    return d[el[a]] < d[el[b]];
}

void prep(){
    dfs(0, 0, 0);
    
    for(int i = 0; i < E5; ++i) {
        first[i] = -1;
    }
    for(int i = 0; i < el.size(); ++i) {
        int u = el[i];
        if(first[u] == -1) {
            first[u] = i;
        }
    }
    
    int n = (int)el.size();
    for(int i = 0; i < n; ++i) {
        st[i][0] = i;
    }
    
    for(int k = 1; k < LOGN; ++k) {
        for(int i = 0; i + (1 << k) < n; ++i) {
            if(isup(st[i][k - 1], st[i + (1 << (k - 1))][k - 1])) {
                st[i][k] = st[i][k - 1];
            } else {
                st[i][k] = st[i + (1 << (k - 1))][k - 1];
            }
        }
    }
    for(int i = 2; i < n; ++i) {
        lg[i] = lg[i >> 1] + 1;
    }
}

int que(int u, int v){
    int a = first[u];
    int b = first[v];
    if(a > b) {
        swap(a, b);
    }
    int k = lg[b - a + 1];
    if(isup(st[a][k], st[b - (1 << k) + 1][k])) {
        return el[st[a][k]];
    } else {
        return el[st[b - (1 << k) + 1][k]];
    }
}
struct ed{
    int u, v, w;
    ed(){};
    ed(int u, int v, int w): u(u), v(v), w(w) {};
};
int t[E6];
void add(int pos, int d) {
    for(; pos < E6; pos |= (pos + 1)) {
        t[pos] += d;
    }
}
int get(int pos) {
    int res = 0;
    for(; pos >= 0; pos = (pos & (pos + 1)) - 1) {
        res += t[pos];
    }
    return res;
}


ll ans[E6];
vector<pii> qonv[E5];
vector<ed> ques;
void dfs2(int u, int p) {
    for(pii q : qonv[u]) {
        int clc = get(ques[q.x].w);
        ans[q.x] += q.y * clc;
    }
    for(auto v : g[u]) {
        if(v.x == p) continue;
        add(v.y, 1);
        dfs2(v.x, u);
        add(v.y, -1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    freopen("union.in", "r", stdin);
    freopen("union.out", "w", stdout);
    
    int n;
    cin >> n;
    vector<ed> in(n - 1);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        in[i] = ed(u, v, w);
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }
    
    prep();
    int q;
    cin >> q;
    ques.resize(q);
    for(int i = 0; i < q; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        
        ques[i] = ed(u, v, w);
        qonv[u].push_back({i, 1});
        qonv[v].push_back({i, 1});
        qonv[que(u, v)].push_back({i, -2});
    }
    
    dfs2(0, 0);
    for(int i = 0; i < q; ++i) {
        cout << ans[i] << "\n";
    }
}


