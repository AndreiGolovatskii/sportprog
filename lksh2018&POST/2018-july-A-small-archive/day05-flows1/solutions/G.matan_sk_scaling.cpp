/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.03.27
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

template <const int maxV, const int maxE>
struct Graph {
  int s, t, e, head[maxV], next[maxE], to[maxE], f[maxE], c[maxE];
  int cc, u[maxV];

  Graph() {
    e = 0, cc = 1;
    fill(u, 0), fill(head, -1);
  }

  int add( int a, int b, int x1, int x2 = 0 ) {
    assert(e + 2 <= maxE);
    next[e] = head[a], to[e] = b, f[e] = 0, c[e] = x1, head[a] = e++;
    next[e] = head[b], to[e] = a, f[e] = 0, c[e] = x2, head[b] = e++;
    return e - 2;
  }

  int gval;
  int dfs( int v, int k, int val ) {
    if (v == t) {
      gval = val;
      return 1;
    }
    u[v] = cc;
    for (int e = head[v]; e != -1; e = next[e])
      if (f[e] + k <= c[e] && u[to[e]] != cc && dfs(to[e], k, min(val, c[e] - f[e]))) {
        assert(k <= gval && f[e] + gval <= c[e]);
        f[e] += gval, f[e ^ 1] -= gval;
        return 1;
      }
    return 0;
  }

  int getFlow() {
    int sum = 0;
    for (int k = 1 << 30; k > 0; k /= 2) 
      for (cc++; dfs(s, k, 2 * k); cc++)
        sum += gval;
    return sum;
  }
};

const int N = 200;
const int M = 1800;

Graph<N + 2, 2 * (M + 2 * N)> g;

int main() {
  #define NAME "matan"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, sum = 0;
  cin >> n;
  g.s = n, g.t = g.s + 1;
  forn(i, n) {
    int w;
    cin >> w;
    if (w >= 0)
      g.add(g.s, i, w), sum += w;
    else
      g.add(i, g.t, -w);
  }
  forn(i, n) {
    int k = 0, x;
    cin >> k;
    while (k--)
      cin >> x, g.add(i, x - 1, INT_MAX);
  }
  cout << sum - g.getFlow() << endl;
  return 0;
}
