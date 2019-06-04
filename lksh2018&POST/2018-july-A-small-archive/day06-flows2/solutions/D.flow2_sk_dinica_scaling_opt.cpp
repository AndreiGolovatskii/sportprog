// Dinic's algorithm + scaling + build smaller graph + precheck [d->d+1]
// Not more than 0.09 sec on all tests

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
#include <iostream>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

#define maxv 503
#define maxe 20010

int e = 2, n, m, he[maxv], ne[maxe], to[maxe], c[maxe], c0[maxe];
int cc, u[maxv], d[maxv], che[maxv], cne[maxe];
int qst, qen, q[maxv];

ll res = 0;
int gmi, K, S, T;

int dfs( int v, int cmi )
{
  if (v == T)
  {
    gmi = cmi;
    return 1;
  }
  u[v] = cc;
  while (che[v])
  {
    int x, i = che[v];
    if (c[i] >= K)
      if (u[x = to[i]] != cc && dfs(x, min(cmi, c[i])))
      { 
        c[i] -= gmi, c[i ^ 1] += gmi;
        return 1;       
      }
    che[v] = cne[che[v]];
  }
  return 0;
}

void back_dfs( int v )
{
  if (u[v] & 1)
    return;
  u[v] |= 1;
  for (int e = he[v]; e; e = ne[e])
    if (c[e ^ 1] >= K)
      back_dfs(to[e]);
}

void forward_dfs( int v )
{
  if (u[v] & 2)
    return;
  u[v] |= 2;
  for (int e = he[v]; e; e = ne[e])
    if (c[e] >= K)
      forward_dfs(to[e]);
}

int Phase()
{
  cc++;
  qst = qen = 0;
  memset(u, 0, sizeof(u));
  q[qen++] = S, u[S] = 1, d[S] = 0;
  while (qst < qen)
  {
    int x, v = q[qst++];
    for (int i = he[v]; i; i = ne[i])
      if (c[i] >= K && u[x = to[i]] != 1)
      {
        u[x] = 1, d[x] = d[v] + 1;
        q[qen++] = x;
      }
  }
  if (u[T] != 1)
    return 0;

  memset(u, 0, sizeof(u));
  forward_dfs(S);
  back_dfs(T);

  memset(che, 0, sizeof(che));
  forn(i, e)
  {
    int a = to[i ^ 1], b = to[i];
    if (u[a] == 3 && u[b] == 3 && d[b] == d[a] + 1)
      cne[i] = che[a], che[a] = i;
  }

  assert(S != T);
  for (cc = 4; dfs(S, K * 2); cc++)
    res += gmi;
  return 1;
}

int main()
{
  assert(scanf("%d%d", &n, &m) == 2);
  forn(i, m)
  {
    int a, b, _c;
    assert(scanf("%d%d%d", &a, &b, &_c) == 3);
    c0[i] = _c;
    ne[e] = he[a], to[e] = b, c[e] = _c, he[a] = e++;
    ne[e] = he[b], to[e] = a, c[e] = 0, he[b] = e++;
  }

  memset(u, 0, sizeof(u)), cc = 1;
  S = 1, T = n;
  for (K = (1 << 30); K > 0; K >>= 1)
    while (Phase())
      ;

  cout << res << endl;
  forn(i, m)
    printf("%d\n", c0[i] - c[2 * i + 2]);
}
