/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxV = 200 + 2;
const int maxE = maxV * maxV * 6;

int n, m, s, t, cc, u[maxV];
int e, head[maxV], to[maxE], f[maxE], c[maxE], Next[maxE], ans[maxE], p[maxE];
int pn, pa[maxV], sum[maxV];

void addE( int a, int b, int x ) {
  Next[e] = head[a], to[e] = b, f[e] = 0, c[e] = x, head[a] = e++;
  Next[e] = head[b], to[e] = a, f[e] = 0, c[e] = 0, head[b] = e++;
}

#define FOR(v) for (int e = head[v]; e != -1; e = Next[e])

int dfs( int v, int k ) {
  u[v] = cc;
  FOR(v)
    if (c[e] - f[e] >= k && (to[e] == t || (u[to[e]] != cc && dfs(to[e], k)))) {
      pa[pn++] = e;
      return 1;
    }
  return 0;
}

int main() {
  #define NAME "cooling"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  scanf("%d%d", &n, &m);
  s = n, t = s + 1;
  memset(head, -1, sizeof(head));
  forn(i, m) {
    int a, b, L, R;
    scanf("%d%d%d%d", &a, &b, &L, &R), a--, b--;
    sum[b] += L, sum[a] -= L;
    p[i] = e, ans[i] = L;
    addE(a, b, R - L);
  }
  forn(i, n)
    if (sum[i] > 0)
      addE(s, i, sum[i]);
    else
      addE(i, t, -sum[i]);
  fprintf(stderr, "v = %d, e = %d\n", t + 1, e);
  for (int k = 1 << 30; k > 0; k /= 2) {
    cc++, pn = 0;
    while (dfs(s, k)) {
      int mi = 2 * k;
      forn(i, pn)
        mi = min(mi, c[pa[i]] - f[pa[i]]);
      forn(i, pn)
        f[pa[i]] += mi, f[pa[i] ^ 1] -= mi;
      cc++, pn = 0;
    }
  }

  FOR(s)
    if (f[e] != c[e]) {
      puts("NO");
      return 0;
    }
  puts("YES");
  forn(i, m)
    printf("%d\n", ans[i] + f[p[i]]);
  return 0;
}
