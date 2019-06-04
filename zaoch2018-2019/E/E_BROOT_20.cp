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
const int MN = 3e6 + 11, LG = 30;

struct edge
{
    int u, v;
    edge(){};
    edge(int u, int v) : u(u), v(v){};
} eds[2 * MN];
vector<int> g[MN];
int __eds_it = 0;
int color[MN], used[MN];

int dfs(int u, int c, int z)
{
    used[u] = 1;
    color[u] = c;
    for (int e : g[u])
    {
        int v = eds[e].v;
        if (v != z)
        {
            if (!used[v])
            {
                if (!dfs(v, c ^ 1, z))
                {
                    return 0;
                }
            }

            if (color[u] == color[v])
            {
                return 0;
            }
        }
    }
    return 1;
}

int check(int u, int n)
{
    memset(color, 0, sizeof(color));
    memset(used, 0, sizeof(used));
    for (int i = 0; i < n; ++i)
    {
        if (!used[i] && i != u)
        {
            if (!dfs(i, 1, u))
            {
                return 0;
            }
        }
    }
    return 1;
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
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        eds[__eds_it] = edge(u, v);
        g[u].push_back(__eds_it++);

        eds[__eds_it] = edge(v, u);
        g[v].push_back(__eds_it++);
    }
    vector<int> r;
    for (int i = 0; i < n; ++i)
    {
        if (check(i, n))
        {
            r.push_back(i + 1);
        }
    }
    cout << r.size() << "\n";
    for (auto i : r)
    {
        cout << i << " ";
    }
}
