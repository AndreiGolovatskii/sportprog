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
//Fast io
namespace io {
    static const int bs = 4096;
    static unsigned char ib[bs];
    static int isz = 0, ic = 0;
    
    static inline bool is(){
        if(isz == ic) {
            ic = 0;
            isz = (int)fread(ib, 1, bs, stdin);
            if(!isz) return 0;
        }
        return 1;
    }
    
    static inline int getChar(){
        return is() ? ib[ic++] : -1;
    }
    static inline int getCharNoP(){
        return is() ? ib[ic] : -1;
    }
    
    static inline void pp(){
        char c = getCharNoP();
        while(c != -1 && c <= 32) {
            ic++;
            c = getCharNoP();
        }
    }
    static inline char readChar(){
        pp();
        int r = getChar();
        while(r != -1 && r <= 32) {
            r = getChar();
        }
        return r;
    }
    static inline int readIntFast(){
        pp();
        int r = 0;
        int c = getChar();
        
        while('0' <= c && c <= '9') {
            r = r * 10 + c - '0';
            c = getChar();
        }
        return r;
    }
    
    static unsigned char ob[bs];
    static int oc = 0;
    
    
    static inline void flush(){
        if(oc) {
            fwrite(ob, 1, oc, stdout);
            oc = 0;
        }
    }
    
    static inline void writeChar(int c) {
        if(oc == bs) {
            flush();
        }
        ob[oc++] = c;
    }
    
    static inline void writeStr(const char *s) {
        while(*s)
            writeChar(*s++);
    }
    static inline void writeIntFast(int a) {
        if(!a) {
            writeChar('0');
            return;
        }
        char s[15];
        int n = 0;
        while(a) s[n++] = '0' + a % 10, a/= 10;
        while(n--) writeChar(s[n]);
    }
}
//end fast io

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
    inline void resize(int n)
    {
        g.resize(n);
        brother.resize(n);
    }
    inline void add_edge(int u, int v)
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
inline bool operator==(const que &a, const que &b) {
    return a.l == b.l && a.r == b.r && a.u == b.u && a.v == b.v;
}
inline bool operator<(const que &a, const que &b) {
    return a.l == b.l ? (a.r == b.r ? (a.u == b.u ? a.v < b.v : a.u < b.u) : a.r < b.r) : a.l < b.l;
}

int used[MN], color[MN], q[MN];
inline void bfs(graph &g, int u, int c)
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
inline int splque(int l, int r, vector<que> &qs, graph &g) {
    int flag = 0;
    for (auto i : qs)
    {
        if ((i.l < l && i.r >= r) || i.l >= r || i.r < l)
        {
            g.add_edge(i.u, i.v);
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
    for (auto &i : qs)
    {
        if((i.l >= l && i.l < r) || (i.r >= l && i.r < r))
        {
            used[color[i.u]] = 1;
            used[color[i.v]] = 1;
        }
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
    
    g.brother.clear();
    vector<que> nneq;
    nneq.reserve(qs.size());
    
    
    for (auto &i : qs)
    {
        if((i.l >= l && i.l < r) || (i.r >= l && i.r < r))
        {
            i.u = color[i.u];
            i.v = color[i.v];
            if (i.u != i.v)
            {
                nneq.push_back(i);
            }
        }
    }
    qs = nneq;
    sort(qs.begin(), qs.end());
    qs.resize(unique(qs.begin(), qs.end()) - qs.begin());
    g = gn;
    return flag;
}

int ans[MN];
inline void sol(int l, int r, vector<que> &qs, graph &g, int flag)
{
    if(flag) {
        if(r - l == 1) {
            ans[l] = flag;
            return;
        } else {
            int m = (l + r) >> 1;
            sol(l, m, qs, g, flag);
            sol(m, r, qs, g, flag);
            return;
        }
    }
    
    auto qsr = qs;
    auto gr = g;
    
    if (r - l == 1)
    {
        ans[l] = flag;
        return;
    }
    else
    {
        int m = (r + l) >> 1;
        int lr = splque(l, m, qs, g);
        sol(l, m, qs, g, flag || lr);
        int rr = splque(m, r, qsr, gr);
        sol(m, r, qsr, gr, flag || rr);
    }
}

int32_t main()
{
//    auto ts = clock();
    
     freopen("input.txt", "r", stdin);
     freopen("output.txt", "w", stdout);
    
    int n, m;
//    cin >> n >> m;
    n = io::readIntFast();
    m = io::readIntFast();
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
//        cin >> u >> v;
        u = io::readIntFast();
        v = io::readIntFast();
        u--;
        v--;
        if (u > v)
            swap(u, v);
        eds.push_back(que(u, v, 2 * u, 2 * v + 1));
        eds.push_back(que(u, v, 2 * u + 1, 2 * v));
    }
    sol(0, n, eds, st, 0);
    vector<int> res;
    for (int i = 0; i < n; ++i)
    {
        if (ans[i] == 0)
            res.push_back(i + 1);
    }
//    cout << res.size() << "\n";
    io::writeIntFast(res.size());
    io::writeChar('\n');
    for (auto i : res)
    {
//        cout << i << ' ';
        io::writeIntFast(i);
        io::writeChar(' ');
    }
    io::flush();
//    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
