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
namespace io
{
    static const int bs = 4096;
    static unsigned char ib[bs];
    static int isz = 0, ic = 0;
    
    static inline bool is()
    {
        if (isz == ic)
        {
            ic = 0;
            isz = (int)fread(ib, 1, bs, stdin);
            if (!isz)
                return 0;
        }
        return 1;
    }
    
    static inline int getChar()
    {
        return is() ? ib[ic++] : -1;
    }
    static inline int getCharNoP()
    {
        return is() ? ib[ic] : -1;
    }
    
    static inline void pp()
    {
        char c = getCharNoP();
        while (c != -1 && c <= 32)
        {
            ic++;
            c = getCharNoP();
        }
    }
    static inline char readChar()
    {
        pp();
        int r = getChar();
        while (r != -1 && r <= 32)
        {
            r = getChar();
        }
        return r;
    }
    static inline int readIntFast()
    {
        pp();
        int r = 0;
        int c = getChar();
        
        while ('0' <= c && c <= '9')
        {
            r = r * 10 + c - '0';
            c = getChar();
        }
        return r;
    }
    
    static unsigned char ob[bs];
    static int oc = 0;
    
    static inline void flush()
    {
        if (oc)
        {
            fwrite(ob, 1, oc, stdout);
            oc = 0;
        }
    }
    
    static inline void writeChar(int c)
    {
        if (oc == bs)
        {
            flush();
        }
        ob[oc++] = c;
    }
    
    static inline void writeStr(const char *s)
    {
        while (*s)
            writeChar(*s++);
    }
    static inline void writeIntFast(int a)
    {
        if (!a)
        {
            writeChar('0');
            return;
        }
        char s[15];
        int n = 0;
        while (a)
            s[n++] = '0' + a % 10, a /= 10;
        while (n--)
            writeChar(s[n]);
    }
} // namespace io

using namespace std;
#define ll long long
#define ull unsigned long long
#define pii pair<int, int>
#define x first
#define y second
#define ld long double
const int MN = 3e6 + 11;

int n, m;
vector<int> g[MN];
int color[MN], incycle[MN];
int ans[MN];

vector<int> pth;

int dfs(int u, int c)
{
    if (incycle[u])
        return -1;
    pth.push_back(u);
    color[u] = c;
    for (auto v : g[u])
    {
        if (incycle[v])
            continue;
        if (color[v] == -1)
        {
            int k = dfs(v, c ^ 1);
            if (k > -1)
                return k;
        }
        if (color[v] == c)
        {
            return v;
        }
    }
    pth.pop_back();
    return -1;
}
vector<int> n1_cycle;
int find_1_cycle()
{
    memset(color, -1, sizeof(color));
    int k = -1;
    for (int i = 0; i < n; ++i)
    {
        if (color[i] == -1)
        {
            k = dfs(i, 0);
            if (k > -1)
            {
                break;
            }
        }
    }
    if (k == -1)
        return 0;
    while (pth.back() != k)
    {
        n1_cycle.push_back(pth.back());
        pth.pop_back();
    }
    n1_cycle.push_back(k);
    for (auto i : n1_cycle)
    {
        incycle[i] = 1;
    }
    pth.clear();
    return 1;
}
struct que
{
    int u, v, c;
    que(){};
    que(int u, int v, int c) : u(u), v(v), c(c){};
};

int cyclepos[MN];
int incyclecolor[MN][2];
void dfs2(int u, int c)
{
    if (incycle[u])
    {
        incyclecolor[cyclepos[u]][c]++;
        pth.push_back(cyclepos[u]);
        return;
    }
    color[u] = c;
    for (auto v : g[u])
    {
        if (color[v] == -1)
            dfs2(v, c ^ 1);
    }
}

int dbal[MN];
int poscolor[MN];
int z1[MN], z2[MN];

