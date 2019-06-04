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

const int MN = 2e2 + 11, MQ = 5e2 + 11, ALP = 26;

int __suff_aut[2 * MN][ALP], __suff_len[2 * MN], __suff_link[2 * MN];
int __last = 1, __nit = 2;

int __new_node(int len)
{
    __suff_len[__nit] = len;
    return __nit++;
}

int __clone(int p, int nlen)
{
    __suff_len[__nit] = nlen;
    memcpy(__suff_aut[__nit], __suff_aut[p], sizeof(__suff_aut[p]));
    __suff_link[__nit] = __suff_link[p];
    return __nit++;
}

void __add_char(int c)
{
    //!!
    assert(c < ALP);
    //!!
    int np = __new_node(__suff_len[__last] + 1);
    int p = __last;
    while (p && !__suff_aut[p][c])
    {
        __suff_aut[p][c] = np;
        p = __suff_link[p];
        //!!
        assert(p != -1);
        //!!
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
        //!!
        assert(p != -1);
        //!!
    }
}
int term[MQ];
vector<int> eds[MN];
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
        eds[r1 - 1].push_back(id);
    }
    que(){};
} ques[MQ];

char s[MN], t[MN];
int n, m;
int ans[MN];
//!!
int term2[MQ];
//!!

int32_t main()
{
    // auto ts = clock();
    
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
                }
                else
                {
                    term[j] = 0;
                }
            }
        }
    }
    for (int i = 0; i < q; ++i)
    {
        if (term[i])
        {
            int l = ques[i].r1 - ques[i].l1;
            int cp = term[i];
            
            while (__suff_link[cp])
            {
                int np = __suff_link[cp];
                if (__suff_len[np] >= l)
                {
                    cp = np;
                }
                else
                {
                    break;
                }
            }
            term[i] = cp;
        }
    }
    //!!
    for (int i = 0; i < q; ++i)
    {
        int cp = 1;
        for (int j = ques[i].l1; j < ques[i].r1; ++j)
        {
            int c = s[j] - 'a';
            if (__suff_aut[cp][c])
            {
                cp = __suff_aut[cp][c];
                term2[i] = cp;
            }
            else
            {
                term2[i] = 0;
                break;
            }
        }
    }
    //!!
    for (int i = 0; i < q; ++i)
    {
        cout << term[i] << " ";
    }
    cout << "\n";
    for (int i = 0; i < q; ++i)
    {
        cout << term2[i] << " ";
        // if (term2[i] != term[i])
        // assert(0);
    }
    io::flush();
    // cerr << ((double)clock() - ts) / CLOCKS_PER_SEC;
}
