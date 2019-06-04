/**
 * Dinic's algorithm + scaling
 * OK, 0.094 sec
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

const int maxv = 500;
const int maxe = 20002;

int K, S, T, e = 2, n, m, he[maxv], ne[maxe], to[maxe], c[maxe], c0[maxe];
int cc, u[maxv], d[maxv], che[maxv];
int qst, qen, q[maxv];

ll res = 0;
int gmi;

int dfs( int v, int cmi ) {
  if (v == T) {
    gmi = cmi;
    return 1;
  }
  u[v] = cc;
  while (che[v]) {
    int x, i = che[v];
    if (d[x = to[i]] == d[v] + 1 && c[i] > 0)
      if (u[x] != cc && dfs(x, min(cmi, c[i]))) { 
        c[i] -= gmi, c[i ^ 1] += gmi;
        return 1;       
      }
    che[v] = ne[che[v]];
  }
  return 0;
}

int Phase() {
  cc++;
  qst = qen = 0;
  q[qen++] = S, u[S] = cc, d[S] = 0;
  while (qst < qen) {
    int x, v = q[qst++];
    for (int i = he[v]; i; i = ne[i])
      if (c[i] >= K && u[x = to[i]] != cc) 
        u[x] = cc, d[x] = d[v] + 1, q[qen++] = x;
  }
  if (u[T] != cc)
    return 0;

  memcpy(che, he, sizeof(he));
  cc++;
  while (dfs(S, 1e9))
    res += gmi, cc++;
  return 1;
}

int main() {
  assert(scanf("%d%d", &n, &m) == 2);
  forn(i, m) {
    int a, b;
    scanf("%d%d%d", &a, &b, &c0[i]), a--, b--;
    ne[e] = he[a], to[e] = b, c[e] = c0[i], he[a] = e++;
    ne[e] = he[b], to[e] = a, c[e] = 0, he[b] = e++;
  }

  S = 0, T = n - 1;
  for (K = (1 << 30); K > 0; K >>= 1)
    while (Phase())
      ;

  cout << res << endl;
  forn(i, m)
    printf("%d\n", c0[i] - c[2 * i + 2]);
}
