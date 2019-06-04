/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.04.09
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

typedef long long ll;
typedef pair <int, int> pii;

template <const int maxV, const int _maxE>
struct Graph {
  static const ll inf = LONG_MAX;
  static const int maxE = 2 * _maxE;
  ll d[maxV];
  int s, t, vn, e, head[maxV], next[maxE], fr[maxE], to[maxE], f[maxE], c[maxE], w[maxE], add[maxV];
  int pe[maxV];

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
    static int qst, qen, q[maxV], inq[maxV];
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
          d[y] = d[x] + w[j];
          if (!inq[y]) 
            inq[y] = 1, q[qen++] = y, qen %= maxV;
        }
      }
    }
    return d[t] != inf;
  }

  #define W(j) (w[j] + add[fr[j]] - add[to[j]])
  int cnt, cntv;
  bool dijkstra() {
    static priority_queue<pii, vector<pii>, greater<pii>> q;
    forn(j, vn)
      d[j] = (j == s ? 0 : inf);
    q.push(pii(d[s], s)), cnt++;
    while (q.size()) {
      auto p = q.top(); q.pop();
      int x = p.second;
      if (d[x] != p.first)
        continue;
      cntv++;
      for (int tmp, y, j = head[x]; j != -1; j = next[j]) {
        if (f[j] < c[j] && d[y = to[j]] > (tmp = d[x] + W(j))) {
          d[y] = tmp, pe[y] = j;
          q.push(pii(d[y], y)), cnt++;
        }
      }
    }
    return d[t] != inf;
  }

  void updatePotentials() {
    forn(i, vn)
      if (d[i] < inf / 2)
        add[i] += d[i];
  }

  ll F, cost;

  bool getFlow( int k ) { // |f| <= k, cost = min
    if (!fb())
      return k == 0;
    updatePotentials();
    while (k) {
      if (!dijkstra()) 
        return 0;
      int mi = k;
      for (int v = t; v != s; v = fr[pe[v]]) 
        mi = min(mi, c[pe[v]] - f[pe[v]]);
      for (int v = t; v != s; v = fr[pe[v]]) {
        f[pe[v]] += mi, f[pe[v] ^ 1] -= mi;
        cost += (ll)mi * w[pe[v]];
      }
      F += mi;
      updatePotentials();
    }
    return 1;
  }
  ll getMaxFlow() {
    F = 0, cost = 0;
    getFlow(INT_MAX);
    return cost;
  }
};

const int V = 100;
const int E = 1000;

Graph<V, E> g;

int main() {
  #define NAME "mincost"
  assert(freopen(NAME ".in", "r", stdin));
  assert(freopen(NAME ".out", "w", stdout));

  int n, m;
  scanf("%d%d", &n, &m);
  g.s = 0, g.t = n - 1, g.vn = n;
  while (m--) {
    int a, b, c, w;
    scanf("%d%d%d%d", &a, &b, &c, &w), a--, b--;
    g.addEdge(a, b, c, w);
  }
  cout <<  g.getMaxFlow() << endl;
  return 0;
}
