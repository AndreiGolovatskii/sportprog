/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

const int maxN = 100;
const int maxV = 2 * maxN;

typedef int mas[maxN];

int N, M, E[maxN][maxN];
mas X, Y, B, P, Q, C;
int w[maxV][maxV];
int p[maxV][maxV];

void go( int i, int j )
{
  int k = p[i][j];
  if (k == i)
    if (i < M)
      E[j - M][i]--;
    else
      E[i - M][j]++;
  else
    go(i, k), go(k, j);
}

int main() {
  #define D (abs(X[i] - P[j]) + abs(Y[i] - Q[j]))
  scanf("%d%d", &N, &M);
  forn(i, N)
    scanf("%d%d%d", &X[i], &Y[i], &B[i]);
  forn(j, M)
    scanf("%d%d%d", &P[j], &Q[j], &C[j]);
  forn(i, N)
    forn(j, M)
      scanf("%d", &E[i][j]), C[j] -= E[i][j];
  
  int V = N + M;
  fill(w, 0x30);
  forn(j, M)
    forn(i, N)
    {
      if (E[i][j] > 0)
        w[j][i + M] = -D;
      w[i + M][j] = D;
    }
  forn(i, V)
    forn(j, V)
      p[i][j] = i;

  forn(k, V)
    forn(i, V)
      forn(j, V)
        if (w[i][j] > w[i][k] + w[k][j])
        {
          w[i][j] = w[i][k] + w[k][j];
          p[i][j] = k;
          if (w[i][j] < 0 && (i == j || (i < M && j < M && C[j] > 0)))
          {
            puts("SUBOPTIMAL");
            go(i, j);
            forn(i, N)
              forn(j, M)
                printf("%d%c", E[i][j], " \n"[j == M - 1]);
            return 0;
          }
        }
  puts("OPTIMAL");
  return 0;
}
