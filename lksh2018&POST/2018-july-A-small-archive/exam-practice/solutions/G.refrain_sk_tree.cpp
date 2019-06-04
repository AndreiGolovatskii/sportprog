/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
	
typedef long long ll;

template <const int maxLen, const int ALPHA_SIZE> 
struct SuffixTree {
  static const int maxV = 1 + maxLen * 2;
  struct edge {
    int st, len, next;
    edge() { }
    edge( int st, int len, int next ) : st(st), len(len), next(next) { }
  };

  int *s, n, vn, root, suf[maxV], dep[maxV], size[maxV];
  edge e[maxV][ALPHA_SIZE];

  int newV( int d, bool end ) {
    assert(vn < maxV);
    dep[vn] = d, size[vn] = end;
    memset(e[vn], 0, sizeof(e[0]));
    return vn++;
  }

  int split( int v, int c, int i ) {
    edge a = e[v][c];
    int u = newV(dep[v] + i, 0);
    e[v][c] = edge(a.st, i, u);
    e[u][s[a.st + i]] = edge(a.st + i, a.len - i, a.next);
    return u;
  }

  void create( int u, int c, int i ) {
    e[u][c] = edge(i, n - i, newV(dep[u] + (n - i), 1));
  }

  SuffixTree( int n, int *s ) : s(s), n(n) {
    vn = 0;
    root = newV(0, 0);

    int v = 0, cur_c = 0, cur_i = 0;
    forn(i, n) {
      if (cur_i && cur_i == e[v][cur_c].len)
        v = e[v][cur_c].next, cur_i = 0;

      int c = s[i], last = -1;
      int *t = s + e[v][cur_c].st;
      while (cur_i && t[cur_i] != c) {
        int w = suf[v], u = split(v, cur_c, cur_i);
        create(u, c, i);
        if (last != -1)
          suf[last] = u;
        last = u;
        if (!v)
          t++, cur_i--;
        edge a;
        while (cur_i && (a = e[w][cur_c = *t]).len <= cur_i)
          cur_i -= a.len, w = a.next, t += a.len;
        v = w;
        if (!cur_i)
          suf[last] = v;
      }
      if (cur_i) {
        cur_i++;
      } else {
        cur_i = 1, cur_c = c;
        while (e[v][c].len < cur_i) {
          create(v, c, i);
          if (v)
            v = suf[v];
          else
            cur_i = 0;
        }
      }
    }
  }

  ll tmp, best;
  int res_v;
  vector<edge> ss;

  void go( int v, int dep, int last = -1 ) {
    dep -= (last == 0);
    forn(i, ALPHA_SIZE)
      if (e[v][i].len) {
        go(e[v][i].next, dep + e[v][i].len, s[e[v][i].st + e[v][i].len - 1]);
        size[v] += size[e[v][i].next];
      }
    if ((tmp = (ll)size[v] * dep) > best)
      best = tmp, res_v = v;
  }
  void out( int v ) {
    if (v == res_v) {
      int sum = 0;
      for (auto x : ss)
        forn(i, x.len)
          sum += (s[x.st + i] != 0);
      writeInt(best), writeChar('\n');
      writeInt(sum), writeChar('\n');
      for (auto x : ss)
        forn(i, x.len)
          if (s[x.st + i] != 0)
            writeInt(s[x.st + i]), writeChar(' ');
    }
    forn(i, ALPHA_SIZE)
      if (e[v][i].len)  {
        ss.push_back(e[v][i]);
        out(e[v][i].next);
        ss.pop_back();
      }
  }
  void solve() {
    best = 0;
    go(0, 0);
    out(0);
  }
};

int main() {
  int n = readInt();
  readInt();
  int a[n + 1];
  forn(i, n)
    a[i] = readInt();
  a[n] = 0;
  SuffixTree<int(1.5e5), 11>(n + 1, a).solve();
}
