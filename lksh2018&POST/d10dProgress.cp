
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

#define pii pair<int, int>
#define x first
#define y second
#define ll long long
#define ld long double

using namespace std;
const int MN = 1e5 + 17, MNF = 1 << 17;
int ftree[MNF + 7];

void add(int x, int v) {
    for(; x < MNF; x |= (x + 1)) {
        ftree[x] += v;
    }
}

int get(){
    int l = 0, r = MNF;
    while(r - l - 1) {
        int rc = ((r - l) >> 1) + l - 1;
        int rv = ftree[rc];
        if(rv < (rc - (rc & (rc + 1)) + 1)) {
            r = rc + 1;
        } else {
            l = rc + 1;
        }
    }
    return l;
}

struct edge {
    int u, v, x;
    edge(){};
    edge(int u, int v, int x): x(x), u(u), v(v) {};
};

int edit = 0;
edge ed[2 * MN];
vector<int> g[MN];

void addedge(int u, int v, int x) {
    g[u].push_back(edit);
    ed[edit++] = edge(u, v, x);
    g[v].push_back(edit);
    ed[edit++] = edge(v, u, x);
}

struct que{
    int id, a, b;
    que(){};
    que(int a, int b, int id): a(a), b(b), id(id){};
};
int queit = 0;
que ques[MN];
const int SEGSIZE = 750;
vector<int> quesAtSegment[MN];
vector<pii> eulerTour;
int vertexPosInEulerTour[MN];

inline void dfs(int u, int p) {
    vertexPosInEulerTour[u] = (int)eulerTour.size();
    for(int e : g[u]) {
        int v = ed[e].v;
        if(v != p) {
            if(ed[e].x < MN)
                eulerTour.push_back({ed[e].x, e / 2});
            dfs(v, u);
            if(ed[e].x < MN)
                eulerTour.push_back({ed[e].x, e / 2});
        }
    }
}

inline void addque(int a, int b, int id) {
    if(a > b) swap(a, b);
    quesAtSegment[a / SEGSIZE].push_back(queit);
    ques[queit++] = que(a, b, id);
}
inline bool cmp(const int &a, const int &b) {
    return ques[a].b < ques[b].b;
}

int ans[MN], CNT[MN];
bitset<MN> cnt;
inline void pr(int a) {
    pii c = eulerTour[a];
    if(cnt[c.y]) {
        cnt[c.y] = 0;
        CNT[c.x]--;
        if(CNT[c.x] == 0) {
            add(c.x, -1);
        }
    } else {
        cnt[c.y] = 1;
        CNT[c.x]++;
        if(CNT[c.x] == 1) {
            add(c.x, 1);
        }
    }
}

int exCNT[SEGSIZE];
bitset<MN> cnt2;
void exceptProcess(int q) {
    int a = ques[q].a;
    int b = ques[q].b;
    int id = ques[q].id;
    
    //    memset(exCNT, 0, sizeof(exCNT));
    for(int i = a; i < b; ++i) {
        pii c = eulerTour[i];
        if(cnt2[c.y]) {
            cnt2[c.y] = 0;
            if(c.x < SEGSIZE)
                exCNT[c.x]--;
        } else {
            cnt2[c.y] = 1;
            if(c.x < SEGSIZE)
                exCNT[c.x]++;
        }
    }
    
    for(int j = 0; j < SEGSIZE; ++j) {
        if(!exCNT[j]) {
            ans[id] = j;
            for(int i = a; i < b; ++i) {
                pii c = eulerTour[i];
                cnt2[c.y] = 0;
                if(c.x < SEGSIZE)
                    exCNT[c.x] = 0;
            }
            return;
        }
    }
}
void processSegment(int seg) {
    if(!quesAtSegment[seg].size()) return;
    sort(quesAtSegment[seg].begin(), quesAtSegment[seg].end(), cmp);
    
    int onsegpos = (seg + 1) * SEGSIZE - 1; // last NOTadded
    int oversegpos = onsegpos + 1; //last NOTadded
    
    cnt = 0;
    memset(ftree, 0, sizeof(ftree));
    memset(CNT, 0, sizeof(CNT));
    
    for(int q : quesAtSegment[seg]) {
        int a = ques[q].a;
        int b = ques[q].b;
        int id = ques[q].id;
        
        if(b <= oversegpos) {
            exceptProcess(q);
            continue;
        }
        while(a <= onsegpos) {
            pr(onsegpos);
            onsegpos--;
        }
        
        while(a - 1 > onsegpos) {
            onsegpos++;
            pr(onsegpos);
        }
        
        while(b > oversegpos) {
            pr(oversegpos);
            oversegpos++;
        }
        ans[id] = get();
        //        for(int i = 0; i < MN; ++i) {
        //            if(!CNT[i]) {
        //                ans[id] = i;
        //                break;
        //            }
        //        }
        //        ans[id] = *st.begin();
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    auto ts = clock();
    
    int n = readInt();
    int q = readInt();
    
    
    eulerTour.reserve(2 * MN);
    for(int i = 0; i < n - 1; ++i) {
        int u, v, x;
        u = readInt();
        v = readInt();
        x = readInt();
        
        addedge(u, v, x);
    }
    dfs(1, -1);
    
    for(int i = 0; i < q; ++i) {
        int a, b;
        a = readInt();
        b = readInt();
        
        addque(vertexPosInEulerTour[a], vertexPosInEulerTour[b], i);
    }
    
    for(int i = 0; i * SEGSIZE < eulerTour.size(); ++i) {
        processSegment(i);
    }
    
    writeDouble(((double) clock() - ts) / CLOCKS_PER_SEC);
    writeChar('\n');
    
    for(int i = 0; i < q; ++i) {
        writeInt(ans[i]);
        writeChar('\n');
    }
    
    return 0;
}
