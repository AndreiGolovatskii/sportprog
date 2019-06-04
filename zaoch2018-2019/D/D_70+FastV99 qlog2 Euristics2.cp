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

const int INF = 1e9, MN = 5e5 + 11;
mt19937 rnd(time(0));
class decTree{
private:
    struct node{
        int key, val, mval, p;
        node *cl, *cr;
        node(){};
        node(int key, int val) {
            this->key = key;
            this->val = val;
            this->mval = val;
            this->p = rnd();
            cl = cr = NULL;
        }
    };
    node *root;
    inline int getVal(node *r) {
        return r ? r->mval : 0;
    }
    inline void upd(node *r) {
        if(r) {
            r->mval = max(r->val, max(getVal(r->cl), getVal(r->cr)));
        }
    }
    inline void split(node *ro, node *&l, node *&r, int key) {
        if(!ro) l = r = NULL;
        else if(ro->key > key) {
            split(ro->cl, l, ro->cl, key);
            upd(ro);
            r = ro;
        } else {
            split(ro->cr, ro->cr, r, key);
            upd(ro);
            l = ro;
        }
    }
    inline node *merge(node *l, node *r) {
        if(!l || !r) return l ? l : r;
        else if(l->p < r->p) {
            l->cr = merge(l->cr, r);
            upd(l);
            return l;
        } else {
            r->cl = merge(l, r->cl);
            upd(r);
            return r;
        }
    }
    inline void insert(node *&ro, node *nn) {
        if(!ro) ro = nn;
        else if(nn->p < ro->p) {
            node *le, *re;
            split(ro, le, re, nn->key);
            nn->cl = le;
            nn->cr = re;
            upd(nn);
            ro = nn;
        } else if(nn->key < ro->key){
            insert(ro->cl, nn);
            upd(ro);
        } else {
            insert(ro->cr, nn);
            upd(ro);
        }
    }
    inline void erase(node *&ro, int key) {
        if(!ro) return;
        if(ro->key == key) {
            ro = merge(ro->cl, ro->cr);
        } else if(ro->key > key) {
            erase(ro->cl, key);
            upd(ro);
        } else {
            erase(ro->cr, key);
            upd(ro);
        }
    }
public:
    inline void build(const vector<pii> &in) {
        root = NULL;
        stack<node*> st;
        for(auto i : in) {
            node *nn = new node(i.x, i.y);
            while(st.size() && st.top()->p > nn->p) {
                nn->cl = st.top();
                upd(st.top());
                st.pop();
            }
            if(st.size()) st.top()->cr = nn;
            st.push(nn);
        }
        while(st.size()) root = st.top(), upd(root), st.pop();
    }
    inline void insert(int key, int val) {
        node *nn = new node(key, val);
        insert(root, nn);
    }
    inline void erase(int key) {
        erase(root, key);
    }
    inline void set(int key, int val) {
        // erase(key);
        // insert(key, val);
        node *ro = root;
        stack<node*> st;
        while(ro->key != key) {
            st.push(ro);
            if(ro->key > key) {
                ro = ro->cl;
            } else if(ro->key < key) {
                ro = ro->cr;
            } else {
                assert(0);
            }
        }
        ro->val = val;
        st.push(ro);
        while(st.size()) upd(st.top()), st.pop();
    }
    inline char prefCheck(int rkey, int rval) {
        node *cur = root;
        while(cur) {
            if(cur->key > rkey) {
                cur = cur->cl;
            } else {
                if(getVal(cur->cl) > rval || cur->val > rval) return 1;
                cur = cur->cr;
            }
        }
        return 0;
    }
    inline int prefMin(int rval) {
        node *ro = root;
        while(ro) {
            if(getVal(ro->cl) > rval) {
                ro = ro->cl;
            } else if(ro->val > rval) {
                return ro->key;
            } else {
                ro = ro->cr;
            }
        }
        return INF;
    }
    decTree(){
        root = NULL;
    };
};
decTree spec;

