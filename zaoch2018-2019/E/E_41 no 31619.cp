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
#include <functional>
#include <cassert>
#include <cstring>
#include <list>
#include <bitset>
#include <deque>
#include <complex>
#include <cmath>

#pragma comment(linker, "/stack:200000000")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

using namespace std;
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define x first
#define y second
#define ld long double
const int MN = 3e6 + 11;

struct edge
{
    int u, v;
    edge(){};
    edge(int u, int v) : u(u), v(v){};
};

struct graph
{
    vector<vector<int>> g;
    vector<int> brother;
    void resize(int n)
    {
        g.resize(n);
        brother.resize(n);
    }
    void add_edge(int u, int v)
    {
        g[u].push_back(v);
        g[v].push_back(u);
    }
    graph(){};
    graph(int n)
    {
        resize(n);
    }
};
struct que
{
    int l, r, u, v;
    que(){};
    que(int l, int r, int u, int v) : l(l), r(r), u(u), v(v){};
};

int used[MN], color[MN], q[MN];
void bfs(graph &g, int u, int c)
{
    used[u] = 1;
    color[u] = c;
    int l = 0, r = 0;
    q[r++] = u;
    while(r - l > 0) {
        int u = q[l++];
        color[u] = c;
    
        for (auto v : g.g[u])
        {
            if (!used[v])
            {
                q[r++] = v;
                used[v] = 1;
            }
        }
    }
}

int ans[MN], pw[MN];
void sol(int l, int r, vector<que> &qs, graph &g, int flag)
{
    vector<que> neq;
    for (auto i : qs)
    {
        if (i.l <= l && i.r >= r)
        {
            g.add_edge(i.u, i.v);
        } else if(i.r <= l || i.l >= r)
        {
            continue;
        }
        else
        {
            neq.push_back(i);
        }
    }
    
    int n = g.g.size();
    int c = 0;
    memset(used, 0, sizeof(used[0]) * n);
    memset(color, 0, sizeof(color[0]) * n);
    for (int i = 0; i < n; ++i)
    {
        if (!used[i])
        {
            bfs(g, i, c++);
        }
    }
    g.g.clear();
    for (int i = 0; i < n; ++i)
    {
        int bi = g.brother[i];
        if (color[i] == color[bi])
            flag = 1;
    }
    memset(used, 0, sizeof(used[0]) * n);
    for (auto &i : neq)
    {
        used[color[i.u]] = 1;
        used[color[i.v]] = 1;
    }
    
    int cnt = 0;
    for (int i = 0; i < c; ++i)
    {
        if (used[i])
            used[i] = cnt++;
        else
            used[i] = -1;
    }
    for (int i = 0; i < n; ++i)
    {
        color[i] = used[color[i]];
    }
    
    graph gn(cnt);
    for (int i = 0; i < n; ++i)
    {
        int bi = g.brother[i];
        if (color[i] != -1 && color[bi] != -1)
            gn.brother[color[i]] = color[bi];
    }
    graph gnr = gn;
    g.brother.clear();
    vector<que> nneq;
    for (auto &i : neq)
    {
        i.u = color[i.u];
        i.v = color[i.v];
        if (i.u != i.v)
        {
            nneq.push_back(i);
        }
    }
    
    neq.clear();
    
    if (r - l == 1)
    {
        ans[l] = flag;
        return;
    }
    else
    {
        int m = (r + l) >> 1;
        sol(l, m, nneq, gn, flag);
        sol(m, r, nneq, gnr, flag);
    }
}

int32_t main()
{
    ios::sync_with_stdio(0);
    cout.tie();
    cin.tie();
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n, m;
    cin >> n >> m;
    graph st(2 * n);
    for (int i = 0; i < n; ++i)
    {
        st.brother[2 * i] = 2 * i + 1;
        st.brother[2 * i + 1] = 2 * i;
    }
    vector<que> eds;
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        if (u > v)
            swap(u, v);
        pw[u]++;
        pw[v]++;
        eds.push_back(que(0, u, 2 * u, 2 * v + 1));
        eds.push_back(que(0, u, 2 * u + 1, 2 * v));
        
        eds.push_back(que(u + 1, v, 2 * u, 2 * v + 1));
        eds.push_back(que(u + 1, v, 2 * u + 1, 2 * v));
        
        eds.push_back(que(v + 1, n, 2 * u, 2 * v + 1));
        eds.push_back(que(v + 1, n, 2 * u + 1, 2 * v));
    }
    sol(0, n, eds, st, 0);
    vector<int> res;
    for (int i = 0; i < n; ++i)
    {
        if (ans[i] == 0)
            res.push_back(i + 1);
    }
    cout << res.size() << "\n";
    for (auto i : res)
    {
        cout << i << ' ';
    }
}
