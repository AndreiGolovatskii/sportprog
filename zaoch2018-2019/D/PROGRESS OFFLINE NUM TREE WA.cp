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
#include <unordered_map>
#include <bitset>
#include <deque>
#include <complex>
#include <cmath>

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
// #define FAST_ALLOCATOR_MEMORY 2e8

#ifdef FAST_ALLOCATOR_MEMORY // 2e8
int allocator_pos = 0;
char allocator_memory[(int)FAST_ALLOCATOR_MEMORY];
inline void * operator new ( size_t n ) {
    char *res = allocator_memory + allocator_pos;
    allocator_pos += n;
    assert(allocator_pos <= (int)FAST_ALLOCATOR_MEMORY);
    return (void *)res;
}
inline void operator delete ( void * ) noexcept { }
//inline void * operator new [] ( size_t ) { assert(0); }
//inline void operator delete [] ( void * ) { assert(0); }
#endif


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
#define pii pair<int, int>
#define x first
#define y second
#define mp make_pair
#define ll long long
using namespace std;

const int MB = 19, MN = 5e5 + 11;
const int MEV = 4 * 25e4 + 11, MQ = 25e4 + 11;
int buf[MN];
int Gtree[1 << (MB + 1)];
    
struct bx {
    inline void clear(){
        memset(::Gtree, 0, sizeof(::Gtree));
    }
    inline void insert(int pos, int val) {
        pos += 1 << MB;
        ::Gtree[pos] = val;
        pos >>= 1;
        while(pos) {
            ::Gtree[pos] = max(::Gtree[pos << 1], ::Gtree[(pos << 1) + 1]);
            pos >>= 1;
        }
    }
    inline int __get(int pos, int l, int val, int cl, int cr) {
        if(cl > l) return 0;
        if(cr <= l + 1) return ::Gtree[pos] > val;
        return __get(pos << 1, l, val, cl, (cr + cl) >> 1)
        || __get((pos << 1) + 1, l, val, (cr + cl) >> 1, cr);
    }
    
    inline int get(int l, int val) {
        return(__get(1, l, val, 0, 1 << MB));
    }
    inline int find_min_that_no_less(int r) {
        int cur = 1;
        int lg = 0, rg = 1 << MB;
        while(rg - lg > 1) {
            if(::Gtree[cur << 1] >= r) {
                cur <<= 1;
                rg -= (rg - lg) >> 1;
            } else {
                cur = (cur << 1) + 1;
                lg += (rg - lg) >> 1;
            }
        }
        return lg;
    }
    inline int __max(int seg, int l, int r, int pref) {
        if(l > pref)
            return 0;
        if(r <= pref) 
            return ::Gtree[seg];
        if(r - l == 1) 
            return 0;
        return max(__max(seg << 1, l, (r + l) >> 1, pref),
             __max((seg << 1) + 1, (r + l) >> 1, r, pref));
    }

    inline int pref_max(int pref) {
        int r = __max(1, 0, 1 << MB, pref);
        return r;
    }
    inline void build(int n) {
        for(int i = 0; i < n; ++i) {
            ::Gtree[(1 << MB) + i] = buf[i];
        }
        for(int i = (1 << MB) - 1; i > 0; --i) {
            ::Gtree[i] = max(::Gtree[i << 1], ::Gtree[(i << 1) + 1]);
        }
    }
} tree;

#define TYPE_SET -1
#define TYPE_ADD -2
#define TYPE_ERR -3
struct ev{
    int t, pos, val;
    ev(){};
    ev(int t, int pos, int val) {
      this->t = t;
      this->pos = pos;
      this->val = val;
   }
};
ev eventsALL[MEV], eventsFIRST[2 * MQ];
int __first_it = 0, __all_it = 0;
int in[MN], inc[MN];
int ans[MN];

inline void solFIRST(int n) {
    for(int i = 0; i < MN; ++i) {
        buf[i] = MN;
    }
    for(int i = n - 1; i >= 0; --i) {
        buf[in[i]] = i;
    }
    tree.clear();
    tree.build(n);
    for(int i = 0; i < __first_it; ++i) {
        auto &c = eventsFIRST[i];
        if(c.t == TYPE_SET) {
            tree.insert(c.pos, c.val);
        } else {
            ans[c.t] = min(ans[c.t], tree.find_min_that_no_less(c.val));
        }
    }
}
struct sb{
    int col, l, r;
    sb(){};
    sb(int col, int l, int r): col(col), l(l), r(r){};
};
inline bool operator<(const sb &a, const sb &b) {
    return a.col < b.col;
}

