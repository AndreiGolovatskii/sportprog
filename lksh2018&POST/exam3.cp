
/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define VERSION "0.1.5"

#include <cassert>
#include <cstdio>
#include <algorithm>

/** Fast allocation */

#ifdef FAST_ALLOCATOR_MEMORY
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

/** Fast input-output */

template <class T = int> inline T readInt();
inline double readDouble();
inline int readUInt();
inline int readChar(); // first non-blank character
inline void readWord( char *s );
inline bool readLine( char *s ); // do not save '\n'
inline bool isEof();
inline int getChar();
inline int peekChar();
inline bool seekEof();
inline void skipBlanks();

template <class T> inline void writeInt( T x, char end = 0, int len = -1 );
inline void writeChar( int x );
inline void writeWord( const char *s );
inline void writeDouble( double x, int len = 0 );
inline void flush();

static struct buffer_flusher_t {
    ~buffer_flusher_t() {
        flush();
    }
} buffer_flusher;

/** Read */

static const int buf_size = 4096;

static unsigned char buf[buf_size];
static int buf_len = 0, buf_pos = 0;

inline bool isEof() {
    if (buf_pos == buf_len) {
        buf_pos = 0, buf_len = fread(buf, 1, buf_size, stdin);
        if (buf_pos == buf_len)
            return 1;
    }
    return 0;
}

inline int getChar() {
    return isEof() ? -1 : buf[buf_pos++];
}

inline int peekChar() {
    return isEof() ? -1 : buf[buf_pos];
}

inline bool seekEof() {
    int c;
    while ((c = peekChar()) != -1 && c <= 32)
        buf_pos++;
    return c == -1;
}

inline void skipBlanks() {
    while (!isEof() && buf[buf_pos] <= 32U)
        buf_pos++;
}

inline int readChar() {
    int c = getChar();
    while (c != -1 && c <= 32)
        c = getChar();
    return c;
}

inline int readUInt() {
    int c = readChar(), x = 0;
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return x;
}

template <class T>
inline T readInt() {
    int s = 1, c = readChar();
    T x = 0;
    if (c == '-')
        s = -1, c = getChar();
    else if (c == '+')
        c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    return s == 1 ? x : -x;
}

inline double readDouble() {
    int s = 1, c = readChar();
    double x = 0;
    if (c == '-')
        s = -1, c = getChar();
    while ('0' <= c && c <= '9')
        x = x * 10 + c - '0', c = getChar();
    if (c == '.') {
        c = getChar();
        double coef = 1;
        while ('0' <= c && c <= '9')
            x += (c - '0') * (coef *= 1e-1), c = getChar();
    }
    return s == 1 ? x : -x;
}

inline void readWord( char *s ) {
    int c = readChar();
    while (c > 32)
        *s++ = c, c = getChar();
    *s = 0;
}

inline bool readLine( char *s ) {
    int c = getChar();
    while (c != '\n' && c != -1)
        *s++ = c, c = getChar();
    *s = 0;
    return c != -1;
}

/** Write */

static int write_buf_pos = 0;
static char write_buf[buf_size];

inline void writeChar( int x ) {
    if (write_buf_pos == buf_size)
        fwrite(write_buf, 1, buf_size, stdout), write_buf_pos = 0;
    write_buf[write_buf_pos++] = x;
}

inline void flush() {
    if (write_buf_pos) {
        fwrite(write_buf, 1, write_buf_pos, stdout), write_buf_pos = 0;
        fflush(stdout);
    }
}

template <class T>
inline void writeInt( T x, char end, int output_len ) {
    if (x < 0)
        writeChar('-'), x = -x;
    
    char s[24];
    int n = 0;
    while (x || !n)
        s[n++] = '0' + x % 10, x /= 10;
    while (n < output_len)
        s[n++] = '0';
    while (n--)
        writeChar(s[n]);
    if (end)
        writeChar(end);
}

