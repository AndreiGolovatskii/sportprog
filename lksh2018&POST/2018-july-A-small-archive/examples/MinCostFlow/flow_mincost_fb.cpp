/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

template <const int maxV, const int _maxE>
struct Graph {
  static const ll inf = LONG_MAX;
  static const int maxE = 2 * _maxE;
  ll d[maxV];
  int s, t, vn, e, head[maxV], next[maxE], fr[maxE], to[maxE], f[maxE], c[maxE], w[maxE];
  int pe[maxV];
  int qst, qen, q[maxV], inq[maxV];

  void init( int s, int t, int vn ) { // source, sink, vertex number
    this->s = s, this->t = t, this->vn = vn;
    e = 0, cc = 1;
    fill(inq, inq + vn, 0);
    fill(head, head + vn, -1);
  }

  int addEdge( int a, int b, int capacity, int weight ) {
    assert(e + 2 <= maxE);
    next[e] = head[a], fr[e] = a, to[e] = b, f[e] = 0, c[e] = capacity, w[e] = weight,  head[a] = e++;
    next[e] = head[b], fr[e] = b, to[e] = a, f[e] = 0, c[e] = 0,        w[e] = -weight, head[b] = e++;
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

  ll F, cost; // to store result

  bool getFlow( ll k ) { // |f| <= k, cost = min
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
  ll getMaxFlowCost() {
    getFlow(INT_MAX);
    return cost;
  }

  /** Path decomposition */
  int cc, *u = inq;
  int pn, *path = q;

  int dfs( int v ) {
    u[v] = cc;
    for (int x, i = head[v]; i != -1; i = next[i])
      if (f[i] > 0 && u[x = to[i]] != cc && (x == t || dfs(x))) {
        f[i]--, f[i ^ 1]++;
        path[pn++] = i;
        return 1;
      }
    return 0;
  }

  int getPath() {
    cc++, pn = 0;
    return dfs(s);
  }
};

/**
  const int maxV = 100;
  const int maxE = 10000;
  Graph<maxV, maxE> g;
  int n = 10;
  g.init(0, n - 1, n); // source, sink, vertex number
  for (...) g.addEdge(a, b, capacity, weight);
  if (g.getFlow(k)) { puts("there is flow of size k"); }
  cout << g.getMaxFlowCost();
*/
