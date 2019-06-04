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

#pragma comment(linker, "/stack:20000000")
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
static inline int readString(char *s)
{
    char c = readChar();
    int l = 0;
    while (c > 32)
    {
        s[l++] = c;
        c = getChar();
    }
    s[l] = 0;
    return l;
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

const int MN = 2e5 + 11, MQ = 5e5 + 11, ALP = 26, LG = 22;
int binup[MN << 1][LG], tin[MN << 1], tout[MN << 1], ftree[MN << 1];
int __suff_aut[MN << 1][ALP], __suff_len[MN << 1], __suff_link[MN << 1];
int term[MQ], adds[MN], ans[MQ];
char s[MN], t[MN];
int __last = 1, __nit = 2, __r = 0, __t = 0;
int n, m;
vector<int> eds[MN], evs[MN], srev[MN << 1];
struct que
{
    int l1, r1, l2, r2, id;
    inline void read(int id)
    {
        this->id = id;
        l1 = io::readIntFast();
        r1 = io::readIntFast();
        l1--;

        l2 = io::readIntFast();
        r2 = io::readIntFast();
        l2--;
        int len = r1 - l1;
        if (r2 - l2 >= len)
        {
            eds[r1 - 1].push_back(id);
            evs[l2 + len - 1].push_back(id);
            evs[r2].push_back(id);
        }
    }
    que(){};
} ques[MQ];

inline int __new_node(int len)
{
    __suff_len[__nit] = len;
    return __nit++;
}

inline int __clone(int p, int nlen)
{
    __suff_len[__nit] = nlen;
    memcpy(__suff_aut[__nit], __suff_aut[p], sizeof(__suff_aut[p]));
    __suff_link[__nit] = __suff_link[p];
    return __nit++;
}

inline void __add_char(int c)
{
    int np = __new_node(__suff_len[__last] + 1);
    int p = __last;
    adds[__r++] = np;
    while (p && !__suff_aut[p][c])
    {
        __suff_aut[p][c] = np;
        p = __suff_link[p];
    }

    __last = np;
    if (!p)
    {
        __suff_link[np] = 1;
        return;
    }
    int ne = __suff_aut[p][c];
    if (__suff_len[ne] - __suff_len[p] == 1)
    {
        __suff_link[np] = ne;
        return;
    }
    int cl = __clone(ne, __suff_len[p] + 1);
    __suff_link[np] = cl;
    __suff_link[ne] = cl;
    while (p && __suff_aut[p][c] == ne)
    {
        __suff_aut[p][c] = cl;
        p = __suff_link[p];
    }
}
inline void dfs(int u)
{
    tin[u] = __t++;
    for (auto &i : srev[u])
    {
        dfs(i);
    }
    tout[u] = __t;
}

inline void ad(int pos, int val)
{
    for (; pos < (MN << 1); pos |= pos + 1)
    {
        ftree[pos] += val;
    }
}

inline int gt(int pos)
{
    int res = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
    {
        res += ftree[pos];
    }
    return res;
}
inline int gt(int l, int r)
{
    return gt(r - 1) - gt(l - 1);
}

int32_t main()
{
    auto ts = clock();

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    n = io::readString(s);
    m = io::readString(t);

    for (int i = 0; i < m; ++i)
    {
        __add_char(t[i] - 'a');
    }

    int q = io::readIntFast();
    for (int i = 0; i < q; ++i)
    {
        ques[i].read(i);
    }

    for (int i = 1; i < __nit; ++i)
    {
        binup[i][0] = __suff_link[i];
        srev[__suff_link[i]].push_back(i);
    }
    binup[1][0] = 1;

    for (int j = 1; j < LG; ++j)
    {
        for (int i = 1; i < __nit; ++i)
        {
            binup[i][j] = binup[binup[i][j - 1]][j - 1];
        }
    }
    {
        int cp = 1, len = 0;
        for (int i = 0; i < n; ++i)
        {
            int c = s[i] - 'a';
            while (cp && !__suff_aut[cp][c])
            {
                cp = __suff_link[cp];
                len = __suff_len[cp];
            }
            if (!cp)
            {
                cp = 1;
                len = 0;
            }
            else
            {
                cp = __suff_aut[cp][c];
                len += 1;
            }

            for (auto j : eds[i])
            {
                int l = ques[j].r1 - ques[j].l1;
                if (l <= len)
                {
                    term[j] = cp;
                    for (int k = LG - 1; k >= 0; --k)
                    {
                        int up = binup[term[j]][k];
                        if (__suff_len[up] >= l)
                        {
                            term[j] = up;
                        }
                    }
                }
                else
                {
                    term[j] = 0;
                }
            }
        }
    }
    dfs(1);
    for (int i = 0; i <= m; ++i)
    {
        for (auto id : evs[i])
        {
            if (ques[id].r2 != i)
            {
                ans[id] -= gt(tin[term[id]], tout[term[id]]);
            }
            else
            {
                ans[id] += gt(tin[term[id]], tout[term[id]]);
            }
        }
        ad(tin[adds[i]], 1);
    }
    for (int i = 0; i < q; ++i)
    {
        io::writeIntFast(ans[i]);
        io::writeChar('\n');
    }
    io::flush();
    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
