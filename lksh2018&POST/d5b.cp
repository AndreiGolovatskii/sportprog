
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

#include <iostream>
#include <string>
#include <math.h>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second

const int MN = 100;
vector<int> g[MN];
struct ed{
    int u, v, f, c;
    ed(){};
    ed(int u, int v, int c): u(u), v(v), c(c), f(0) {};
};
ed edges[2 * MN * MN];
bool used[MN], gb[MN][MN];
int s, t;
int dfs1(int u, int cm, int k) {
    if(u == t) {
        return cm;
    }
    used[u] = 1;
    for(int i : g[u]) {
        ed &e = edges[i];
        if(!used[e.v] && e.c - e.f >= k) {
            int d = dfs1(e.v, min(cm, e.c - e.f), k);
            if(d > 0) {
                e.f += d;
                ed &re = edges[i ^ 1];
                re.f -= d;
                return d;
            }
        }
    }
    return 0;
}

bool col[MN];
void dfs2(int u) {
    col[u] = 1;
    if(u == t) {
        return;
    }
    used[u] = 1;
    for(int i : g[u]) {
        ed &e = edges[i];
        if(used[e.v]) continue;
        if(e.c - e.f > 0) {
            dfs2(e.v);
        }
    }
}

int calc() {
    int res = 0;
    for(int i = 1; i < MN; ++i) {
        for(int j = i + 1; j < MN; ++j) {
            if(gb[i][j] && col[i] != col[j]) {
                res++;
            }
        }
    }
    return res;
}


bool res[MN];
int rans = 1e9;
void find(int u, int v){
    s = u;
    t = v;
    for(int i = 25; i >= 0; --i) {
        memset(used, 0, MN);
        while(dfs1(s, 1e9, 1 << i)) {
            memset(used, 0, MN);
        }
    }
    
    memset(col, 0, MN);
    memset(used, 0, MN);
    dfs2(s);
    
    int k = calc();
    if(k < rans) {
        rans = k;
        for(int i = 0; i < MN; ++i) {
            res[i] = col[i];
        }
    }
}



int main() {
    //    assert(freopen("input.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    int n;
    n = readInt();
    
    int it = 0;
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            int k;
            k = readChar();
            if(k == '1' && j > i) {
                edges[it] = ed(i, j, 1);
                g[i].push_back(it);
                it++;
                edges[it] = ed(j, i, 1);
                g[j].push_back(it);
                it++;
                gb[i][j] = 1;
            }
            
        }
    }
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            if(i == j) continue;
            find(i, j);
        }
    }
    
    for(int i = 1; i <= n; ++i) {
        if(res[i]) {
            writeInt(i);
            writeChar(' ');
        }
    }
    writeChar('\n');
    
    for(int i = 1; i <= n; ++i) {
        if(!res[i]) {
            writeInt(i);
            writeChar(' ');
        }
    }
}
