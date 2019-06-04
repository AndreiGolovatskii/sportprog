
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
#include <queue>
#include <map>
#include <set>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>

const int MN = 1e6 + 100, ALPH = 29;
int globr = 0;
struct node{
    int pr, pr_val;
    int term;
    int next[ALPH];
    int suffL;
    node(){suffL = -1;memset(next, -1, sizeof(next)); term = -1;}
};
int mg = 1;
node vertex[(int) 1e5];
int newNode(int pr = 0, int pr_val = 0) {
    int r = mg++;
    vertex[r].pr = pr;
    vertex[r].pr_val = pr_val;
    return r;
}

char t[MN];
char s[MN];
void addWord(int root, int id) {
    
    for(int i = 0; s[i] != 0; i++) {
        s[i] -= 'a' - 1;
        if(vertex[root].next[s[i]] == -1) {
            vertex[root].next[s[i]] = newNode(root, s[i]);
        }
        root = vertex[root].next[s[i]];
    }
    vertex[root].term = id;
}
int fout[(int)1e5];
int getFout(int pos) {
    if(pos == 1) {
        return pos;
    }
    if(fout[pos] == 0) {
        if(vertex[pos].term == -1) {
            return fout[pos] = getFout(vertex[pos].suffL);
        } else {
            return fout[pos] = pos;
        }
    }
    return fout[pos];
}

int ans[(int)1e5 + 7];
void mark(int pos){
    while(pos > 1) {
        pos = getFout(pos);
        ans[vertex[pos].term] = 1;
        pos = vertex[pos].suffL;
    }
}


int getLink(int pos) {
    if(vertex[pos].suffL != -1) {
        return vertex[pos].suffL;
    }
    int k = vertex[pos].pr_val;
    int p = getLink(vertex[pos].pr);
    while(vertex[p].next[k] == -1) {
        p = getLink(p);
    }
    return vertex[pos].suffL = vertex[p].next[k];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    
    readWord(t);
    int n;
    
    int root = mg++;
    vertex[root].suffL = 0;
    for(int i = 0; i < ALPH; ++i) {
        vertex[0].next[i] = root;
    }
    
    n = readInt();
    for(int i = 0; i < n; ++i) {
        readWord(s);
        addWord(root, i);
    }
    for(int i = root; i < mg; ++i) {
        getLink(i);
    }
    
    for(int i = 0; t[i] != '\0'; i++) {
        t[i] -= 'a' - 1;
        while(vertex[root].next[t[i]] == -1) {
            root = vertex[root].suffL;
        }
        root = vertex[root].next[t[i]];
        mark(root);
    }
    for(int i = 0; i < n; ++i) {
        if(ans[i]) {
            writeWord("Yes\n");
        } else {
            writeWord("No\n");
        }
    }
}
