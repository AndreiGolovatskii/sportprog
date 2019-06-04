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
const int MN = 5e5 + 11, MQ = 5e5 + 11;
char s[MN], t[MN];
int n, m;

const int HCNT = 3;
int BASE[HCNT] = {27, 29, 31};
int MOD[HCNT] = {(int)(1e9 + 7), (int)(1e9 + 11), (int)(1e9 + 13)};
ll BASEPOW[HCNT][MN];
struct hs
{
    ll val[HCNT];
    inline void operator+=(const hs &a)
    {
        for (int i = 0; i < HCNT; ++i)
        {
            val[i] += a.val[i];
            val[i] %= MOD[i];
        }
    }
    inline void operator+=(const int a)
    {
        for (int i = 0; i < HCNT; ++i)
        {
            val[i] += a;
            val[i] %= MOD[i];
        }
    }
    inline void pw(int a)
    {
        for (int i = 0; i < HCNT; ++i)
        {
            val[i] *= BASEPOW[i][a];
            val[i] %= MOD[i];
        }
    }
    inline hs operator<<(int a) const
    {
        hs r;
        for (int i = 0; i < HCNT; ++i)
        {
            r.val[i] = val[i] * BASEPOW[i][a];
            r.val[i] %= MOD[i];
        }
        return r;
    }
    inline hs operator-(const hs &a) const
    {
        hs r;
        for (int i = 0; i < HCNT; ++i)
        {
            r.val[i] = val[i] - a.val[i];
            r.val[i] %= MOD[i];
            if (r.val[i] < 0)
                r.val[i] += MOD[i];
        }
        return r;
    }
    hs()
    {
        memset(val, 0, sizeof(val));
    }
};

bool operator<(const hs &a, const hs &b)
{
    for (int i = 0; i < HCNT; ++i)
    {
        if (a.val[i] < b.val[i])
            return 1;
        else if (a.val[i] < b.val[i])
            return 0;
    }
    return 0;
}

void prep()
{
    for (int i = 0; i < HCNT; ++i)
    {
        BASEPOW[i][0] = 1;
        for (int j = 1; j < MN; ++j)
        {
            BASEPOW[i][j] = BASEPOW[i][j - 1] * BASE[i];
            BASEPOW[i][j] %= MOD[i];
        }
    }
}

hs shs[MN], ths[MN];
void clchs(char *s, int n, hs *shs)
{
    for (int i = 0; i < n; ++i)
    {
        shs[i + 1] = shs[i] << 1;
        shs[i + 1] += s[i] - 'a' + 1;
    }
}
hs gh(int l, int r, hs *shs)
{
    return shs[r] - (shs[l] << (r - l));
}
struct que
{
    hs f;
    int l, r, id;
    que(){};
    que(const hs &f, int l, int r, int id) : f(f), l(l), r(r), id(id){};
};

vector<que> quebylen[MN];

int ans[MN];
int32_t main()
{
    // auto ts = clock();
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    prep();
    n = io::readString(s);
    m = io::readString(t);
    clchs(s, n, shs);
    clchs(t, m, ths);
    int q = io::readIntFast();
    for (int i = 0; i < q; ++i)
    {
        int l1 = io::readIntFast();
        int r1 = io::readIntFast();
        l1--;
        
        int l2 = io::readIntFast();
        int r2 = io::readIntFast();
        l2--;
        quebylen[r1 - l1].push_back(que(gh(l1, r1, shs), l2, r2, i));
    }
    for (int len = 1; len < MN; ++len)
    {
        if (quebylen[len].size() == 0)
            continue;
        map<hs, vector<int>> mvp;
        for (int i = 0; i + len <= m; ++i)
        {
            mvp[gh(i, i + len, ths)].push_back(i);
        }
        for (auto i : quebylen[len])
        {
            ans[i.id] = upper_bound(mvp[i.f].begin(), mvp[i.f].end(), i.r - len) - lower_bound(mvp[i.f].begin(), mvp[i.f].end(), i.l);
        }
    }
    for (int i = 0; i < q; ++i)
    {
        cout << ans[i] << "\n";
    }
    
    // cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
