/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define V(i, j) (2 * ((i) * n + (j)))

const int N = 50;
const int inf = 1e9;
const int VN = N * N * 2;
const int EN = N * N * 5 * 2;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int S, T, n, m, a[N][N];
int e = 2, Next[EN], head[VN], to[EN], f[EN], c[EN];
int cc = 1, u[VN];

void add_edge( int i, int j, int x ) {
  assert(e + 2 <= EN);
  Next[e] = head[i], to[e] = j, c[e] = x, head[i] = e++;
  Next[e] = head[j], to[e] = i, c[e] = 0, head[j] = e++;
}

void add( int x1, int y1, int x2, int y2 ) {
  if (0 <= x2 && x2 < m && 0 <= y2 && y2 < n && a[x2][y2] != 1)
    add_edge(V(x1, y1) + 1, V(x2, y2), inf);
}

inline int dfs( int v, int mi ) {
  if (v == T)
    return mi;
  u[v] = cc;
  for (int gmi, e = head[v]; e; e = Next[e])
    if (f[e] < c[e] && u[to[e]] != cc && (gmi = dfs(to[e], min(mi, c[e] - f[e]))) != 0) {
      f[e] += gmi, f[e ^ 1] -= gmi;
      return gmi;
    }
  return 0;
}

int main() {
  int k, l, x, y, sx, sy, ex, ey;
  assert(scanf("%d%d%d%d", &m, &n, &k, &l) == 4 && m <= N && n <= N);
  while (k--)
    scanf("%d%d", &x, &y), a[--x][--y] = 1; // mountain
  while (l--)
    scanf("%d%d", &x, &y), a[--x][--y] = 2; // may build the wall
  scanf("%d%d", &sx, &sy), sx--, sy--;
  scanf("%d%d", &ex, &ey), ex--, ey--;
  forn(i, m)
    forn(j, n)
      if (a[i][j] != 1) {
        forn(k, 4)
          add(i, j, i + dx[k], j + dy[k]);
        add_edge(V(i, j), V(i, j) + 1, a[i][j] == 2 ? 1 : inf);
      }
  S = V(sx, sy) + 1;
  T = V(ex, ey);

  int flow = 0, df;
  for (; (df = dfs(S, inf)) != 0; flow += df, cc++)
    if (df >= inf / 2) {
      puts("-1");
      return 0;
    }

  printf("%d\n", flow);
  forn(v, VN)
    if (u[v] == cc)
      for (int e = head[v]; e; e = Next[e])
        if (f[e] && u[to[e]] != cc)
          printf("%d %d\n", (v / 2) / n + 1, (v / 2) % n + 1);
}
