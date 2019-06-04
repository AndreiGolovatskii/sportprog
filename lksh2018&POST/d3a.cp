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

using namespace std;
const int MN = 1e6;

struct node{
    int val, cnt;
    int cl, cr, pr;
    node(){cl = cr = pr = NULL;}
    node(int val) : val(val), cnt(1), pr(NULL), cl(NULL), cr(NULL){}
};
int it = 1;
node ve[MN];
int cnt(int root) {
    if(root) {
        return ve[root].cnt;
    } else {
        return 0;
    }
}

void upd(int &root) {
    if(root) {
        ve[root].cnt = cnt(ve[root].cl) + cnt(ve[root].cr) + 1;
        if(ve[root].cl) {
            ve[ve[root].cl].pr = root;
        }
        if(ve[root].cr) {
            ve[ve[root].cr].pr = root;
        }
        ve[root].pr = 0;
    }
}

int numByNode(int r) {
    int ans = cnt(ve[r].cl) + 1;
    while(ve[r].pr) {
        if(ve[ve[r].pr].cr == r) {
            ans += cnt(ve[ve[r].pr].cl) + 1;
        }
        r = ve[r].pr;
    }
    return ans;
}
int getRoot(int r) {
    while(ve[r].pr) {
        r = ve[r].pr;
    }
    return r;
}
int getNode(int root, int pos){
    if(!root) return 0;
    if(cnt(ve[root].cl) + 1 == pos) {
        return root;
    } else if(cnt(ve[root].cl) >= pos) {
        return getNode(ve[root].cl, pos);
    } else {
        return getNode(ve[root].cr, pos - cnt(ve[root].cl) - 1);
    }
}


void split(int &tl, int &tr, int t, int key) {
    if (!t)
        tr = tl = NULL;
    else if(cnt(ve[t].cl) >= key) {
        split(tl, ve[t].cl, ve[t].cl, key);
        tr = t;
        upd(tr);
        upd(tl);
    } else {
        split(ve[t].cr, tr, ve[t].cr, key - cnt(ve[t].cl) - 1);
        tl = t;
        upd(tr);
        upd(tl);
    }
}
int maxR(int r) {
    if(r)
        while(ve[r].cr){
            r = ve[r].cr;
        }
    return r;
}

int maxL(int r) {
    if(r)
        while(ve[r].cl){
            r = ve[r].cl;
        }
    return r;
}

int merge(int t1, int t2) {
    if(!t1)
        return t2;
    if(!t2)
        return t1;
    else if((rand() % (cnt(t1) + cnt(t2))) < cnt(t1)) {
        ve[t1].cr = merge(ve[t1].cr, t2);
        upd(t1);
        return t1;
    } else {
        ve[t2].cl = merge(t1, ve[t2].cl);
        upd(t2);
        return t2;
    }
}


using namespace std;
int vertexPos[MN];
map<pii, int> edgePos;

void updpos(int a, int pos) {
    int n = getNode(a, pos);
    if(n) {
        vertexPos[ve[n].val] = n;
        int n1 = getNode(a, pos + 1);
        if(n1) {
            vertexPos[ve[n1].val] = n1;
            edgePos[{ve[n].val, ve[n1].val}] = n;
        }
    }
}

pair<int, int> splitByVertex(int u) {
    int uNode = vertexPos[u];
    int k = numByNode(uNode);
    int root = getRoot(uNode);
    int l = NULL, r = NULL;
    
    split(l, r, root, k);
    int uCopy = it++;
    ve[uCopy] = node(u);
    r = merge(uCopy, r);
    
    updpos(r, 1);
    
    return {l, r};
}

void add_edge(int u, int v) {
    auto uC = splitByVertex(u);
    auto vC = splitByVertex(v);
    int fake = NULL;
    
    
    split(vC.y, fake, vC.y, cnt(vC.y) - 1);
    
    int a1 = cnt(uC.x), a2 = cnt(uC.y), a3 = cnt(vC.x), a4 = cnt(vC.y);
    uC.x = merge(uC.x, vC.y);
    uC.x = merge(uC.x, vC.x);
    uC.x = merge(uC.x, uC.y);
    updpos(uC.x, a1);
    updpos(uC.x, a1 + a4);
    updpos(uC.x, a1 + a3 + a4);
    updpos(uC.x, a1 + a2 + a3 + a4);
}

void eraseEdge(int u, int v) {
    int uNode = edgePos[{u, v}];
    int vNode = edgePos[{v, u}];
    int root = getRoot(uNode);
    int k1 = numByNode(uNode), k2 = numByNode(vNode);
    if(k2 < k1) {
        swap(uNode, vNode);
        swap(k1, k2);
    }
    int a1, a2, a3, fake;
    split(a1, a2, root, k1);
    root = a2;
    split(a2, a3, root, k2 - k1);
    split(fake, a3, a3, 1);
    int k = cnt(a1);
    int r = merge(a1, a3);
    
    updpos(r, k);
}

int isConnected(int u, int v) {
    return getRoot(vertexPos[u]) == getRoot(vertexPos[v]);
}

void init(int n) {
    for(int i = 1; i <= n; ++i) {
        vertexPos[i] = it++;
        ve[vertexPos[i]] = node(i);
    }
}
void check(int n) {
    for(int i = 1; i <= n; ++i) {
        for(int j = i + 1; j <= n; ++j) {
            writeInt(isConnected(i, j));
        }
    }
    writeChar('\n');
}


char s[20];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    assert(freopen("eulertour.in", "r", stdin));
    assert(freopen("eulertour.out", "w", stdout));
    //    assert(freopen("input.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    
    
    int n, m;
    n = readInt();
    m = readInt();
    init(n);
    
    for(int i = 0; i < m; ++i) {
        readWord(s);
        int u, v;
        u = readInt();
        v = readInt();
        if(s[0] == 'l') {
            add_edge(u, v);
        } else if(s[0] == 'c') {
            eraseEdge(u, v);
        } else {
            writeInt(isConnected(u, v));
        }
    }
}
