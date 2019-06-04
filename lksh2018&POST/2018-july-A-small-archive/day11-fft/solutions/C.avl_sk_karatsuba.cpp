#include <cassert>
#include <cstdio>
#include <cstring>

#define forn(i, n) for (int i = 0; i < (n); i++)

const int maxn = 1 << 16;
const int maxh = 16;
const int P = 786433;

typedef long long ll;

ll f[2][maxn + 1], g[maxn];
ll mem[2 * maxn];
int pos = 0;

void Mul( int n, ll *c, ll *a, ll *b ) {
  if (n <= 16) {
    memset(c, 0, sizeof(c[0]) * 2 * n);
    forn(i, n)
      forn(j, n)
        c[i + j] += a[i] * b[j];
    return;
  }

  int k = n / 2;
  Mul(k, c, a, b);
  Mul(k, c + n, a + k, b + k);

  ll *d = mem + pos; pos += k;
  ll *e = mem + pos; pos += k;
  ll *x = mem + pos; pos += n;

  forn(i, k) {
    d[i] = a[i] + a[i + k];
    e[i] = b[i] + b[i + k];
  }
  Mul(k, x, d, e);
  forn(i, n)
    x[i] -= c[i] + c[i + n];
  forn(i, n)
    c[i + k] += x[i];

  pos -= 2 * n;
}

int main() {
  int h, n;
  scanf("%d%d", &n, &h), h++;
  f[0][0] = f[1][1] = 1;
  for (int i = 2; i < h; i++) {
    const int ma = 1 << (i - 1), i0 = i & 1, i1 = i0 ^ 1;
    forn(k, ma)
      g[k] = f[i1][k] + 2 * f[i0][k];
    f[i0][0] = 0;
    Mul(ma, f[i0] + 1, f[i1], g);
    forn(j, 1 << i)
      f[i0][j] %= P;
  }

  ll sum = 0;
  forn(j, n) {
    const int k = n - j - 1, i0 = h & 1, i1 = i0 ^ 1;
    sum += f[i1][j] * (f[i1][k] + 2 * f[i0][k]);
  }
  printf("%d\n", (int)(sum % P));
}
