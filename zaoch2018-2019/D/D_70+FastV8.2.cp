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

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>
const int MN = 5e5 + 3, MQ = 25e4 + 3, MQC = 5e4 + 3, MEXMN = 1 << 9;
int ans[MN];
int curra[MN];
struct que{
    int a, b, id, t;
    que(){};
    que(int a, int b, int t, int id): a(a), b(b), t(t), id(id){};
};
int BS = 3969;
inline bool operator<(const que &f, const que &s) {
    if(f.t / BS == s.t / BS) {
        return f.a / BS == s.a / BS ? f.b < s.b : f.a / BS < s.a / BS;
    } return f.t / BS < s.t / BS;
}
int normit = 0, chit = 0;
que normques[MQ], change[MQC];
int mex[MN];
int16_t up[(MN >> 9) + 11];

inline void addval(int a) {
    if(!(mex[a]++)) up[a >> 9]++;
}

inline void errval(int a) {
    if(!(--mex[a])) up[a >> 9]--;
}
inline int get() {
    int i = -1;
    while(up[++i] == MEXMN);
    i *= MEXMN;
    i -= 1;
    while (mex[++i]);
    return i;
}

int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n = io::readIntFast();
    int q = io::readIntFast();
    
    memset(ans, -1, sizeof(ans));
    
    for(int i = 0; i < n; ++i) {
        curra[i] = io::readIntFast();
    }
    for(int i = 0; i < q; ++i) {
        char t = io::readChar();
        int a = io::readIntFast();
        int b = io::readIntFast();
        a--;
        
        if(t == '?') {
            normques[normit++] = que(a, b, chit, i);
        }
        else {
            int l = curra[a];
            curra[a] = b;
            change[chit++] = que(a, b, l, 0);
        }
    }
    if(!normit) return 0;
    
    
    BS = 1;
    if(chit <= 1000) {
        while((ll)BS * BS * normit < (ll)n * n) BS++;
    } else {
        while((ll)BS * BS * BS * normit < (ll)chit * n * n) BS++;
    }
    
    int l = 0, r = 0, t = chit;
    sort(normques, normques + normit);
    for(int i = 0; i < normit; ++i) {
        que c = normques[i];
        while(t < c.t) {
            curra[change[t].a] = change[t].b;
            if(l <= change[t].a && change[t].a < r) {
                errval(change[t].t);
                addval(change[t].b);
            }
            t++;
        }
        while(t > c.t) {
            t--;
            curra[change[t].a] = change[t].t;
            if(l <= change[t].a && change[t].a < r) {
                errval(change[t].b);
                addval(change[t].t);
            }
        }
        while (r > c.b) {
            errval(curra[--r]);
        }
        while (r < c.b) {
            addval(curra[r++]);
        }
        while(l < c.a) {
            errval(curra[l++]);
        }
        while(l > c.a) {
            addval(curra[--l]);
        }
        ans[c.id] = get();
    }
    
    
    
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeIntFast(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
