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
    static inline long long readLL(){
        pp();
        long long r = 0;
        int c = getChar();
        int b = 0;
        if(c == '-') {
            b = 1;
        }
        
        while(c >= '0' && c <= '9') {
            r = r * 10 + c - '0';
            c = getChar();
        }
        if(b) r = -r;
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
    static inline void writeLL(long long a) {
        if(a < 0) {
            a = -a;
        }
        if(!a) {
            writeChar('0');
            return;
        }
        char s[24];
        int n = 0;
        while(a) s[n++] = '0' + a % 10, a/= 10;
        while(n--) writeChar(s[n]);
    }
    
    
}
//end fasat io


using namespace std;
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>
const int MN = 5e5 + 12, MQ = 25e4 + 11, MQC = 5e4 + 11;
const int DECSIZEMAX = 4000, DECSIZEMIN = 250;
int curra[MN];
int ans[MQ];

struct que{
    int a, b, id;
    que(){};
    inline que(int id, int a, int b): a(a), b(b), id(id){};
};
int TMPDECSIZE;
inline bool operator<(const que &a, const que &b) {
    int at = a.a / TMPDECSIZE;
    int bt = b.a / TMPDECSIZE;
    return at ^ bt ? at < bt : a.b < b.b;
}

que change_gueries[MQC];
int ch_que_sz = 0;

const int MEXMN = 711;
pii c[MQ];
namespace curr_mex{
    int cnt[MN];
    int up[MEXMN];
    
    inline void clear() {
        memset(cnt, 0, sizeof(cnt));
        memset(up, 0, sizeof(up));
    }
    
    inline void add(int a) {
        if(!(cnt[a]++))
            up[a / MEXMN]++;
    }
    inline void erase(int a) {
        if(!(--cnt[a]))
            up[a / MEXMN]--;
    }
    inline void ch_ai(int a, int b) {
        erase(curra[a]);
        curra[a] = b;
        add(curra[a]);
    }
    
    inline void get(int id, int l, int r){
        int ch_it = 0;
        int cit = 0;
        while(ch_it < ch_que_sz && change_gueries[ch_it].id < id) {
            int p = change_gueries[ch_it].a;
            int v = change_gueries[ch_it++].b;
            if(p >= l && p < r) {
                c[cit++] = {p, curra[p]};
                ch_ai(p, v);
            }
        }
        
        for(int i = 0;; ++i) {
            if(up[i] < MEXMN) {
                for(int j = i * MEXMN;; ++j) {
                    if(cnt[j] == 0) {
                        while(cit--) {
                            ch_ai(c[cit].x, c[cit].y);
                        }
                        ans[id] = j;
                        return;
                    }
                }
            }
        }
        exit(2);
    }
};


que allq[MQ];
int alls = 0, allc = 0;
int n;
namespace queries{
    int l, r;
    int id;
    
    inline void processR(int nr) {
        while(nr > r)
            curr_mex::add(curra[r++]);
    }
    inline void processL(int nl) {
        while(nl < l)
            curr_mex::add(curra[--l]);
        while(nl > l)
            curr_mex::erase(curra[l++]);
    }
    
    inline void process(){
        curr_mex::clear();
        l = id * TMPDECSIZE;
        r = id * TMPDECSIZE;
        id++;
        que i;
        while(allq[allc].a < TMPDECSIZE * id) {
            i = allq[allc++];
            processL(i.a);
            processR(i.b);
            
            curr_mex::get(i.id, i.a, i.b);
        }
    }
}


inline int getTmpSize() {
    ld one = 1.0;
    int r = (int)sqrt(n * one / alls * n);
    return TMPDECSIZE = r;
}

inline void sol() {
    sort(allq, allq + alls);
    allq[alls].a = allq[alls].b = 1e9;
    queries::id = 0;
    while(allc < alls) {
        queries::process();
    }
    for(int i = 0; i < ch_que_sz; ++i)
        curra[change_gueries[i].a] = change_gueries[i].b;
    allc = alls = ch_que_sz = 0;
}

int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    auto ts = clock();
    n = (int)io::readLL();
    int q = (int)io::readLL();
    
    memset(ans, -1, sizeof(ans));
    
    for(int i = 0; i < n; ++i) {
        curra[i] = (int)io::readLL();
    }
    for(int i = 0; i < q; ++i) {
        char t = io::readChar();
        int a = (int)io::readLL();
        int b = (int)io::readLL();
        a--;
        
        if(t == '?') {
            allq[alls++] = que(i, a, b);
        }
        else {
            change_gueries[ch_que_sz++] = (que(i, a, b));
        }
        if(2 * (ll)ch_que_sz * alls >= (ll)alls * getTmpSize()) {
            sol();
        }
    }
    
    getTmpSize();
    sol();
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeLL(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
    cerr << "Slow: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
