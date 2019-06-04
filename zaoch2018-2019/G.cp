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

#define FAST_ALLOCATOR_MEMORY 2e8

#ifdef FAST_ALLOCATOR_MEMORY // 2e8
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void *operator new(size_t n)
{
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
    return (void *)res;
}
inline void operator delete(void *)noexcept {}
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }
#endif

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
const int MN = 1e4 + 11;
int a[MN];
vector<int> g[MN];
int col[MN];

inline void dfs(int u, int c)
{
    col[u] = c;
    for (auto v : g[u])
    {
        if (!col[v])
            dfs(v, c);
    }
}
vector<int> colmm[MN];

const int INF = 1e9 + 11;
int d[MN];

int32_t main()
{
    auto ts = clock();
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    int n, m;
    n = io::readIntFast();
    m = io::readIntFast();

    for (int i = 0; i < n; ++i)
    {
        a[i] = io::readIntFast();
    }
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
    int c = 1;
    for (int i = 0; i < n; ++i)
    {
        if (!col[i])
        {
            dfs(i, c++);
        }
    }

    for (int i = 0; i < n; ++i)
    {
        colmm[col[i]].push_back(a[i]);
    }
    for (int i = 1; i < c; ++i)
    {
        sort(colmm[i].begin(), colmm[i].end());
        reverse(colmm[i].begin(), colmm[i].end());
    }

    d[0] = -INF;
    for (int i = 1; i <= n; ++i)
    {
        d[i] = INF;
    }

    int r = 0;
    for (int i = 0; i < n; ++i)
    {
        int cll = col[i];
        int c = r + 1;
        for (auto ai : colmm[cll])
        {
            while (c > 0)
            {
                if (d[c - 1] < ai)
                {
                    d[c] = ai;
                    r = max(r, c);
                    break;
                }
                else
                {
                    c--;
                }
            }
        }
    }
    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
    io::writeIntFast(r);
    io::flush();
}
