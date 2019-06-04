#define FAST_ALLOCATOR_MEMORY 1e8 // количество байт

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
#include <set>
#include <cstdio>
#include <ctime>
#include <vector>
#include <map>
#include <iostream>
#include <stack>

using namespace std;
#define pii pair<int, int>
#define x first
#define y second
const int MN = 5 * 1e5 + 17;

pii ev[MN];
int dsu[MN], ne[MN], r[MN];
stack<pii> ch, chr;
int gp(int u) {
    return dsu[u] ? gp(dsu[u]) : u;
}

int get(int u, int v) {
    return gp(u) == gp(v);
}

void un(int u, int v) {
    int pu = gp(u), pv = gp(v);
    if(r[pv] < r[pu]) {
        ch.push({pv, dsu[pv]});
        chr.push({pu, r[pu]});
        
        r[pu] = max(r[pu], r[pv] + 1);
        dsu[pv] = pu;
    } else {
        ch.push({pu, dsu[pu]});
        chr.push({pv, r[pv]});
        
        
        r[pv] = max(r[pv], r[pu] + 1);
        dsu[pu] = pv;
    }
}

void rollback(int k) {
    while(k) {
        pii a = ch.top();
        ch.pop();
        dsu[a.x] = a.y;
        
        
        a = chr.top();
        chr.pop();
        r[a.x] = a.y;
        k--;
    }
}

int ans = 0;
int rec(int l, int r) {
    if(l >= r) return 0;
    if(l == r - 1) {
        if(ev[l].x == 0) {
            writeInt(ans);
            writeChar('\n');
        }
        return 0;
    }
    int lastans = ans;
    for(int i = (r + l) / 2; i < r; ++i) {
        if(ev[i].x < 0) {
            if(ne[i] <= l) {
                int u = -ev[i].x;
                int v = -ev[i].y;
                if(!get(u, v)) {
                    ans--;
                    un(u, v);
                }
            }
        }
    }
    rec(l, (r + l) / 2);
    
    rollback(lastans - ans);
    ans = lastans;
    
    for(int i = l; i < (r + l) / 2; ++i) {
        if(ev[i].x > 0 ) {
            if(ne[i] >= r || ne[i] == 0) {
                int u = ev[i].x;
                int v = ev[i].y;
                if(!get(u, v)) {
                    ans--;
                    un(u, v);
                }
            }
        }
    }
    
    rec((r + l) / 2, r);
    
    rollback(lastans - ans);
    ans = lastans;
    return 0;
}

map<pii, int> last;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    //    assert(freopen("out.put.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    auto ts = clock();
    int n, k;
    n = readInt();
    k =readInt();
    ans = n;
    for(int i = 0; i < k; ++i) {
        int u, v;
        char t;
        t = readChar();
        if(t == '?') {
            ev[i] = {0, 0};
            continue;
        }
        
        u = readInt();
        v = readInt();
        if(u > v) {
            swap(u, v);
        }
        r[u] = r[v] = 1;
        if(t == '+') {
            ev[i] = {u, v};
        } else if(t == '-'){
            ev[i] = {-u, -v};
        }
    }
    
    for(int i = 0; i < k; ++i) {
        pii j = ev[i];
        if(j.x < 0) {
            ne[i] = last[{-j.x, -j.y}];
            ne[last[{-j.x, -j.y}]] = i;
        } else if(ev[i].x > 0) {
            last[j] = i;
        }
    }
    last.clear();
    rec(0, k);
    
    //    writeDouble(((double)clock() - ts) / CLOCKS_PER_SEC);
}
