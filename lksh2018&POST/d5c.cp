
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

const int MN = 70;
const int MN2 = MN * MN;
vector<int> g[10 * MN * MN];
struct ed{
    int u, v, f, c;
    ed(){};
    ed(int u, int v, int c): u(u), v(v), c(c), f(0) {};
};
ed edges[10 * MN2];
bool used[10 * MN2];
char gb[MN][MN];
int s, t;
int dfs1(int u, int cm) {
    if(u == t) {
        return cm;
    }
    used[u] = 1;
    for(int i : g[u]) {
        ed &e = edges[i];
        if(!used[e.v] && e.c - e.f > 0) {
            int d = dfs1(e.v, min(cm, e.c - e.f));
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

int v[MN][MN];
int main() {
    //    assert(freopen("input.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    int n, m;
    n = readInt();
    m = readInt();
    int it = 1;
    int vit = 0;
    s = 0;
    t = 9 * MN2;
    for(int i = 0; i < MN; ++i) {
        for(int j = 0; j < MN; ++j) {
            gb[i][j] = '.';
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            gb[i][j] = readChar();
            if(gb[i][j] == '.') continue;
            
            int k;
            if(gb[i][j] == 'H') k = 1;
            else if(gb[i][j] == 'O') k = 2;
            else if(gb[i][j] == 'N') k = 3;
            else if(gb[i][j] == 'C') k = 4;
            else continue;
            
            v[i][j] = it++;
            
            edges[vit] = ed(s, v[i][j], k);
            g[s].push_back(vit++);
            
            edges[vit] = ed(v[i][j], s, 0);
            g[v[i][j]].push_back(vit++);
            
            edges[vit] = ed(t, v[i][j] + MN2, 0);
            g[t].push_back(vit++);
            
            
            edges[vit] = ed(v[i][j] + MN2, t, k);
            g[v[i][j] + MN2].push_back(vit++);
        }
    }
    if(it == 1) {
        writeWord("Invalid");
        return 0;
    }
    
    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            for(int k = -1; k < 2; k += 2) {
                if(gb[i][j + k] && gb[i][j + k] != '.' && gb[i][j] != '.') {
                    edges[vit] = ed(v[i][j] + MN2, v[i][j + k], 0);
                    g[v[i][j] + MN2].push_back(vit++);
                    
                    edges[vit] = ed(v[i][j + k], v[i][j] + MN2, 1);
                    g[v[i][j + k]].push_back(vit++);
                }
                
                if(gb[i + k][j] && gb[i + k][j] != '.' && gb[i][j] != '.') {
                    edges[vit] = ed(v[i][j] + MN2, v[i + k][j], 0);
                    g[v[i][j] + MN2].push_back(vit++);
                    
                    edges[vit] = ed(v[i + k][j], v[i][j] + MN2, 1);
                    g[v[i + k][j]].push_back(vit++);
                }
            }
        }
    }
    
    memset(used, 0, sizeof(used));
    while(dfs1(s, 4)) {
        memset(used, 0, sizeof(used));
    }
    
    for(int e : g[s]) {
        if(edges[e].f < edges[e].c) {
            writeWord("Invalid");
            return 0;
        }
    }
    
    writeWord("Valid");
}

