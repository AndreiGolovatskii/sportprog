
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
int n, m;
pii first[MN], second[MN];

ll crpr(const pii &a, const pii &b) {
    return (ll)a.x * b.y - (ll)a.y * b.x;
}
ll dtpr(const pii &a, const pii &b) {
    return (ll)a.x * b.x + (ll)a.y * b.y;
}
pii operator-(const pii &a, const pii &b) {
    return {a.x - b.x, a.y - b.y};
}
ld distSQ(const pii &a) {
    return (a.x * a.x + a.y * a.y);
}

int dist(int posF, int posS) {
    ld d1 = sqrt(distSQ(first[posF] - second[posS]));
    int ne = (posS + 1) % m;
    pii v1 = second[ne] - second[posS], v2 = first[posF] - second[posS];
    ld ang1 = abs(atan2(crpr(v1, v2), dtpr(v1, v2)));
    
    v1 = second[posS] - second[ne], v2 = first[posF] - second[ne];
    ld ang2 = abs(atan2(crpr(v1, v2), dtpr(v1, v2)));
    
    if(ang1 < M_PI / 2 && ang2 < M_PI / 2) {
        ld sq = abs(crpr(v1, v2) / sqrt(distSQ(v1)));
        d1 = min(d1, sq);
    }
    return d1;
}
int ch(int l, int r, int posF) {
    for(int i = 0; i < 100; ++i) {
        int ml = l + (r - l) / 3;
        int mr = l + 2 * (r - l) / 3;
        ld a = dist(posF, ml);
        ld b = dist(posF, mr);
        if(a < b) {
            l = ml;
        } else {
            r = mr;
        }
    }
    return l;
}

ld find(int posF) {
    int p = ch(0, m, posF);
    return dist(posF, p);
}

pii cy[MN];
ld sol() {
    int mp = 0;
    ld mv = 0;
    for(int i = 0; i < m; ++i) {
        ld nv = dist(0, i);
        if(nv > mv) {
            mv = nv;
            mp = i;
        }
    }
    for(int i = mp; i < n; ++i) {
        cy[i - mp] = second[i];
    }
    for(int i = 0; i < mp; ++i) {
        cy[i + n - mp - 1] = second[i];
    }
    swap(second, cy);
    ld ans = 1e9;
    for(int i = 0; i < n; ++i) {
        ans = min(ans, find(i));
    }
    return ans;
}


int main() {
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    
    
    auto ts = clock();
    
    n = readInt();
    for(int i = 0; i < n; ++i) {
        first[i].x = readInt();
        first[i].y = readInt();
    }
    
    m = readInt();
    for(int i = 0; i < m; ++i) {
        second[i].x = readInt();
        second[i].y = readInt();
    }
    ld ans = 1e9;
    ans = min(ans, sol());
    
    swap(first, second);
    swap(m, n);
    ans = min(ans, sol());
    
    
    writeDouble(ans, 10);
    //    writeChar('\n');
    
    return 0;
}
