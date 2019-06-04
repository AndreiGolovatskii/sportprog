#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <math.h>
#include <algorithm>
#include <vector>
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

struct node{
    int l, r, v, m;
    int cl, cr;
    node(int l, int r, int v): l(l), r(r), v(v){}
    node(){l = r = v = m = 0; cl = cr = 0;};
};

int glr = 0;
const int MN = 200 * 1000 + 10;
node vx[50 * MN];

int build(int l, int r){
    int root = glr++;
    vx[root] = node(l, r, 0);
    if(l == r) {
        return root;
    } else {
        vx[root].cl = build(l, (l + r) / 2);
        vx[root].cr = build((l + r) / 2 + 1, r);
        vx[root].v = vx[vx[root].cl].v + vx[vx[root].cr].v;
        return root;
    }
}

int ch(int root, int pos, int nv, int nm) {
    if(pos < vx[root].l || pos > vx[root].r) {
        return root;
    }
    if(vx[root].l == vx[root].r){
        int nroot = glr++;
        vx[nroot].m = nm;
        vx[nroot].l = vx[root].l;
        vx[nroot].r = vx[root].r;
        vx[nroot].v = nv;
        
        return nroot;
    }
    int nroot = glr++;
    vx[nroot].l = vx[root].l;
    vx[nroot].r = vx[root].r;
    vx[nroot].cl = ch(vx[root].cl, pos, nv, nm);
    vx[nroot].cr = ch(vx[root].cr, pos, nv, nm);
    vx[nroot].v = vx[vx[nroot].cl].v + vx[vx[nroot].cr].v;
    return nroot;
}

int ver[MN];
int er(int root) {
    if(vx[root].l == vx[root].r) {
        writeInt(vx[root].m);
        writeChar('\n');
        int nr = glr++;
        
        vx[nr].l = vx[root].l;
        vx[nr].r = vx[root].r;
        vx[nr].v = 0;
        return nr;
    }
    if(vx[vx[root].cr].v > 0) {
        int nr = glr++;
        
        vx[nr].l = vx[root].l;
        vx[nr].r = vx[root].r;
        vx[nr].v = 0;
        vx[nr].cr = er(vx[root].cr);
        vx[nr].cl = vx[root].cl;
        vx[nr].v = vx[vx[nr].cl].v + vx[vx[nr].cr].v;
        return nr;
    } else {
        
        int nr = glr++;
        
        vx[nr].l = vx[root].l;
        vx[nr].r = vx[root].r;
        vx[nr].v = 0;
        vx[nr].cl = er(vx[root].cl);
        vx[nr].cr = vx[root].cr;
        vx[nr].v = vx[vx[nr].cl].v + vx[vx[nr].cr].v;
        return nr;
    }
}

int add(int root) {
    if(vx[root].l == vx[root].r) {
        return vx[root].r;
    }
    if(vx[root].v == 0) {
        return vx[root].r;
    }
    if(vx[vx[root].cl].v > 0) {
        return add(vx[root].cl);
    } else {
        return add(vx[root].cr);
    }
}
int ch(int root, int pos, int nm){
    if(vx[root].l > pos || vx[root].r < pos) {
        return root;
    }
    if(vx[root].l == vx[root].r) {
        
        int nr = glr++;
        
        vx[nr].l = vx[root].l;
        vx[nr].r = vx[root].r;
        vx[nr].v = 1;
        vx[nr].m = nm;
        return nr;
    }
    
    int nr = glr++;
    vx[nr].l = vx[root].l;
    vx[nr].r = vx[root].r;
    vx[nr].cl = ch(vx[root].cl, pos, nm);
    vx[nr].cr = ch(vx[root].cr, pos, nm);
    vx[nr].v = vx[vx[nr].cl].v + vx[vx[nr].cr].v;
    return nr;
}

int add(int root, int nm) {
    int pos = add(root);
    pos--;
    return ch(root, pos, nm);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    assert(freopen("pqueue.in", "r", stdin));
    assert(freopen("pqueue.out", "w", stdout));
    
    
    //    assert(freopen("input.txt", "r", stdin));
    //    assert(freopen("output.txt", "w", stdout));
    
    int n;
    n = readUInt();
    ver[0] = build(1, MN);
    for(int i = 0; i < n; ++i) {
        int a;
        a = readInt();
        if(a == 1) {
            int t, m;
            t = readInt();
            m = readInt();
            ver[i + 1] = add(ver[t], m);
        } else {
            int t;
            t = readInt();
            ver[i + 1] = er(ver[t]);
        }
    }
}

#include <queue>
#include <map>
#include <set>

using namespace std;
#define x first
#define y second
#define ll long long
#define dbl double
#define pii pair<int, int>

struct node{
    int l, r, v, m;
    node *cl, *cr;
    node(int l, int r, int v): l(l), r(r), v(v){}
};

node *build(int l, int r){
    node *root = new node(l, r, 0);
    if(l == r) {
        return root;
    } else {
        root->cl = build(l, (l + r) / 2);
        root->cr = build((l + r) / 2 + 1, r);
        root->v = root->cl->v + root->cr->v;
        return root;
    }
}

node *ch(node *root, int pos, int nv, int nm) {
    if(pos < root->l || pos > root->r) {
        return root;
    }
    if(root->l == root->r){
        node *nroot = new node(root->l, root->r, nv);
        nroot->m = nm;
        return nroot;
    }
    node *nroot = new node(root->l, root->r, nv);
    nroot->cl = ch(root->cl, pos, nv, nm);
    nroot->cr = ch(root->cr, pos, nv, nm);
    nroot->v = nroot->cl->v + nroot->cr->v;
    return nroot;
}

const int MN = 30;
node* ver[MN];
int l[MN], u[MN], vu[MN];

int fl(int v) {
    if(ver[v]->v == 0) return l[v] = u[v] =  MN;
    else return l[v];
}
int fu(int v, int &a) {
    a = vu[v];
    return u[v];
}
int get(node *root, int pos) {
    while(root->l != root->r) {
        if(root->cl->r >= pos) {
            root = root->cl;
        } else {
            root = root->cr;
        }
    }
    return root->m;
}

node *add(int v, int nm) {
    int pos = fl(v);
    return ch(ver[v], pos - 1, 1, nm);
}

node *er(int v, int &a) {
    int pos = fu(v, a);
    return ch(ver[v], pos, 0, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    
    //    freopen("pqueue.in", "r", stdin);
    //    freopen("pqueue.out", "w", stdout);
    
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int n;
    cin >> n;
    ver[0] = build(1, MN);
    for(int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        if(a == 1) {
            int t, m;
            cin >> t >> m;
            ver[i + 1] = add(t, m);
            l[i + 1] = l[t] - 1;
            u[i + 1] = u[t];
            vu[i + 1] = m;
        } else {
            int t, k;
            cin >> t;
            ver[i + 1] = er(t, k);
            l[i + 1] = l[t];
            u[i + 1] = u[t] - 1;
            vu[i + 1] = get(ver[i + 1], u[i + 1]);
            
            cout << k << "\n";
        }
    }
}
