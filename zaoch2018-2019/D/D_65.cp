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
    
    static int getChar(){
        return is() ? ib[ic++] : -1;
    }
    static int getCharNoP(){
        return is() ? ib[ic] : -1;
    }
    
    static void pp(){
        char c = getCharNoP();
        while(c != -1 && c <= 32) {
            ic++;
            c = getCharNoP();
        }
    }
    static char readChar(){
        pp();
        int r = getChar();
        while(r != -1 && r <= 32) {
            r = getChar();
        }
        return r;
    }
    static long long readLL(){
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
    
    
    static void flush(){
        if(oc) {
            fwrite(ob, 1, oc, stdout);
            oc = 0;
        }
    }
    
    static void writeChar(int c) {
        if(oc == bs) {
            flush();
        }
        ob[oc++] = c;
    }
    
    static void writeStr(const char *s) {
        while(*s)
            writeChar(*s++);
    }
    static void writeLL(long long a) {
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
const int MN = 5e5 + 123, MQ = 25e4 + 11, QDEK = 12512;
const int DECSIZE = 1000, DECCNT = 501;
int curra[MN];
int ans[MQ];

struct que{
    int a, b, id;
    que(){};
    inline que(int id, int a, int b): a(a), b(b), id(id){};
};
inline bool operator<(const que &a, const que &b) {
    return a.a / DECSIZE == b.a / DECSIZE ? a.b < b.b : a.a / DECSIZE < b.a / DECSIZE;
}

que change_gueries[QDEK];
int ch_que_sz = 0;

const int MEXMN = 711;
pii c[MQ];
struct mex{
    int cnt[MN];
    int up[MEXMN];
    
    inline void clear() {
        memset(cnt, 0, sizeof(cnt));
        memset(up, 0, sizeof(up));
    }
    
    inline void usedadd(int val) {
        up[val / MEXMN]++;
    }
    
    inline void usederr(int val) {
        up[val / MEXMN]--;
    }
    
    inline void add(int a) {
        if(!(cnt[a]++))
            usedadd(a);
    }
    inline void erase(int a) {
        if(!(--cnt[a]))
            usederr(a);
    }
    inline void ch_ai(int a, int b) {
        erase(curra[a]);
        curra[a] = b;
        add(curra[a]);
    }
    
    inline int get(int id, int l, int r){
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
        
        for(int i = 0; i < MEXMN; ++i) {
            if(up[i] < MEXMN) {
                for(int j = i * MEXMN; j < (i + 1) * MEXMN; ++j) {
                    if(cnt[j] == 0) {
                        while(cit--) {
                            ch_ai(c[cit].x, c[cit].y);
                        }
                        return j;
                    }
                }
            }
        }
        exit(2);
    }
} curr_mex;


int spec[DECSIZE + 12];
que allq[MQ];
int alls = 0, allc = 0;
struct decq{
    int l, r;
    int id;
    
    inline void processR(int nr) {
        while(nr > r) {
            curr_mex.add(curra[r++]);
        }
    }
    inline void processL(int nl) {
        while(nl < l) {
            curr_mex.add(curra[--l]);
        }
        while(nl > l) {
            curr_mex.erase(curra[l++]);
        }
    }
    
    inline void ch_ai(int a, int b) {
        curra[a] = b;
    }
    
    inline void spec_prep(que &cur) {
        memset(spec, 0, sizeof(spec));
        
        int ch_it = 0;
        int cit = 0;
        while(ch_it < ch_que_sz && change_gueries[ch_it].id < cur.id) {
            int p = change_gueries[ch_it].a;
            int v = change_gueries[ch_it++].b;
            if(p >= cur.a && p < cur.b) {
                c[cit++] = {p, curra[p]};
                ch_ai(p, v);
            }
        }
        
        for(int i = cur.a; i < cur.b; ++i) {
            if(curra[i] <= DECSIZE) {
                spec[curra[i]]++;
            }
        }
        
        for(int i = 0; i < DECSIZE + 12; ++i) {
            if(spec[i] == 0) {
                while(cit--) {
                    ch_ai(c[cit].x, c[cit].y);
                }
                ans[cur.id] = i;
                return;
            }
        }
        exit(-1);
    }
    
    inline void process(){
        curr_mex.clear();
        while(allc < alls && allq[allc].a / DECSIZE == id) {
            auto i = allq[allc++];
            if(i.b <= (id + 1) * DECSIZE) {
                spec_prep(i);
                continue;
            }
            
            processL(i.a);
            processR(i.b);
            ans[i.id] = curr_mex.get(i.id, i.a, i.b);
        }
    }
} queries[DECCNT];

void sol(){
    sort(allq, allq + alls);
    for(int i = 0; i < DECCNT; ++i) {
        queries[i].id = i;
        queries[i].r = queries[i].l = (i + 1) * DECSIZE;
        queries[i].process();
    }
    for(int i = 0; i < ch_que_sz; ++i) {
        curra[change_gueries[i].a] = change_gueries[i].b;
    }
    ch_que_sz = 0;
    alls = 0;
    allc = 0;
}
const int DS = 5001;
int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    // auto ts = clock();
    int n = (int)io::readLL();
    int q = (int)io::readLL();
    
    memset(ans, -1, sizeof(ans));
    memset(curra, -1, sizeof(curra));
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
        } else if(t == '!') {
            change_gueries[ch_que_sz++] = (que(i, a, b));
            if(ch_que_sz == DS) {
                sol();
            }
        } else {
            exit(1);
        }
    }
    sol();
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeLL(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
    // cerr << "Slow: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
