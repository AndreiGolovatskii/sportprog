/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2015.03.30
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
  bool dijkstra() { // O(ElogV)
    static priority_queue<pii, vector<pii>, greater<pii>> q;
    forn(j, vn)
      d[j] = (j == s ? 0 : inf);
    q.push(pii(d[s], s));
    while (q.size()) {
      auto p = q.top(); q.pop();
      int x = p.second;
      if (d[x] != p.first)
        continue;
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

  ll F, cost; // to store result

  bool getFlow( ll k ) { // |f| <= k, cost = min
    F = 0, cost = 0;
    if (!fb())
      return k == 0;
    updatePotentials();
    while (k && dijkstra()) {
      int mi = k;
      for (int v = t; v != s; v = fr[pe[v]]) 
        mi = min(mi, c[pe[v]] - f[pe[v]]);
      for (int v = t; v != s; v = fr[pe[v]]) {
        f[pe[v]] += mi, f[pe[v] ^ 1] -= mi;
        cost += (ll)mi * w[pe[v]];
      }
      F += mi, k -= mi;
      updatePotentials();
    }
    return !k;
  }
  ll getMaxFlowCost() {
    getFlow(INT_MAX);
    return cost;
  }
};

const int V = 100;
const int E = 1000;

Graph<V, E> g;

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
 