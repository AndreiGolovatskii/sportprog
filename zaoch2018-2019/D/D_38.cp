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
const int MN = 5e5 + 123, MQ = 25e4 + 11, MCQ = 5e4 + 11;;
const int DECSIZE = 750;
//int a[MN];
int curra[MN];
int ans[MQ];
#define ULLONG_MAX (-1LL)



struct que{
    int a, b, id;
    que(){};
    que(int id, int a, int b): a(a), b(b), id(id){};
};
bool operator<(const que &a, const que &b) {
    return a.b < b.b;
}

que change_gueries[MCQ];
int ch_que_sz = 0;

const int MEXMN = MN / 64 + 1, MEXMQ = MEXMN / 64 + 1;
pii c[MQ];
struct mex{
    int cnt[MN];
    
    unsigned ll used[MEXMN];
    unsigned ll up[MEXMQ];
    
    inline void clear() {
        memset(cnt, 0, sizeof(cnt));
        memset(used, 0, sizeof(used));
        memset(up, 0, sizeof(up));
    }
    
    inline void usedadd(int val) {
        int pos = val / 64;
        int re = (val & 63);
        used[pos] ^= 1LL << re;
        
        int np = pos / 64;
        if(used[pos] == ULLONG_MAX) {
            up[np] |= 1LL << (pos & 63);
        } else {
            up[np] &= ULLONG_MAX - (1LL << (pos & 63));
        }
    }
    
    inline void add(int a) {
        if(a < 0) return;
        if(cnt[a] == 0) {
            usedadd(a);
        }
        cnt[a]++;
    }
    inline void erase(int a) {
        if(a < 0) return;
        if(cnt[a] == 1) {
            usedadd(a);
        }
        cnt[a]--;
    }
    inline pii ch_ai(int a, int b) {
        erase(curra[a]);
        int c = curra[a];
        curra[a] = b;
        add(curra[a]);
        return {a, c};
    }
    inline int first_byte(unsigned ll a) {
        int c = 0;
        while(a & 1) {
            a >>= 1;
            c++;
        }
        return c;
    }
    inline int get(int id, int l, int r){
        int ch_it = 0;
        int cit = 0;
        while(ch_it < ch_que_sz && change_gueries[ch_it].id < id) {
            int p = change_gueries[ch_it].a;
            int v = change_gueries[ch_it].b;
            if(p >= l && p < r) {
                c[cit++] = ch_ai(p, v);
            }
            ch_it++;
        }
        
        
        for(int i = 0; i < MEXMQ; ++i) {
            if(up[i] != ULLONG_MAX) {
                int np = (i << 6) + first_byte(up[i]);
                int pos = (np << 6) + first_byte(used[np]);
                
                while(cit--) {
                    ch_ai(c[cit].x, c[cit].y);
                }
                return pos;
            }
        }
        exit(2);
    }
} curr_mex;


int spec[DECSIZE + 12];
struct decq{
    vector<que> ques;
    int l, r;
    int id;
    
    inline void processR(int nr) {
        //        if(nr < r) exit(3);
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
    
    
    inline pii ch_ai(int a, int b) {
        int c = curra[a];
        curra[a] = b;
        return {a, c};
    }
    
    inline void spec_prep(que &cur) {
        memset(spec, 0, sizeof(spec));
        
        int ch_it = 0;
        int cit = 0;
        while(ch_it < ch_que_sz && change_gueries[ch_it].id < cur.id) {
            int p = change_gueries[ch_it].a;
            int v = change_gueries[ch_it].b;
            if(p >= cur.a && p < cur.b) {
                c[cit++] = ch_ai(p, v);
            }
            ch_it++;
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
        if(!ques.size())
            return;
        sort(ques.begin(), ques.end());
        curr_mex.clear();
        for(auto &i : ques) {
            
            if(i.b < (id + 1) * DECSIZE) {
                spec_prep(i);
                continue;
            }
            
            processL(i.a);
            processR(i.b);
            ans[i.id] = curr_mex.get(i.id, i.a, i.b);
        }
    }
    decq(){};
} queries[DECSIZE];


int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    //
    //    auto ts = clock();
    
    int n = io::readLL();
    int q = io::readLL();
    
    memset(ans, -1, sizeof(ans));
    memset(curra, -1, sizeof(curra));
    for(int i = 0; i < n; ++i) {
        curra[i] = io::readLL();
    }
    for(int i = 0; i < q; ++i) {
        char t = io::readChar();
        int a = io::readLL();
        int b = io::readLL();
        if(t == '?') {
            a--;
            int pos = a / DECSIZE;
            queries[pos].ques.push_back(que(i, a, b));
        } else if(t == '!') {
            a--;
            change_gueries[ch_que_sz++] = (que(i, a, b));
        } else {
            exit(1);
        }
    }
    for(int i = 0; i < DECSIZE; ++i) {
        queries[i].id = i;
        queries[i].l = (i + 1) * DECSIZE;
        queries[i].r = (i + 1) * DECSIZE;
        queries[i].process();
    }
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeLL(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
    //    cerr << ((double)clock() - ts) / CLOCKS_PER_SEC << "\n";
}
