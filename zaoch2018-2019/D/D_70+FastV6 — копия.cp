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
int ch_que_sz = 0,  TMPDECSIZE;
int curra[MN], cnt[MN], up[(MN >> 9) + 1], ans[MQ];
pii c[MQ];

struct que{
    int a, b, id;
    que(){};
    inline que(int id, int a, int b): a(a), b(b), id(id){};
};
que allq[MQ], change_gueries[MQC];

inline bool operator<(const que &a, const que &b) {
    int at = a.a / TMPDECSIZE;
    int bt = b.a / TMPDECSIZE;
    return at ^ bt ? at < bt : a.b < b.b;
}
inline void clear() {
    memset(cnt, 0, sizeof(cnt));
    memset(up, 0, sizeof(up));
}

inline void add(int a) {
    if(!(cnt[a]++))
        up[a >> 9]++;
}
inline void erase(int a) {
    if(!(--cnt[a]))
        up[a >> 9]--;
}
inline void ch_ai(int a, int b) {
    erase(curra[a]);
    curra[a] = b;
    add(curra[a]);
}

inline void get(int id, int l, int r){
    int ch_it = 0;
    int cit = 0;
    while(change_gueries[ch_it].id < id) {
        int p = change_gueries[ch_it].a;
        int v = change_gueries[ch_it++].b;
        if(p >= l && p < r) {
            c[cit++] = {p, curra[p]};
            ch_ai(p, v);
        }
    }
    
    
    int i = -1;
    while(!(up[++i] ^ MEXMN));
    i <<= 9;
    i -= 1;
    while(cnt[++i]);
    ans[id] = i;
    while(cit--) {
        ch_ai(c[cit].x, c[cit].y);
    }
}



int alls = 0, allc = 0;
int n;

int qqq = 0;
inline int getTmpSize() {
    return TMPDECSIZE = (qqq ? n / qqq : n) + 1;
}

inline void sol() {
    sort(allq, allq + alls);
    allq[alls].a = allq[alls].b = MN << 1;
    change_gueries[ch_que_sz] = que(MN, MN, MN);
    int id = 0;
    while(allc < alls){
        clear();
        int l, r;
        l = r = id * TMPDECSIZE;
        
        id++;
        while(allq[allc].a < TMPDECSIZE * id) {
            que i = allq[allc++];
            while(i.a < l)
                add(curra[--l]);
            while(i.b > r)
                add(curra[r++]);
            while(i.a > l)
                erase(curra[l++]);
            
            get(i.id, i.a, i.b);
        }
        
    }
    for(int i = 0; i < ch_que_sz; ++i)
        curra[change_gueries[i].a] = change_gueries[i].b;
    qqq = allc = alls = ch_que_sz = 0;
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    auto ts = clock();
    n = io::readIntFast();
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
            allq[alls++] = que(i, a, b);
            if((qqq + 1) * (qqq + 1) < alls) qqq++;
        }
        else {
            change_gueries[ch_que_sz++] = que(i, a, b);
        }
        if(2 * (ll)ch_que_sz * alls > (ll)alls * getTmpSize()) {
            sol();
        }
    }
    
    getTmpSize();
    sol();
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeIntFast(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
    cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
