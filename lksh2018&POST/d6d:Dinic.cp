
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
#define ll long long

const int MN = 5000 + 7;
struct edge{
    int u, v, c, f, w;
    edge(){};
    edge(int u, int v, int c, int w): u(u), v(v), c(c), f(0), w(w){};
};
int s, t, d[MN], giter[MN];
vector<int> g[MN];
int edgemax = 0;
edge edges[4 * MN];

void addedge(int u, int v, int c, int w) {
    edges[edgemax] = edge(u, v, c, w);
    g[u].push_back(edgemax++);
    
    edges[edgemax] = edge(v, u, 0, -w);
    g[v].push_back(edgemax++);
    
}

int bfs(int k){
    queue<int> q;
    memset(d, -1, MN * sizeof(d[0]));
    d[s] = 0;
    q.push(s);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for(int e : g[u]) {
            edge &ed = edges[e];
            int v = ed.v;
            if(d[v] == -1 && ed.f + k <= ed.c) {
                d[v] = d[u] + 1;
                q.push(v);
            }
        }
    }
    return d[t] != -1;
}

ll dfs(int u, int cm, int k) {
    if(!cm) return 0;
    if(u == t) return cm;
    for(int &i = giter[u]; i < (int)g[u].size(); ++i) {
        edge &ed = edges[g[u][i]];
        if(d[ed.v] < d[u] + 1 || ed.c < ed.f + k) continue;
        int d = dfs(ed.v, min(cm, ed.c - ed.f), k);
        if(d) {
            ed.f += d;
            edge &red = edges[g[u][i] ^ 1];
            red.f -=d;
            return d;
        }
    }
    return 0;
}

ll dinic(){
    ll flow = 0;
    for(int i = 29; i >= 0; --i) {
        while(bfs(1 << i)) {
            memset(giter, 0, sizeof(giter));
            while(ll k = dfs(s, 1e9, 1 << i)){
                flow += k;
            }
        }
    }
    return flow;
}

int main() {
    //    assert(freopen("input.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    int n, m;
    n = readInt();
    m = readInt();
    s = 1;
    t = n;
    for(int i = 0; i < m; ++i) {
        int u, v, c, w;
        u = readInt();
        v = readInt();
        c = readInt();
        //        w = readInt();
        
        addedge(u, v, c, 0);
    }
    writeInt<ll>(dinic());
    writeChar('\n');
    for(int i = 0; i < 2 * m; i += 2) {
        writeInt(edges[i].f);
        writeChar('\n');
    }
}
