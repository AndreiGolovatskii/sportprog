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
    static const int bufSize = 4096;
    
    static unsigned char buf[bufSize];
    int sz = 0, it = 0;
    static inline bool isBuf(){
        if(it == sz) {
            it = 0;
            sz = (int)fread(buf, 1, bufSize, stdin);
            if(!sz) return 0;
        }
        return 1;
    }
    static inline int getChar(){
        return isBuf() ? buf[it++] : -1;
    }
    static inline int getCharNoP(){
        return isBuf() ? buf[it] : -1;
    }
    static inline void pp(){
        int c = getCharNoP();
        while(c <= 32) {
            it++;
            c = getCharNoP();
        }
    }
    static inline int readChar() {
        pp();
        int r = getChar();
        while(r <= 32 && r != -1) {
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
            c = getChar();
        }
        
        while(c >= '0' && c <= '9') {
            r = r * 10 + c - '0';
            c = getChar();
        }
        if(b) r = -r;
        return r;
    }
    
    static inline int readInt(){
        pp();
        int r = 0;
        
        int c = getChar();
        int b = 0;
        if(c == '-') {
            b = 1;
            c = getChar();
        }
        
        while(c >= '0' && c <= '9') {
            r = r * 10 + c - '0';
            c = getChar();
        }
        if(b) r = -r;
        return r;
    }
    
    
    static unsigned char o_buf[bufSize];
    int o_it = 0;
    
    static inline void writeChar(int c){
        if(o_it == bufSize) {
            fwrite(o_buf, 1, o_it, stdout);
            o_it = 0;
        }
        o_buf[o_it++] = c;
    }
    static inline void writeLL(long long c){
        if(!c) {
            writeChar('0');
            return;
        }
        if(c < 0) writeChar('-'), c = -c;
        char s[24];
        int n = 0;
        while(c)
            s[n++] = c % 10 + '0', c /= 10;
        while(n--)
            writeChar(s[n]);
    }
    static inline void writeWorld(const char *s) {
        while(*s) writeChar(*s++);
    }
    static inline void flush(){
        if(o_it) {
            fwrite(o_buf, 1, o_it, stdout);
        }
        fflush(stdout);
    }
    
}
//end fasat io


using namespace std;
#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<int, int>
const int MN = 1e5 + 11;
int a[MN];

int32_t main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    int n = io::readInt();
    ll p = io::readLL();
    ll k = io::readInt();
    
    ll ans = 0;
    for(int i = 0; i < n; ++i) {
        a[i] = io::readInt();
        ans += a[i] / k;
        a[i] = k - (a[i] % k);
    }
    sort(a, a + n);
    for(int i = 0; i < n && p >= a[i] && a[i]; ++i) {
        ans++;
        p -= a[i];
    }
    ans += p / k;
    io::writeLL(ans);
    io::flush();
}