set<int> elDec[MN];
int in[MN];
inline vector<pii> constr(int i){
    vector<pii> cur;
    for(auto j = elDec[i].begin(); j != elDec[i].end();) {
        int c = *j;
        j++;
        if(j == elDec[i].end())
            cur.push_back({c, MN});
        else
            cur.push_back({c, *j});
    }
    if(cur.size())
        spec.insert(i, cur[0].x);
    else
        spec.insert(i, MN);
    return cur;
}

struct seg{
    int l, r;
    seg *cl, *cr;
    vector<pii> sorce;
    decTree val;
    seg(){};
    seg(int l, int r) {
        this->l = l;
        this->r = r;
        cl = cr = NULL;
    }
};

const int CS = 3;
seg *build(int l, int r, int sk = 1) {
    seg *ro = new seg(l, r);
    if(r - l == 1) {
        ro->sorce = constr(l);
        if(!sk)
            ro->val.build(ro->sorce);
        return ro;
    }
    if(r - (r - l) / CS > 0 && (r + l) / CS - l > 0) {
        ro->cl = build(l, (r + l) / CS, 0);
        ro->cr = build((r + l) / CS, r, 1);
    } else {
        ro->cl = build(l, (r + l) / 2, 0);
        ro->cr = build((r + l) / 2, r, 1);
    }
    ro->sorce.resize(ro->cl->sorce.size() + ro->cr->sorce.size());
    merge(ro->cl->sorce.begin(), ro->cl->sorce.end(), ro->cr->sorce.begin(), ro->cr->sorce.end(), ro->sorce.begin());
    ro->cl->sorce.clear();
    ro->cr->sorce.clear();
    if(!sk) {
        ro->val.build(ro->sorce);
    }
    return ro;
}

inline void erase(seg *ro, int pos, int st, int sk = 1) {
    if(ro->l > pos || ro->r <= pos) {
        return;
    } else {
        if(!sk)
            ro->val.erase(st);
        if(ro->cl) {
            erase(ro->cl, pos, st, 0);
            erase(ro->cr, pos, st, 1);
        }
    }
}

inline void sv(seg *ro, int pos, int st, int val, int sk = 1) {
    if(ro->l > pos || ro->r <= pos) {
        return;
    } else {
        if(!sk)
            ro->val.set(st, val);
        if(ro->cl) {
            sv(ro->cl, pos, st, val, 0);
            sv(ro->cr, pos, st, val, 1);
        }
    }
}

inline void add(seg *ro, int pos, int st, int val, int sk = 1) {
    if(ro->l > pos || ro->r <= pos) {
        return;
    } else {
        if(!sk)
            ro->val.insert(st, val);
        if(ro->cl) {
            add(ro->cl, pos, st, val, 0);
            add(ro->cr, pos, st, val, 1);
        }
    }
}
inline void ch(int pos, int dval, int p, seg *root) {
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
            
            sv(root, dval, *itp, pos);
        } else {
            spec.set(dval, pos);
        }
        
        add(root, dval, pos, nxt);
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
            sv(root, dval, *tl, nxt);
        } else {
            spec.set(dval, nxt);
        }
        erase(root, dval, pos);
        cu.erase(itl);
    }
}
inline int gt(seg *root, int l, int r){
    while(root->cl) {
        if(root->cl->val.prefCheck(l, r)) {
            root = root->cl;
        } else {
            root = root->cr;
        }
    }
    return min(root->l, spec.prefMin(r));
}

int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    // auto ts = clock();
    int n, q;
    n = io::readIntFast();
    q = io::readIntFast();
    
    int am = 0;
    for(int i = 0; i < n; ++i) {
        in[i] = io::readIntFast();
        am = max(am, in[i]);
        elDec[in[i]].insert(i + 1);
    }
    
    seg *root = build(0, min(MN, am + (int)5e4 + 111));
    
    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
    for(int i = 0; i < q; ++i) {
        int l, r;
        char t;
        t = io::readChar();
        l = io::readIntFast();
        r = io::readIntFast(); l--;
        if(t == '?') {
            io::writeIntFast(gt(root, l, r));
            io::writeChar('\n');
        } else {
            int old = in[l];
            in[l] = r;
            if(old == r) continue;
            ch(l + 1, old, -1, root);
            ch(l + 1, r, 1, root);
        }
    }
    io::flush();
    // cerr << "Fast: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
