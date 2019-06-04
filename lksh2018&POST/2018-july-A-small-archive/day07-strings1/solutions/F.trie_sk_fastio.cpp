/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define zero(a) memset(a, 0, sizeof(a))

typedef long long ll;

template <const int maxN>
struct AhoCorasic {
  static const int maxV = maxN + 1;
  struct Vertex {
    int next[26], p, dep, ch, suf, data;
  };

  Vertex a[maxV];
  int vn, qst, qen, q[maxV];

  int newV( int P, int D, int K ) {
    assert(vn < maxV);
    Vertex &v = a[vn];
    v.dep = D, v.ch = K, v.p = P, v.data = 0;
    zero(v.next);
    return vn++;
  }

  AhoCorasic() {
    vn = 0, newV(-1, 0, -1);
  }

  void add( const char *s, int d ) {
    int v = 0;
    while (*s) {
      int ch = *s++ - 'a', &x = a[v].next[ch];
      if (!x)
        x = newV(v, a[v].dep + 1, ch);
      v = x;
    }
    a[v].data += d;
  }
  void add( const string &s, int d ) {
    add(s.c_str(), d);
  }

  void build() {
    qst = qen = 0;
    q[qen++] = 0;
    while (qst < qen) {
      int v = q[qst++];
      Vertex &V = a[v];
      V.suf = (V.dep <= 1 ? 0 : a[a[V.p].suf].next[V.ch]);
      forn(i, 26)
        if (V.next[i])
          q[qen++] = V.next[i];
        else 
          V.next[i] = a[V.suf].next[i];
      V.data += a[V.suf].data;
    }
  }
};

const int maxN = 1e5;
const int mLen = 1e5;

vector <int> to[maxN];
vector <char> ch[maxN];
int n, m;
char s[mLen + 1];

AhoCorasic<maxN> trie;
               
ll ans = 0;

void go( int v, int tv ) {
  ans += trie.a[tv].data;
  forn(i, to[v].size())
    go(to[v][i], trie.a[tv].next[ch[v][i] - 'a']);
}

int main() {
  n = readInt();
  forn(i, n) {
    int deg = readInt();
    to[i].resize(deg);
    ch[i].resize(deg);
    forn(j, deg) {
      to[i][j] = readInt() - 1;
      ch[i][j] = readChar();
    }
  }
  m = readInt();
  while (m--) 
    readWord(s), trie.add(s, 1);
  trie.build();

  go(0, 0);
  cout << ans << endl;
}
