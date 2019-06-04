
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

const int MN = 1e6, ALPH = 31;
struct node{
    int l = 0, r = 0, par = -1, link = -1;
    int ne[ALPH];
    int len() {return r - l;};
    node(){memset(ne, -1, sizeof(ne));};
    node(int l, int r, int par):l(l), r(r), par(par){memset(ne, -1, sizeof(ne));};
};
int treeit = 0;
node tree[MN];
char s[MN];

pii go(pii st, int l, int r) {
    while (l < r) {
        if(st.y == tree[st.x].len()) {
            st = {tree[st.x].ne[s[l]], 0};
            if(st.x == -1) return st;
        } else {
            if(s[tree[st.x].l + st.y] != s[l]){
                return {-1, -1};
            }
            if (r - l < tree[st.x].len() - st.y){
                return {st.x, st.y + r - l};
            }
            l += tree[st.x].len() - st.y;
            st.y = tree[st.x].len();
        }
    }
    return st;
}
int split(pii st) {
    if(st.y == tree[st.x].len()) {
        return st.x;
    }
    if(st.y == 0) {
        return tree[st.x].par;
    }
    node v = tree[st.x];
    int newnode = treeit++;
    tree[newnode] = node(v.l, v.l + st.y, v.par);
    tree[v.par].ne[s[v.l]] = newnode;
    tree[newnode].ne[s[v.l + st.y]] = st.x;
    tree[st.x].par = newnode;
    tree[st.x].l += st.y;
    return newnode;
}
int getlink(int v) {
    if(tree[v].link != -1){
        return tree[v].link;
    }
    if(tree[v].par == -1){
        return 0;
    }
    int to = getlink(tree[v].par);
    return tree[v].link = split(go({to, tree[to].len()}, tree[v].l + (tree[v].par == 0), tree[v].r));
}

pii last = {0, 0};
void addchar(int si){
    for(;;) {
        pii ne = go(last, si, si + 1);
        if(ne.x != -1) {
            last = ne;
            return;
        }
        int m = split(last);
        int newleaf = treeit++;
        tree[newleaf] = node(si, MN, m);
        tree[m].ne[s[si]] = newleaf;
        
        last.x = getlink(m);
        last.y = tree[last.x].len();
        if(!m) break;
    }
}

void prep(){
    treeit = 1;
}

int n = 0;
void add(){
    readWord(s + n);
    for(int i = n; s[i] != '\0'; ++i) {
        if(isupper(s[i])) {
            s[i] = tolower(s[i]);
        }
        s[i] -= 'a' - 1;
        n++;
        addchar(i);
    }
}
char t[100];
void check(){
    bool f = true;
    readWord(t);
    pii st = {0, 0};
    for(int i = 0; t[i] != '\0'; ++i) {
        char c = t[i];
        if(isupper(c)) {
            c = tolower(c);
        }
        if(!c) exit(0);
        if(c == '\n') {
            break;
        } else if(f){
            c -= 'a' - 1;
            for(;;) {
                if(st.y == tree[st.x].len()) {
                    st = {tree[st.x].ne[c], 0};
                    if(st.x == -1) {
                        f = false;
                        break;
                    }
                } else {
                    if(s[tree[st.x].l + st.y] != c){
                        f = false;
                        break;
                    }
                    st.y++;
                    break;
                }
            }
        }
    }
    if(f) {
        writeWord("YES\n");
    } else {
        writeWord("NO\n");
    }
}

void sol(){
    prep();
    for(;;) {
        char t;
        t = readChar();
        if(!t) return;
        if(t == '?') {
            check();
        } else if(t == 'A'){
            add();
        } else {
            break;
        }
    }
}

int MM = 50;
void gen(int n) {
    freopen("input.txt", "w", stdout);
    
    for(int i = 0; i < n; ++i) {
        if(rand() & 1) {
            printf("? ");
            MM = 25;
        } else {
            MM = 250;
            printf("A ");
        }
        int m = rand() % MM + 1;
        for(int i = 0; i < m; ++i) {
            printf("%c", 'a' + rand() % 16);
        }
        printf("\n");
    }
}
bool find(int n) {
    for(int i = 0; i < n; ++i) {
        int k = 0;
        for(; t[k] != 0 && s[i + k] != 0; ++k) {
            if(isupper(t[k])) {
                t[k] = tolower(t[k]);
            }
            if(isupper(s[i + k])) {
                s[i + k] = tolower(s[i + k]);
            }
            if(s[i + k] != t[k]) {
                break;
            }
        }
        if(t[k] == 0) {
            return 1;
        }
    }
    return 0;
}

void oksol() {
    char c;
    int it = 0;
    int n = 0;
    while(true) {
        c = readChar();
        if(c == '?') {
            readWord(t);
            if(find(n)) {
                //                writeWord(t);
                //                if(ans[it++] != 1) {
                //                    cout << it << "\n";
                //                }else {
                //                    writeWord("ok\n");
                //                    cout << "ok ";
                //                }
                writeWord("YES\n");
            } else {
                //                if(ans[it++] != 0) {
                //                    cout << it << "\n";
                //                } else {
                //                    cout << "ok ";
                //                }
                //                writeWord(t);
                writeWord("NO\n");
            }
        } else if(c == 'A') {
            readWord(s + n);
            for(int i = n; s[i] != '\0'; ++i) {
                n++;
            }
        } else {
            break;
        }
    }
}


int main() {
    freopen("nenokku.in", "r", stdin);
    freopen("nenokku.out", "w", stdout);
    //
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    
    //    srand(clock());
    //        gen(10000);
    sol();
    //    oksol();
}