int qsz = 0;
int dpr()
{
    sort(pth.begin(), pth.end());
    pth.resize(unique(pth.begin(), pth.end()) - pth.begin());
    int p1 = 0, p2 = 0;
    int z = 0;
    
    int k = pth.size();
    p1 = p2 = 0;
    for (int i = 0; i < k; ++i)
    {
        int u = pth[i];
        if ((u & 1) != z)
        {
            z ^= 1;
            swap(p1, p2);
        }
        if (incyclecolor[u][0])
        {
            dbal[u + 1] -= p1;
            dbal[n1_cycle.size()] -= p2;
            dbal[u] += p2;
            
            qsz += p1 + p2;
        }
        if (incyclecolor[u][1])
        {
            dbal[u + 1] -= p2;
            dbal[n1_cycle.size()] -= p1;
            dbal[u] += p1;
            
            qsz += p1 + p2;
        }
        if (incyclecolor[u][0])
        {
            p2++;
        }
        if (incyclecolor[u][1])
        {
            p1++;
        }
        if (incyclecolor[u][1] && incyclecolor[u][0])
        {
            qsz++;
            dbal[u]++;
            dbal[u + 1]--;
        }
    }
    p1 = p2 = 0;
    for (int i = k - 1; i >= 0; --i)
    {
        int u = pth[i];
        if ((u & 1) != z)
        {
            z ^= 1;
            swap(p1, p2);
        }
        
        if (incyclecolor[u][0])
        {
            dbal[u] += p1;
            dbal[0] += p2;
            dbal[u + 1] -= p2;
        }
        if (incyclecolor[u][1])
        {
            dbal[u] += p2;
            dbal[0] += p1;
            dbal[u + 1] -= p1;
        }
        if (incyclecolor[u][0])
        {
            p2++;
        }
        if (incyclecolor[u][1])
        {
            p1++;
        }
    }
    //
    
    // qsz += n * (n - 1) / 2 + m * (m - 1) / 2 + n * m;
    for (auto i : pth)
    {
        incyclecolor[i][0] = incyclecolor[i][1] = 0;
    }
    return 0;
}
void sol()
{
    memset(color, -1, sizeof(color));
    int cn = n1_cycle.size();
    for (int i = 0; i < cn; ++i)
    {
        int u = n1_cycle[i];
        cyclepos[u] = i;
    }
    
    for (int i = 0; i < cn; ++i)
    {
        int u = n1_cycle[i];
        for (int v : g[u])
        {
            if (incycle[v])
            {
                int up = cyclepos[u];
                int vp = cyclepos[v];
                if ((up + 1) % cn == vp || (vp + 1) % cn == up)
                    continue;
            }
            if (color[v] != -1)
                continue;
            pth.clear();
            incyclecolor[cyclepos[u]][1]++;
            pth.push_back(cyclepos[u]);
            dfs2(v, 0);
            dpr();
        }
    }
    int cb = 0;
    for (int i = 0; i < cn; ++i)
    {
        cb += dbal[i];
        if (cb == qsz)
        {
            ans[n1_cycle[i]] = 1;
        }
    }
}

int32_t main()
{
    // auto ts = clock();
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    n = io::readIntFast();
    m = io::readIntFast();
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        u = io::readIntFast();
        v = io::readIntFast();
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int r = find_1_cycle();
    if (r == 0)
    {
        io::writeIntFast(n);
        io::writeChar('\n');
        for (int i = 0; i < n; ++i)
        {
            io::writeIntFast(i + 1);
            io::writeChar(' ');
        }
    }
    else
    {
        int r2 = find_1_cycle();
        if (r2 == 1)
        {
            io::writeIntFast(0);
            io::writeChar('\n');
        }
        else
        {
            sol();
            vector<int> res;
            for (int i = 0; i < n; ++i)
            {
                if (ans[i] == 1)
                    res.push_back(i + 1);
            }
            io::writeIntFast(res.size());
            io::writeChar('\n');
            for (auto i : res)
            {
                io::writeIntFast(i);
                io::writeChar(' ');
            }
        }
    }
    io::flush();
    // cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
