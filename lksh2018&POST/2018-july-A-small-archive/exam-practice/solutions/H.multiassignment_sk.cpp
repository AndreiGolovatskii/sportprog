/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

typedef long long ll;

template <const int maxV, const int _maxE>
struct Graph {
  static const ll inf = LONG_MAX;
  static const int maxE = 2 * _maxE;
  ll d[maxV];
  int s, t, vn, e, head[maxV], next[maxE], fr[maxE], to[maxE], f[maxE], c[maxE], w[maxE];
  int pe[maxV];
  int qst, qen, q[maxV], inq[maxV];

  Graph() {
    fill(head, -1);
  }

  int addEdge( int a, int b, int C, int W ) {
    assert(e + 2 <= maxE);
    next[e] = head[a], fr[e] = a, to[e] = b, f[e] = 0, c[e] = C, w[e] = W, head[a] = e++;
    next[e] = head[b], fr[e] = b, to[e] = a, f[e] = 0, c[e] = 0, w[e] = -W, head[b] = e++;
    return e - 2;
  }

  bool fb() {
    assert(vn);
    forn(j, vn)
      d[j] = inf, inq[j] = 0;
    d[s] = 0, inq[s] = 1;
    qst = qen = 0;
    q[qen++] = s;
    while (qst != qen) {
      int y, x = q[qst++]; qst %= maxV;
      inq[x] = 0;
      for (int j = head[x]; j != -1; j = next[j]) {
        if (f[j] < c[j] && d[y = to[j]] > d[x] + w[j]) {
          d[y] = d[x] + w[j], pe[y] = j;
          if (!inq[y]) 
            inq[y] = 1, q[qen++] = y, qen %= maxV;
        }
      }
    }
    return d[t] != inf;
  }

  ll F, cost;

  bool getFlow( int k ) { // |f| <= k, cost = min
    F = 0, cost = 0;
    while (k && fb()) {
      int mi = k;
      for (int v = t; v != s; v = fr[pe[v]]) 
        mi = min(mi, c[pe[v]] - f[pe[v]]);
      for (int v = t; v != s; v = fr[pe[v]]) {
        f[pe[v]] += mi, f[pe[v] ^ 1] -= mi;
        cost += (ll)mi * w[pe[v]];
      }
      F += mi, k -= mi;
    }
    return !k;
  }
};

const int N = 50;

Graph<2 * N + 2, N * N + 2 * N> g;

int n, cc, u[N], pa[N], c[N][N];

int dfs( int v ) {
  u[v] = cc;
  forn(i, n)
    if (c[i][v] && (pa[i] == -1 || (u[pa[i]] != cc && dfs(pa[i])))) {
      pa[i] = v;
      return 1;
    }
  return 0;
}
           
int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int k, x;
  cin >> n >> k;
  int ind[n][n];
  forn(i, n)
    forn(j, n) {
      cin >> x;
      ind[i][j] = g.addEdge(i, j + n, 1, x);
    } 
  g.s = 2 * n, g.t = g.s + 1, g.vn = g.t + 1;
  forn(i, n) {
    g.addEdge(g.s, i, k, 0);
    g.addEdge(i + n, g.t, k, 0);
  }
  assert(g.getFlow(n * k));
  printf("%lld\n", g.cost);
  forn(i, n) 
    forn(j, n)
      c[i][j] = g.f[ind[i][j]];
  forn(_, k) {
    fill(pa, -1);
    forn(i, n)
      cc++, dfs(i);
    forn(i, n) {
      printf("%d%c", pa[i] + 1, " \n"[i == n - 1]);
      c[i][pa[i]] = 0;
    }
  }
}
