/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back

typedef long long ll;

const int maxn = 2010;

int N, K, T[maxn], L[maxn], is[maxn];
ll SL[maxn], ST[maxn];
int pos[maxn][maxn], fp[maxn][maxn];
ll w[maxn][maxn], f[maxn][maxn];

inline ll Cost( int l, int r, int x ) {
  return ((ll)L[x] * (ST[x + 1] - ST[l]) - (SL[x + 1] - SL[l])) +
         ((SL[r + 1] - SL[x]) - (ll)L[x] * (ST[r + 1] - ST[x]));
}

inline void relax( int i, int j, ll F, ll FP ) {
  if (F < f[i][j])
    f[i][j] = F, fp[i][j] = FP;
}

int main() {
  scanf("%d%d%d", &N, &K, &T[0]), L[0] = 0;
  for (int i = 1; i < N; i++)
    scanf("%d%d", &L[i], &T[i]), L[i] += L[i - 1];
  SL[0] = ST[0] = 0;
  forn(i, N) {
    SL[i + 1] = SL[i] + (ll)T[i] * L[i];
    ST[i + 1] = ST[i] + T[i];
  }

  forn(l, N) {
    int x = l;
    for (int r = l; r < N; r++) {
      while (x + 1 <= r && Cost(l, r, x) >= Cost(l, r, x + 1))
        x++;
      pos[l][r] = x, w[l][r] = Cost(l, r, x);
    }
  }

  memset(f, 0x30, sizeof(f));
  ll inf = f[0][0];
  f[0][0] = 0;
  for (int k = 1; k <= N; k++)
    for (int i = min(k - 1, K - 1); i >= 0; i--) {
      int minJ = (f[i][k - 1] == inf ? 0 : fp[i][k - 1]);
      int maxJ = (f[i + 1][k] == inf ? k - 1 : min(k - 1, fp[i + 1][k]));
      for (int j = minJ; j <= maxJ; j++)
        relax(i + 1, k, f[i][j] + w[j][k - 1], j);
    }

  printf("%lld\n", f[K][N]);
  int i = K, j = N;
  while (i) {
    int next = fp[i][j];
    is[pos[next][j - 1]] = 1;
    i--, j = next;
  }
  forn(t, N)
    if (is[t])
      printf("%d ", t + 1);
}
