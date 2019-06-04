/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define IS(a, i) (((a) >> (i)) & 1)

typedef unsigned int uint;

uint cur = 0, a, b;
inline uint gen16() {
  cur = cur * a + b;
  return cur >> 16;
}

const int N = 16;
const int N2 = 1 << N;

int n, n2, t;
char bn[N2];
uint f[N2], g[N2], h[N2], fs[N2], gs[N2], hs[N2];
uint tmp[N + 1][N2];

void calc_sum( uint *f ) {
  forn(bit, n)
    fornd(i, n2)
      if (IS(i, bit))
        f[i] += f[i ^ (1 << bit)];
}

int main() {
  assert(scanf("%d%d", &n, &t) == 2 && n <= N);
  scanf("%d%d", &a, &b);

  n2 = 1 << n;
  forn(i, n2)
    bn[i] = bn[i >> 1] + (i & 1);

  while (t--) {
    forn(i, n2) f[i] = gen16();
    forn(i, n2) g[i] = gen16();
    calc_sum(f);
    calc_sum(g);
    forn(i, n2) h[i] = f[i] * g[i] * ((bn[i] & 1) ? -1 : 1);
    calc_sum(h);

    uint sum = 0;
    forn(i, n2) sum += ((bn[i] & 1) ? -1 : 1) * h[i] * (i+1);
    cout << sum << endl;
  }
}
