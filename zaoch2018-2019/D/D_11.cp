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
const int MN = 10000, MQ = 1000;
const int DECSIZE = 150;
int a[MN];
int curra[MN];
int ans[MN];

struct mex{
    int cnt[MN];
    bool used[MN];
    void clear() {
        memset(cnt, 0, sizeof(cnt));
        memset(used, 0, sizeof(used));
    }
    
    void add(int a) {
        if(a < 0) return;
        if(cnt[a] == 0) {
            used[a] = 1;
        }
        cnt[a]++;
    }
    void erase(int a) {
        if(a < 0) return;
        if(cnt[a] == 1) {
            used[a] = 0;
        }
        cnt[a]--;
    }
    int get(){
        for(int i = 0; i < MN; ++i) {
            if(!used[i]) {
                return i;
            }
        }
        exit(2);
    }
} curr_mex;


struct que{
    int a, b, id;
    que(){};
    que(int id, int a, int b): a(a), b(b), id(id){};
};
bool operator<(const que &a, const que &b) {
    return a.b < b.b;
}

vector<que> change_gueries;
int ch_que_sz;

struct decq{
    vector<que> ques;
    int l, r;
    
    
    void processR(int nr) {
        //        if(nr < r) exit(3);
        while(nr > r) {
            curr_mex.add(curra[r++]);
        }
        
        while(nr < r) {
            curr_mex.erase(curra[--r]);
        }
    }
    void processL(int nl) {
        while(nl < l) {
            curr_mex.add(curra[--l]);
        }
        while(nl > l) {
            curr_mex.erase(curra[l++]);
        }
    }
    void ch_ai(int a, int b) {
        curr_mex.erase(curra[a]);
        curra[a] = b;
        curr_mex.add(curra[a]);
    }
    
    void process(){
        if(!ques.size())
            return;
        sort(ques.begin(), ques.end());
        curr_mex.clear();
        memcpy(curra, a, sizeof(a));
        int ch_it = 0;
        for(auto &i : ques) {
            while(ch_it < ch_que_sz && change_gueries[ch_it].id < i.id) {
                ch_ai(change_gueries[ch_it].a, change_gueries[ch_it].b);
                ch_it++;
            }
            if(i.b < r) {
                r = i.b;
                l = i.b;
            }
            processL(i.a);
            processR(i.b);
            ans[i.id] = curr_mex.get();
        }
    }
} queries[DECSIZE];


int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    
    int n = io::readLL();
    int q = io::readLL();
    
    memset(ans, -1, sizeof(ans));
    memset(a, -1, sizeof(a));
    for(int i = 0; i < n; ++i) {
        a[i] = io::readLL();
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
            change_gueries.push_back(que(i, a, b));
        } else {
            exit(1);
        }
    }
    ch_que_sz = change_gueries.size();
    for(int i = 0; i < DECSIZE; ++i) {
        queries[i].l = (i + 1) * DECSIZE;
        queries[i].r = (i + 1) * DECSIZE + 1;
        queries[i].process();
    }
    
    for(int i = 0; i < q; ++i) {
        if(ans[i] != -1) {
            io::writeLL(ans[i]);
            io::writeChar('\n');
        }
    }
    
    
    io::flush();
}
