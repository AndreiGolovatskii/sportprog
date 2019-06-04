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

mt19937 rd;
const int INF = 1e9;
struct decTree {
    struct node{
        node *cl, *cr;
        int pos, maxVal, p, val;
        node(){};
        node(int pos, int val) {
            p = rd();
            this->pos = pos;
            this->val = this->maxVal = val;
            cl = cr = NULL;
        }
    };
    node *root;
    
    inline int gv(node *r) {
        return r ? r->maxVal : 0;
    }
    inline void upd(node *e) {
        if(e) {
            e->maxVal = max(e->val, max(gv(e->cl), gv(e->cr)));
        }
    }
    inline node *un(node *l, node *r) {
        if(!l || !r)
            return r ? r : l;
        if(l->p < r->p) {
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
            upd(r);
        } else {
            ers(r->cr, pos);
            upd(r);
        }
    }
    
    inline void genUpd(node *r) {
        if(r) {
            genUpd(r->cl);
            genUpd(r->cr);
            upd(r);
        }
    }
    inline void lineBuild(vector<pii> &in) {
        deque<node *> st;
        int n = (int)in.size();
        for(int i = 0; i < n; ++i) {
            node *nn = new node(in[i].x, in[i].y);
            while(st.size() && st.back()->p > nn->p) {
                nn->cl = st.back();
                st.pop_back();
            }
            if(st.size()){
                st.back()->cr = nn;
            }
            st.push_back(nn);
        }
        if(st.size())
            root = st.front();
        else
            root = NULL;
        genUpd(root);
    }
    inline int trFnd(int l, int r) {
        node *cur = root;
        while(cur) {
            if(cur->pos > l) {
                cur = cur->cl;
            } else if(cur->pos <= l) {
                if(gv(cur->cl) > r || cur->val > r) return 1;
                cur = cur->cr;
            }
        }
        return 0;
    }
    inline int findMinPos(int r) {
        node *cur = root;
        while(1) {
            if(cur->cl && cur->cl->maxVal > r) {
                cur = cur->cl;
            } else if(cur->val > r) {
                return cur->pos;
            } else if(cur->cr && cur->cr->maxVal > r){
                cur = cur->cr;
            } else {
                return INF;
            }
        }
    }
    inline void ers(int pos) {
        ers(root, pos);
    }
    inline void add(node *&ro, node *nn) {
        if(!ro) ro = nn;
        else if(nn->p < ro->p) {
            node *le, *re;
            spl(ro, le, re, nn->pos);
            nn->cl = le;
            nn->cr = re;
            upd(nn);
            ro = nn;
            return;
        } else if(nn->pos < ro->pos){
            add(ro->cl, nn);
            upd(ro);
        } else {
            add(ro->cr, nn);
            upd(ro);
        }
    }
    inline void add(int pos, int val) {
        node *nn = new node(pos, val);
        add(root, nn);
    }
    decTree(){
        root = 0;
    }
};
const int MN = 5e5 + 11;
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
        spec.add(i, cur[0].x);
    else
        spec.add(i, MN);
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

seg *build(int l, int r, int sk = 1) {
    seg *ro = new seg(l, r);
    if(r - l == 1) {
        ro->sorce = constr(l);
        if(!sk)
            ro->val.lineBuild(ro->sorce);
        return ro;
    }
    
    ro->cl = build(l, (r + l) >> 1, 0);
    ro->cr = build((r + l) >> 1, r, 1);
    
    ro->sorce.resize(ro->cl->sorce.size() + ro->cr->sorce.size());
    merge(ro->cl->sorce.begin(), ro->cl->sorce.end(), ro->cr->sorce.begin(), ro->cr->sorce.end(), ro->sorce.begin());
    ro->cl->sorce.clear();
    ro->cr->sorce.clear();
    if(!sk) {
        ro->val.lineBuild(ro->sorce);
    }
    return ro;
}

inline void erase(seg *ro, int pos, int st, int sk = 1) {
    if(ro->l > pos || ro->r <= pos) {
        return;
    } else {
        if(!sk)
            ro->val.ers(st);
        if(ro->cl) {
            erase(ro->cl, pos, st, 0);
            erase(ro->cr, pos, st, 1);
        }
    }
}
inline void add(seg *ro, int pos, int st, int val, int sk = 1) {
    if(ro->l > pos || ro->r <= pos) {
        return;
    } else {
        if(!sk)
            ro->val.add(st, val);
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
            erase(root, dval, *itp);
            add(root, dval, *itp, pos);
        } else {
            spec.ers(dval);
            spec.add(dval, pos);
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
            erase(root, dval, *tl);
            add(root, dval, *tl, nxt);
        } else {
            spec.ers(dval);
            spec.add(dval, nxt);
        }
        erase(root, dval, pos);
        cu.erase(itl);
    }
}



inline int gt(seg *root, int l, int r){
    while(root->cl) {
        if(root->cl->val.trFnd(l, r)) {
            root = root->cl;
        }else {
            root = root->cr;
        }
    }
    return min(root->l, spec.findMinPos(r));
}

int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    // auto ts = clock();
    int n, q;
    n = io::readIntFast();
    q = io::readIntFast();
    
    for(int i = 0; i < n; ++i) {
        in[i] = io::readIntFast();
        elDec[in[i]].insert(i + 1);
    }
    
    seg *root = build(0, MN);
    
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
