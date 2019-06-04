/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 2e8

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define mp make_pair

const int N = 1e5;

struct Edge  { int to, w; };
struct Query { int a, b, lca, mi, ma; };

struct Event { 
  int w, i, type; 
  bool operator < ( const Event &e ) const { 
    return mp(w, !type) < mp(e.w, !e.type);
  }
};

bool color[N];
int n, qn, p[N];
Query q[N];
vector<Edge> c[N];
vector<int> ind[N];
vector<Event> events;
int T, t_in[N], t_out[N];

template<const int N>
struct Fenwick {
  int sum[N];
  void add( int x, int d ) {
    for (; x < n; x |= x + 1)
      sum[x] += d;
  }
  int get( int x ) {
    int r = 0;
    for (; x >= 0; x &= x + 1, x--)
      r += sum[x];
    return r;
  }
  int get( int l, int r ) {
    return get(r) - get(l - 1);
  }
};

Fenwick<N> f;
 
int get( int v ) {
  return v == p[v] ? v : (p[v] = get(p[v]));
}

void calc_lca( int v, int pr, int prw ) {
  if (v != pr)
    events.pb({prw, v, 0});
  color[v] = 1;
  for (int i : ind[v]) {
    int u = q[i].a + q[i].b - v;
    if (color[u]) 
      q[i].lca = get(u);
  }
  t_in[v] = T++;
  for (auto edge : c[v])
    if (edge.to != pr) 
      calc_lca(edge.to, v, edge.w);
  t_out[v] = T - 1;
  p[v] = pr;
}

void solve_lca() {
  forn(i, qn)
    ind[q[i].a].pb(i), ind[q[i].b].pb(i);
  forn(i, n)
    p[i] = i;
  calc_lca(0, 0, 0);
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
  qn = readInt();
  forn(i, qn)  {
    q[i].a = readInt() - 1;
    q[i].b = readInt() - 1;
    q[i].mi = readInt();
    q[i].ma = readInt();
  }
  solve_lca();
  forn(i, qn) {
    events.pb({q[i].mi, i, 1});
    events.pb({q[i].ma + 1, i, -1});
  }

  int res = 0;
  sort(all(events));
  for (const Event &e : events) 
    if (e.type) {
      f.add(t_in[q[e.i].a], e.type);
      f.add(t_in[q[e.i].b], e.type);
      f.add(t_in[q[e.i].lca], -2 * e.type);
    } else
      res += (f.get(t_in[e.i], t_out[e.i]) > 0); 
  printf("%d\n", res);
}
