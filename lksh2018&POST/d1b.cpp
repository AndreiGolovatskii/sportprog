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

const int MN = 1000000 + 17, LOGN = 25;

vector<int> g[MN];
vector<int> el;
int first[MN], d[MN];
int st[MN][LOGN], lg[MN];

void dfs(int u, int di) {
    d[u] = di;
    el.push_back(u);
    for(int v : g[u]) {
        dfs(v, di + 1);
        el.push_back(u);
    }
}

void prep(){
    dfs(0, 0);
    
    for(int i = 0; i < MN; ++i) {
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
            if(d[el[st[i][k - 1]]] < d[el[st[i + (1 << (k - 1))][k - 1]]]) {
                st[i][k] = st[i][k - 1];
            } else {
                st[i][k] = st[i + (1 << (k - 1))][k - 1];
            }
        }
    }
    for(int i = 2; i < MN; ++i) {
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
    if(d[el[st[a][k]]] < d[el[st[b - (1 << k) + 1][k]]]) {
        return el[st[a][k]];
    } else {
        return el[st[b - (1 << k) + 1][k]];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    for(int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    
    ll a1, a2;
    cin >> a1 >> a2;
    
    int x, y, z;
    cin >> x >> y >> z;
    
    prep();
    
    int v = 0;
    ll ans;
    ans = v = que((a1 + v) % n, a2);
    for(int i = 2; i <= m; ++i) {
        a1 = (a1 * x + a2 * y + z) % n;
        swap(a1, a2);
        a1 = (a1 * x + a2 * y + z) % n;
        swap(a1, a2);
        
        v = que((a1 + v) % n, a2);
        ans += v;
    }
    cout << ans;
}


