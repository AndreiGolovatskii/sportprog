#include <cassert>
#include <cstdio>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int MOD = 786433, PHI = 1 << 18; // 3*2^{18}+1

inline int Mul( int a, int b ) {
  return ((long long)a * b) % MOD; 
}

int Pow( int a, int n ) {
  if (n == 1)
    return a;
  int x = Pow(a, n >> 1);
  x = Mul(x, x);
  return (n & 1) ? Mul(x, a) : x;
}

int Inv( int x ) {
  return Pow(x, MOD - 2);
}

const int maxn = 1 << 16;

int f[2][maxn], res[maxn];
int mpos = 0, mem[maxn * 4];

void FFT( int len, int *res, int *a, int x ) {
  if (len == 1) {
    res[0] = a[0];
    return;
  }

  int i, l = len / 2;
  int *a0 = mem + mpos; mpos += l;
  int *a1 = mem + mpos; mpos += l;
  for (i = 0; i < l; i++)
    a0[i] = a[i + i], a1[i] = a[i + i + 1];

  int *r0 = mem + mpos; mpos += l;
  int *r1 = mem + mpos; mpos += l;
  FFT(l, r0, a0, Mul(x, x));
  FFT(l, r1, a1, Mul(x, x));

  int t = 1, tmp;
  forn(i, l) {
    tmp = Mul(t, r1[i]);
    if ((res[i] = r0[i] + tmp) >= MOD)
      res[i] -= MOD;
    if ((res[i + l] = r0[i] - tmp) < 0)
      res[i + l] += MOD;
    t = Mul(t, x);
  }
  mpos -= 2 * len;
}

int main( void ) {
  int n, h;
  scanf("%d%d", &n, &h), h++;

  int N = 1 << h, x = Pow(5, PHI / N);
  assert(N <= maxn);
  for (int i = 0; i < N; i++)
    f[0][i] = 1;
  f[1][0] = 1;
  for (int i = 1; i < N; i++)
    f[1][i] = Mul(f[1][i - 1], x);

  for (int k = 2; k <= h; k++) 
    for (int t = 1, i = 0; i < N; i++)
      f[k & 1][i] = (long long)f[(k & 1) ^ 1][i] * (f[(k & 1) ^ 1][i] + 2 * f[k & 1][i]) * t % MOD, t = Mul(t, x);

  FFT(N, res, f[h & 1], Inv(x));
  printf("%d\n", Mul(res[n], Inv(N)));
}
