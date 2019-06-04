#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxv = 1000;
const int maxe = 8000;
const int inf = 1e9;

int n, m, k, e = 0, he[maxv], ne[maxe], w[maxe], fr[maxe], to[maxe], c[maxe], f[maxe], ind[maxe];
int d[maxv], pr[maxv], u[maxv];
int pn, p[maxv];

void AddE( int i, int a, int b, int ww ) {
  ind[e] = i, ne[e] = he[a], fr[e] = a, to[e] = b, c[e] = 1, w[e] = ww, he[a] = e++;
  ind[e] = i, ne[e] = he[b], fr[e] = b, to[e] = a, c[e] = 0, w[e] = -ww, he[b] = e++;
}

int dfs( int v ) {
  u[v] = 1;
  for (int x, i = he[v]; i != -1; i = ne[i])
    if (f[i] > 0 && !u[x = to[i]] && (x == n - 1 || dfs(x))) {
      f[i]--, f[i ^ 1]++;
      p[pn++] = i;
      return 1;
    }
  return 0;
}

int main() {
  assert(freopen("brides.in", "r", stdin));
  assert(freopen("brides.out", "w", stdout));

  memset(he, -1, sizeof(he));
  scanf("%d%d%d", &n, &m, &k);
  forn(i, m) {
    int a, b, ww;
    scanf("%d%d%d", &a, &b, &ww), a--, b--;
    AddE(i, a, b, ww);
    AddE(i, b, a, ww);
  }

  double sum = 0;
  forn(i, k) {
    fill(d, d + n, inf);
    d[0] = 0;
    for (int run = 1; run;) {
      run = 0;
      forn(j, e)
        if (f[j] < c[j] && d[to[j]] > d[fr[j]] + w[j])
          d[to[j]] = d[fr[j]] + w[j], pr[to[j]] = j, run = 1;
    }

    if (d[n - 1] == inf) {
      puts("-1");
      return 0;
    }
    for (int j = n - 1; j != 0; j = fr[pr[j]])
      sum += w[pr[j]], f[pr[j]]++, f[pr[j] ^ 1]--;
  }

  printf("%.20f\n", sum / k);
  forn(i, k) {
    memset(u, 0, sizeof(u));
    pn = 0;
    dfs(0);
    printf("%d", pn);
    for (int i = pn - 1; i >= 0; i--)
      printf(" %d", ind[p[i]] + 1);
    puts("");
  }
  return 0;
}