vector<sb> tree2[1 << (MB + 1)];
vector<ev> segQues[1 << (MB + 1)];
inline void solSeg(int seg, int l, int r) {
    if(r - l == 1) {
        for(auto i : segQues[seg]) {
            if(i.t > 0) {
                ans[i.t] = min(ans[i.t], l);
            }
        }
    } else {
        for(auto &i : tree2[seg]) {
            if(i.col < (r + l) >> 1) {
                tree2[(seg << 1)].push_back(i);
            } else {
                tree2[(seg << 1) + 1].push_back(i);
            }
        }
        tree2[seg].clear();
        for(auto &i : tree2[seg << 1]) {
            tree.insert(i.l, i.r);
        }
        int it = 0;
        for(auto &c : segQues[seg]) {
            if(c.t > 0) {
                if(tree.pref_max(c.pos) >= c.val) {
                    segQues[seg << 1].push_back(c);
                } else {
                    segQues[(seg << 1) + 1].push_back(c);
                }
            } else {
                if(-c.t < (r + l) >> 1) {
                    buf[it++] = c.pos;
                    tree.insert(c.pos, c.val);
                    segQues[seg << 1].push_back(c);
                } else {
                    segQues[(seg << 1) + 1].push_back(c);
                }
            }
        }
        segQues[seg].clear();
        for(int i = 0; i < it; ++i) {
            tree.insert(buf[i], 0);
        }
        for(auto &i : tree2[seg << 1]) {
            tree.insert(i.l, 0);
        }
        solSeg(seg << 1, l, (l + r) >> 1);
        solSeg((seg << 1) + 1, (l + r) >> 1, r);
    }
}

inline void solSECOND(int n) {
    memset(buf, -1, sizeof(buf));
    for(int i = 0; i < n; ++i) {
        if(buf[in[i]] >= 0) {
            tree2[1].push_back(sb(in[i], buf[in[i]], i));
        }
        buf[in[i]] = i;
    }
    for(int i = 0; i < MN; ++i) {
        if(buf[i] >= 0) {
            tree2[1].push_back(sb(i, buf[i], MN));
        }
    }
    sort(tree2[1].begin(), tree2[1].end());
    tree.clear();
    for(int i = 0; i < __all_it; ++i) {
        segQues[1].push_back(eventsALL[i]);
    }
    solSeg(1, 0, 1 << MB);
}

set<int> elDec[MN];
inline void ch(int pos, int dval, int p) {
    auto &cu = elDec[dval];
    auto itl = cu.lower_bound(pos);
    if(p > 0) {
        int nxt = MN;
        if(itl != cu.end()) {
            nxt = *itl;
        }
        if(itl != cu.begin()) {
            auto itp = itl;
            itp--;
            eventsALL[__all_it++] = ev(-dval, *itp, pos);
        } else {
            eventsFIRST[__first_it++] = ev(TYPE_SET, dval, pos);
        }
        eventsALL[__all_it++] = ev(-dval, pos, nxt);
        cu.insert(pos);
    } else {
        int nxt = MN;
        auto tl = itl, tr = itl;
        tr++;
        if(tr != cu.end()) {
            nxt = *tr;
        }
        if(itl != cu.begin()) {
            tl--;
            eventsALL[__all_it++] = ev(-dval, *tl, nxt);
        } else {
            eventsFIRST[__first_it++] = ev(TYPE_SET, dval, nxt);
        }
        eventsALL[__all_it++] = ev(-dval, pos, 0);
        cu.erase(itl);
    }
}


int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    auto ts = clock();
    int n, q;
    n = io::readIntFast();
    q = io::readIntFast();
    
    memset(ans, -1, sizeof(ans));
    for(int i = 0; i < n; ++i) {
        in[i] = io::readIntFast();
        inc[i] = in[i];
        elDec[in[i]].insert(i);
    }
    
    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
    for(int i = 0; i < q; ++i) {
        int l, r;
        char t;
        t = io::readChar();
        l = io::readIntFast();
        r = io::readIntFast(); l--;
        if(t == '?') {
            ans[i + 1] = MN;
            eventsALL[__all_it++] = ev(i + 1, l, r);
            eventsFIRST[__first_it++] = ev(i + 1, l, r);
        } else {
            int old = in[l];
            in[l] = r;
            if(old == r) continue;
            ch(l, old, -1);
            ch(l, r, 1);
        }
    }
    memcpy(in, inc, sizeof(in));
    solFIRST(n);

    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
    solSECOND(n);

    for(int i = 0; i <= q; ++i) {
        if(ans[i] >= 0) {
            io::writeIntFast(ans[i]);
            io::writeChar('\n');
        }
    }

    io::flush();
    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
