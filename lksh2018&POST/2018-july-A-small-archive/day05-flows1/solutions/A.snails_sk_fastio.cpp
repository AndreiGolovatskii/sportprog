/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <cstdio>
#include <cassert>
#include "optimization.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5, M = 1e5, E = 2 * M + 2;

int e = 2, head[N], Next[E], f[E], c[E], to[E];
int n, m, s, t, cc, u[N];

void add( int a, int b ) {
  Next[e] = head[a], to[e] = b, f[e] = 0, c[e] = 1, head[a] = e++;
  Next[e] = head[b], to[e] = a, f[e] = 0, c[e] = 0, head[b] = e++;
}

int dfs( int v ) {
  u[v] = cc;
  for (int e = head[v]; e; e = Next[e]) {
    int x = to[e];
    if (f[e] < c[e] && u[x] != cc && (x == t || dfs(x))) {
      f[e]++, f[e ^ 1]--;
      return 1;
    }
  }
  return 0;
}

void go( int v ) {
  writeInt(v + 1), writeChar(' ');
  for (int e = head[v]; e; e = Next[e]) 
    if (f[e] > 0) {
      f[e]--, go(to[e]);
      break;
    }
}

int main() {
  n = readInt();
  m = readInt();
  s = readInt() - 1;
  t = readInt() - 1;
  assert(n <= N && m <= M);
  while (m--) {
    int a = readInt() - 1;
    int b = readInt() - 1;
    add(a, b);
  }
  forn(_, 2) {
    cc++;
    if (!dfs(s)) {
      writeWord("NO\n");
      return 0;
    }
  }
  writeWord("YES\n");
  forn(_, 2)
    go(s);
}
