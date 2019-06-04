/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5;
const int E = 2 * N;

char is[E];
int e, head[N], Next[E], to[E];
int cc, u[N], deg[N];

int dfs( int v, int need ) {
  if (deg[v] <= need) {
    deg[v]++;
    return 1;
  }
  u[v] = cc;
  for (int e = head[v]; e != -1; e = Next[e])
    if (is[e] && u[to[e]] != cc && dfs(to[e], need)) {
      is[e] = 0, is[e ^ 1] = 1;
      return 1;
    }
  return 0;
}

int solve( int n, int m, int *a, int *b, int *orient ) {
  forn(i, m)
    a[i]--, b[i]--;

  memset(head, -1, sizeof(head));
  memset(deg, 0, sizeof(deg));
  e = 0;
  forn(i, m) {
    Next[e] = head[a[i]], is[e] = 0, to[e] = b[i], head[a[i]] = e++;
    Next[e] = head[b[i]], is[e] = 0, to[e] = a[i], head[b[i]] = e++;
    if (rand() & 1)
      deg[a[i]]++, is[e - 2] = 1;
    else
      deg[b[i]]++, is[e - 1] = 1;
  }

  for (int cnt = 0;; cnt++) {
    int ma = 0;
    forn(i, n)
      if (deg[i] > deg[ma])
        ma = i;
    cc++;
    if (!dfs(ma, deg[ma] - 2)) {
      fprintf(stderr, "%d steps\n", cnt);
      forn(i, m)
        orient[i] = is[2 * i] ? 0 : 1;
      return deg[ma];
    }
    deg[ma]--;
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int n, m;
  cin >> n >> m;
  int a[m], b[m], orient[m];
  for (int i = 0; i < m; i++)
    cin >> a[i] >> b[i];

  int res = solve(n, m, a, b, orient);
  cout << res << "\n";
  for (int i = 0; i < m; i++)
    cout << orient[i] << " ";
}
