/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 2e8

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back

const int N = 1e5;
const int C = 1e6 + 1;

struct Edge  { int to, w; };
struct Query { int a, b, w, lca, ans; };
struct SumQuery { int i, coef; };

int n, qn, color[N], p[N];
vector<Edge> c[N];
vector<int> ind[N];
vector<SumQuery> sq[N];
Query q[N];

struct Fenwick {
  int sum[C];

  void add( int x, int d ) {
    for (; x < C; x |= x + 1)
      sum[x] += d;
  }

  int get( int x ) {
    int r = 0;
    for (; x >= 0; x &= x + 1, x--)
      r += sum[x];
    return r;
  }
} f; 

void dfs( int v, int pr ) {
  for (auto query : sq[v])
    q[query.i].ans += query.coef * f.get(q[query.i].w);
  for (Edge &e : c[v])
    if (e.to != pr) {
      f.add(e.w, 1);
      dfs(e.to, v);
      f.add(e.w, -1);
    }
}

int get( int v ) {
  return v == p[v] ? v : (p[v] = get(p[v]));
}

void calc_lca( int v, int pr ) {
  color[v] = 1;
  for (int i : ind[v]) {
    int u = q[i].a + q[i].b - v;
    if (color[u]) 
      q[i].lca = get(u);
  }
  for (Edge &e : c[v])
    if (e.to != pr)
      calc_lca(e.to, v);
  p[v] = pr;
}

int main() {
  n = readInt();
  forn(i, n - 1) {
    int a = readInt() - 1;
    int b = readInt() - 1;
    int x = readInt();
    c[a].pb({b, x});
    c[b].pb({a, x});
  }
  int qn = readInt();
  forn(i, qn) {
    q[i].a = readInt() - 1;
    q[i].b = readInt() - 1;
    q[i].w = readInt();
    ind[q[i].a].pb(i);
    ind[q[i].b].pb(i);
  }
  forn(i, n)
    p[i] = i;
  calc_lca(0, 0);
  forn(i, qn) {
    sq[q[i].a].pb({i, 1});
    sq[q[i].b].pb({i, 1});
    sq[q[i].lca].pb({i, -2});
  }
  dfs(0, 0);
  forn(i, qn)
    writeInt(q[i].ans, '\n');
}
