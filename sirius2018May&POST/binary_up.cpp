#include <bits/stdc++.h>

using namespace std;

const int MN = (int)1e5;
vector<int> g[MN];

int bp[MN][35];
int mx[MN][35];
int p[MN], cost[MN], d[MN];

void dfs(int u, int di) {
    d[u] = di;
    for(auto v : g[u]) {
        dfs(v, di + 1);
    }
}
int lca(int u, int v) {
    if(d[v] > d[u]) {
        swap(u, v);
    }
    for(int i = 34; i >= 0; --i) {
        if(d[bp[u][i]] - d[v] >= 0) {
            u = bp[u][i];
        }
    }
    if(u == v) return v;
    for(int i = 34; i >= 0; --i) {
        if(bp[u][i] != bp[v][i]) {
            v = bp[v][i];
            u = bp[u][i];
        }
    }
    return p[v];
}

int fm(int u, int lc) {
    int ans = (int) 1e9 + 1;
    if(u == lc) {
        return ans;
    }

    for(int i = 34; i >= 0; --i) {
        if(d[bp[u][i]] >= d[lc]) {
            ans = min(ans, mx[u][i]);
            u = bp[u][i];
        }
    }
    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    cin >> n;
    for(int i = 1; i < n; ++i) {
        int pi, c;
        cin >> pi >> c;
        pi--;
        g[pi].push_back(i);
        cost[i] = c;
        p[i] = pi;
    }

    dfs(0, 0);

    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < 35; ++j) {
            mx[i][j] = 1e9;
        }
    }
    cost[0] = 1e9;
    for(int i = 0; i < n; ++i) {
        bp[i][0] = p[i];
        mx[i][0] = cost[i];
    }
    for(int j = 1; j < 35; ++j) {
        for(int i = 0; i < n; ++i){
            bp[i][j] = bp[bp[i][j - 1]][j - 1];
            mx[i][j] = min(mx[i][j - 1], mx[bp[i][j - 1]][j - 1]);
        }
    }

    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        int lc = lca(u, v);
        cout << min(fm(u, lc), fm(v, lc)) << "\n";
    }
}