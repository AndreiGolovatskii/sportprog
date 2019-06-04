#include <cassert>
#include <cstdio>
#include <cstring>

#define forn(i, n) for (int i = 0; i < n; i++)

const int maxn = 303;
const int maxv = maxn * 2;

int n, c[maxv][maxv], w[maxv][maxv];
int p[maxv], d[maxv], u[maxv], la[maxv];

int main() {
  assert(freopen("assignment.in", "r", stdin));
  assert(freopen("assignment.out", "w", stdout));

  int sum = 0;
  scanf("%d", &n);
  memset(c, 0, sizeof(c));
  memset(w, 0, sizeof(w));
  forn(i, n)
    forn(j, n) {
      scanf("%d", &w[i][j + n]);
      w[j + n][i] = -w[i][j + n];
      c[i][j + n] = 1;
    }
    
  int st = n + n, en = st + 1;
  forn(i, n)
    c[st][i] = c[i + n][en] = 1;

  int N = n + n + 2;
  memset(p, 0, sizeof(p));
  forn(k, n) {
    forn(i, N)
      d[i] = 1e9, u[i] = 0;
    d[st] = 0;

    int mi = st, tmp;
    while (mi != -1) {
      u[mi] = 1;
      forn(i, N)
        if (c[mi][i] > 0 && d[i] > (tmp = d[mi] + w[mi][i] + p[mi] - p[i]))
          d[i] = tmp, la[i] = mi;
      mi = -1;
      forn(i, N)
        if (!u[i] && (mi == -1 || d[i] < d[mi]))
          mi = i;
    } 
    forn(i, N)
      p[i] += d[i];

    int i = en;
    while (i != st) {
      int j = la[i];
      c[j][i]--, c[i][j]++, sum += w[j][i];
      i = j;
    }
  }
  printf("%d\n", sum);
  forn(j, n)
    forn(i, n)
      if (c[i][j + n] == 0)
        printf("%d %d\n", i + 1, j + 1);
  return 0;
}
