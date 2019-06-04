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

#define FAST_ALLOCATOR_MEMORY 2e9

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

#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>

mt19937 rd;
const int INF = 1e9;
namespace seg {
    struct node{
        int pos, maxVal, p, c;
        multiset<int> val;
        node *cl, *cr;
        
        node(){};
        node(int pos, int val) {
            p = rd();
            this->pos = pos;
            this->maxVal = val;
            this->val.clear();
            this->val.insert(val);
            cl = cr = NULL;
        }
    };
    inline int gv(node *r) {
        return r ? r->maxVal : 0;
    }
    inline void upd(node *e) {
        if(e) {
            e->maxVal = max(*e->val.rbegin(), max(gv(e->cl), gv(e->cr)));
        }
    }
    
    inline node *un(node *l, node *r) {
        if(!l || !r)
            return r ? r : l;
        if(l->p > r->p) {
            l->cr = un(l->cr, r);
            upd(l);
            return l;
        } else {
            r->cl = un(l, r->cl);
            upd(r);
            return r;
        }
    }
    inline void spl(node *r, node *&le, node *&re, int pos) {
        if(!r) {
            le = re = 0;
            return;
        } else if(r->pos < pos){
            spl(r->cr, r->cr, re, pos);
            upd(r);
            le = r;
        } else {
            spl(r->cl, le, r->cl, pos);
            upd(r);
            re = r;
        }
    }
    inline void ers(node *&r, int pos) {
        if(!r) return;
        if(r->pos == pos) {
            r = un(r->cl, r->cr);
        } else if(pos < r->pos) {
            ers(r->cl, pos);
        } else {
            ers(r->cr, pos);
        }
    }
    
    void st(node *&ro, int pos, int val, int p) {
        node *le, *re;
        spl(ro, le, re, pos);
        spl(re, ro, re, pos + 1);
        if(ro) {
            if(p > 0) {
                ro->val.insert(val);
            } else {
                ro->val.erase(ro->val.lower_bound(val));
                if(ro->val.size() == 0) {
                    delete ro;
                    ro = NULL;
                }
                
            }
            upd(ro);
            le = un(le, ro);
            ro = un(le, re);
        } else {
            if(p < 0) {
                exit(-1);
            }
            node *c = new node(pos, val);
            le = un(le, c);
            ro = un(le, re);
        }
    }
    
    
    int que(node *ro, int r) {
        if(!ro) return INF;
        while(1) {
            if(ro->cl && ro->cl->maxVal > r) {
                ro = ro->cl;
            } else if(*ro->val.rbegin() > r) {
                return ro->pos;
            } else if(ro->cr && ro->cr->maxVal > r) {
                ro = ro->cr;
            } else {
                return INF;
            }
        }
    }
}

const int MN = 5e5 + 11;
seg::node *ftree[MN], *spec;

void add(int tpos, int pos, int val, int p, int rp) {
    if(tpos == 0) {
        seg::st(spec, pos, val, p);
        return;
    }
    for(int i = tpos; i < rp; i |= i + 1) {
        seg::st(ftree[i], pos, val, p);
    }
}

int gt(int l, int r) {
    int ans = MN;
    for(int i = l; i >= 0; i = (i & (i + 1)) - 1) {
        ans = min(ans, seg::que(ftree[i], r));
    }
    ans = min(ans, seg::que(spec, r));
    return ans;
}

set<int> elDec[MN];

int in[MN];
int valNext[MN], val0next[MN];

void ch(int pos, int val, int p) {
    auto &cu = elDec[val];
    auto itl = cu.lower_bound(pos);
    auto tlr = cu.upper_bound(pos);
    int nxt = MN;
    if(tlr != cu.end()) {
        nxt = *tlr;
    }
    if(p < 0) {
        if(itl != cu.begin()) {
            auto it2 = itl;
            it2--;
            int c = *it2;
            if(c) {
                if(valNext[c] != pos) {
                    exit(-1);
                }
                add(c, val, valNext[c], -1, valNext[c]);
                valNext[c] = nxt;
                add(c, val, valNext[c], 1, valNext[c]);
            } else {
                add(0, val, val0next[val], -1, val0next[val]);
                val0next[val] = nxt;
                add(0, val, val0next[val], 1, val0next[val]);
            }
        }
        add(pos, val, valNext[pos], -1, valNext[pos]);
        cu.erase(pos);
    } else {
        if(itl != cu.begin()) {
            auto it2 = itl;
            --it2;
            int c = *it2;
            if(c) {
                if(valNext[c])
                    add(c, val, valNext[c], -1, valNext[c]);
                valNext[c] = pos;
                add(c, val, valNext[c], 1, valNext[c]);
            } else {
                if(val0next[val])
                    add(0, val, val0next[val], -1, val0next[val]);
                val0next[val] = pos;
                add(0, val, val0next[val], 1, val0next[val]);
            }
        }
        if(pos) {
            valNext[pos] = nxt;
        } else {
            val0next[val] = nxt;
        }
        add(pos, val, nxt, 1, nxt);
        cu.insert(pos);
    }
}

int last[MN];
int32_t main() {
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    
    auto ts = clock();
    int n, queries;
    n = io::readIntFast();
    queries = io::readIntFast();
    
    for(int i = 0; i < n; ++i) {
        in[i] = io::readIntFast();
        ch(last[in[i]], in[i], 1);
        last[in[i]] = i + 1;
    }
    for(int i = 0; i < n + 1; ++i) {
        ch(last[i], i, 1);
    }
    cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
    for(int i = 0; i < queries; ++i) {
        int l, r;
        char t;
        t = io::readChar();
        l = io::readIntFast();
        r = io::readIntFast(); l--;
        if(t == '?') {
            io::writeIntFast(gt(l, r));
            io::writeChar('\n');
        } else {
            int old = in[l];
            in[l] = r;
            if(old == r) continue;
            ch(l + 1, old, -1);
            ch(l + 1, r, 1);
        }
    }
    io::flush();
    cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
