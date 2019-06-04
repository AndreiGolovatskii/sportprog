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
        }
    }
    static char readChar(){
        int r = getChar();
        while(r != -1 && r <= 32) {
            r = getChar();
        }
        return r;
    }
    static long long readLL(){
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

int32_t main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    
    int n = io::readLL();
    int c, p = 0;
    for(int i = 0; i < n; ++i) {
        if(!i) c = io::readChar();
        else if(io::readChar() != c) p = i;
    }
    if(p) {
        io::writeStr("Yes\n1 ");
        io::writeLL(p + 1);
        io::writeStr(" 1\n");
    } else {
        io::writeStr("No\n");
    }
    io::flush();
}