inline void writeWord( const char *s ) {
    while (*s)
        writeChar(*s++);
}

inline void writeDouble( double x, int output_len ) {
    if (x < 0)
        writeChar('-'), x = -x;
    int t = (int)x;
    writeInt(t), x -= t;
    writeChar('.');
    for (int i = output_len - 1; i > 0; i--) {
        x *= 10;
        t = std::min(9, (int)x);
        writeChar('0' + t), x -= t;
    }
    x *= 10;
    t = std::min(9, (int)(x + 0.5));
    writeChar('0' + t);
}

#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>
#include <map>
#include <set>

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("sse4")

#define x first
#define y second
#define ll long long
#define ld long double
#define pii pair<ll, ll>

using namespace std;
const int MN = 1e5 + 17;

pii dots[MN];
struct line{
    ll a, b, c;
    line(){};
    line(ll a, ll b, ll c): a(a), b(b), c(c) {};
};
line lines[MN];

ll crpr(const pii &a, const pii &b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}
pii operator-(const pii &a, const pii &b) {
    return {a.x - b.x, a.y - b.y};
}

pii find(const vector<pii> &a, const pii &np) {
    int n = a.size();
    int l = 0, r = n - 1;
    while(r - l > 1) {
        int m = (r + l) >> 1;
        pii f = a[m], s = a[m + 1];
        if(crpr(s - f, np) > 0) {
            r = m;
        } else {
            l = m;
        }
    }
    return a[r];
}

int main() {
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    
    
    auto ts = clock();
    
    int n = readInt();
    int m = readInt();
    for(int i = 0; i < n; ++i) {
        int a = readInt();
        int b = readInt();
        int c = readInt();
        lines[i] = line(a, b, c);
    }
    for(int i = 0; i < m; ++i) {
        dots[i].x = readInt();
        dots[i].y = readInt();
    }
    
    
    sort(dots, dots + m);
    vector<pii> up, down;
    pii last = dots[m - 1], first = dots[0];
    up.push_back(dots[0]);
    down.push_back(dots[0]);
    
    for(int i = 0; i < m; ++i) {
        pii a = dots[i];
        if(crpr(last - first, a - first) >= 0) {
            while(up.size() > 1) {
                pii lt = up.back();
                pii plt = up[up.size() - 2];
                if(crpr(a - lt, lt - plt) <= 0) {
                    up.pop_back();
                } else {
                    break;
                }
            }
            up.push_back(a);
        }
        if(crpr(last - first, a - first) <= 0) {
            while(down.size() > 1) {
                pii lt = down.back();
                pii plt = down[down.size() - 2];
                if(crpr(a - lt, lt - plt) >= 0) {
                    down.pop_back();
                } else {
                    break;
                }
            }
            down.push_back(a);
        }
    }
    vector<int> ans;
    reverse(down.begin(), down.end());
    up.push_back(up[0]);
    down.push_back(down[0]);
    
    for(int i = 0; i < n; ++i) {
        line cur = lines[i];
        if(cur.b > 0 || (cur.b == 0 && cur.a < 0)) {
            cur = line(-cur.a, -cur.b, -cur.c);
        }
        pii ln = {-cur.b, cur.a};
        
        pii d1 = find(up, ln);
        ll c1 = d1.y * ln.x - d1.x * ln.y;
        
        ln = {-ln.x, -ln.y};
        pii d2 = find(down, ln);
        
        ln = {-ln.x, -ln.y};
        ll c2 = d2.y * ln.x - d2.x * ln.y;
        if(c1 < c2) {
            swap(c1, c2);
        }
        if(cur.c <= c1 && cur.c >= c2) {
            ans.push_back(i + 1);
        }
    }
    writeInt(ans.size());
    writeChar('\n');
    for(auto i : ans) {
        writeInt(i);
        writeChar(' ');
    }
    
    //    writeDouble(((double) clock() - ts) / CLOCKS_PER_SEC);
    //    writeChar('\n');
    
    return 0;
}
