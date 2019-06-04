#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#define FAST_ALLOCATOR_MEMORY 2e8

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
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>

const int INF = 1e9, MN = 5e5 + 11;
mt19937 rnd(time(0));
const int MNDES = 1e7;
struct node{
    int key, val, mval, p;
    int cl, cr;
    node(){};
    node(int key, int val) {
        this->key = key;
        this->val = val;
        this->mval = val;
        this->p = rnd();
        cl = cr = 0;
    }
}nr[MNDES];
int nodeit = 1;
int st[MN];
class decTree{
private:
    int root;
    inline int getVal(int r) {
        return r ? nr[r].mval : 0;
    }
    inline void upd(int r) {
        if(r) {
            nr[r].mval = max(nr[r].val, max(getVal(nr[r].cl), getVal(nr[r].cr)));
        }
    }
    		
    inline int merge(int l, int r) {
        if(!l || !r) return l ? l : r;
        else if(nr[l].p < nr[r].p) {
            nr[l].cr = merge(nr[l].cr, r);
            upd(l);
            return l;
        } else {
            nr[r].cl = merge(l, nr[r].cl);
            upd(r);
            return r;
        }
    }
    inline void __insert(int &ro, int nn) {
        if(!ro) ro = nn;
        else if(nr[nn].p < nr[ro].p) {
            int le, re;
            split(ro, le, re, nr[nn].key);
            nr[nn].cl = le;
            nr[nn].cr = re;
            upd(nn);
            ro = nn;
        } else if(nr[nn].key < nr[ro].key){
            __insert(nr[ro].cl, nn);
            upd(ro);
        } else {
            __insert(nr[ro].cr, nn);
            upd(ro);
        }
    }
    inline void __erase(int &ro, int key) {
        if(!ro) return;
        if(nr[ro].key == key) {
            ro = merge(nr[ro].cl, nr[ro].cr);
        } else if(nr[ro].key > key) {
            __erase(nr[ro].cl, key);
            upd(ro);
        } else {
            __erase(nr[ro].cr, key);
            upd(ro);
        }
    }
    inline int nnode(int key, int val) {
        assert(nodeit < MNDES);
        nr[nodeit] = node(key, val);
        return nodeit++;
    }
public:
    inline void build(const std::vector<pii> &in) {
        root = 0;
        int stit = 0;
        for(auto i : in) {
            int nn = nnode(i.x, i.y);
            while(stit && nr[st[stit - 1]].p > nr[nn].p) {
                nr[nn].cl = st[stit - 1];
                upd(st[stit - 1]);
                stit--;
            }
            if(stit) nr[st[stit - 1]].cr = nn;
            st[stit++] = nn;
        }
        while(stit) root = st[stit - 1], upd(root), stit--;
    }
    inline void insert(int key, int val) {
        int nn = nnode(key, val);
        __insert(root, nn);
    }
    inline void erase(int key) {
        __erase(root, key);
    }
    inline void set(int key, int val) {
        int ro = root;
        int stit = 0;
        while(nr[ro].key != key) {
            st[stit++] = ro;
            if(nr[ro].key > key) {
                ro = nr[ro].cl;
            } else if(nr[ro].key < key) {
                ro = nr[ro].cr;
            } else {
                assert(0);
            }
        }
        nr[ro].val = val;
        st[stit++] = ro;
        while(stit) upd(st[stit - 1]), stit--;
    }
    inline char prefCheck(int rkey, int rval) {
        int cur = root;
        while(cur) {
            if(nr[cur].key > rkey) {
                cur = nr[cur].cl;
            } else {
                if(getVal(nr[cur].cl) > rval || nr[cur].val > rval) return 1;
                cur = nr[cur].cr;
            }
        }
        return 0;
    }
    inline int prefMin(int rval) {
        int ro = root;
        while(ro) {
            if(getVal(nr[ro].cl) > rval) {
                ro = nr[ro].cl;
            } else if(nr[ro].val > rval) {
                return nr[ro].key;
            } else {
                ro = nr[ro].cr;
            }
        }
        return INF;
    }
    decTree(){
        root = 0;
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
    
    auto ts = clock();
    int n, q;
    n = io::readIntFast();
    q = io::readIntFast();
    
    for(int i = 0; i < n; ++i) {
        in[i] = io::readIntFast();
        elDec[in[i]].insert(i + 1);
    }
    
    seg *root = build(0, MN);
    // cerr << "Slow: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
    
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
    // cerr << "Slow: " << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
