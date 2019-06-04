
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
#include <complex>


#pragma GCC optimize("03,unroll-loops")
#pragma GCC target("sse4")

#define pii pair<ll, ll>
#define x first
#define y second
#define ll long long
#define ld long double



using namespace std;
const int MK = 17, MN = (1 << MK);
const int BASE = (int)1e5, BASEL = 5;

typedef complex<ld> comp;
int rev[MN + 7];
comp w[MN + 7];

void prep() {
    for(int i = 0; i < MN; ++i) {
        rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (MK - 1));
    }
    for(int k = 1; k < MN; k <<= 1) {
        ld ang = M_PI / k;
        comp t = comp(cos(ang), sin(ang));
        w[k] = comp(1, 0);
        for(int i = 1; i < k; ++i) {
            if(i & 1) {
                w[k + i] = w[(k + i) >> 1] * t;
            } else {
                w[k + i] = w[(k + i) >> 1];
            }
        }
    }
}

vector<comp> fft(const vector<comp> &a) {
    vector<comp> f(MN);
    for(int i = 0; i < MN; ++i) {
        f[rev[i]] = a[i];
    }
    for(int k = 1; k < MN; k <<= 1) {
        for(int i = 0; i < MN; i += k + k) {
            for(int j = 0; j < k; ++j) {
                assert(i + j + k < MN);
                comp t = w[k + j] * f[i + j + k];
                f[i + j + k] = f[i + j] - t;
                f[i + j] = f[i + j] + t;
            }
        }
    }
    
    return f;
}

vector<ll> multiply(const vector<comp> &a, const vector<comp> &b) {
    vector<comp> fa = fft(a), fb = fft(b);
    for(int i = 0; i < MN; ++i) {
        fa[i] *= fb[i];
    }
    fa = fft(fa);
    
    reverse(fa.begin() + 1 , fa.end());
    vector<ll> ans(fa.size());
    for(int i = 0; i < fa.size(); ++i) {
        fa[i] /= MN;
        ans[i] = (ll)(fa[i].real() + 0.5);
    }
    ll c = 0;
    for (int i = 0; i < ans.size(); ++i) {
        ans[i] += c;
        c = ans[i] / BASE;
        ans[i] %= BASE;
    }
    return ans;
}


char sc[(1 << 18) + 7];
void getlnum(vector<ll> &a){
    readWord(sc);
    string s = (string)sc;
    reverse(s.begin(), s.end());
    for(int i = 0; i < s.size(); i += BASEL) {
        string t = s.substr(i, BASEL);
        reverse(t.begin(), t.end());
        int n = stoi(t);
        a.push_back(n);
    }
    a.resize(MN);
}
void printlnum(const vector<ll> &a) {
    int k = a.size() - 1;
    while(a[k] == 0 && k >= 0) {
        k--;
    }
    if(k < 0) {
        writeInt(0);
        return;
    }
    for(int i = k; i >= 0; --i) {
        string s = to_string(a[i]);
        if(i != k) {
            reverse(s.begin(), s.end());
            s.resize(BASEL, '0');
            reverse(s.begin(), s.end());
        }
        writeWord(s.c_str());
    }
}
vector<comp> toComp(const vector<ll> &a) {
    vector<comp> r(a.size());
    for(int i = 0; i < a.size(); ++i) {
        r[i] = comp(a[i], 0);
    }
    return r;
}

int main() {
    //    auto ts = clock();
    
    //    freopen("input.txt", "r", stdin);
    //    freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    vector<ll> a, b;
    getlnum(a);
    getlnum(b);
    prep();
    
    printlnum(multiply(toComp(a), toComp(b)));
    
    //    writeWord("\n");
    //    writeDouble(((ld)clock() - ts) / CLOCKS_PER_SEC);
}
