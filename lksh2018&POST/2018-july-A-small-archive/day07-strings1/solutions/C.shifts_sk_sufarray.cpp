#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

#define maxn 100010

int n, num[maxn];
char s[maxn];
int p[maxn], col[maxn], p2[maxn];

int main() {
  int K;
  scanf("%s%d", s, &K);
  n = strlen(s);

  int ma = max(n, 256);
  forn(i, n)
    col[i] = s[i], p[i] = i;
  for (int k2 = 1; k2 / 2 < n; k2 *= 2) {
    int k = k2 / 2;
    memset(num, 0, sizeof(num));
    forn(i, n)
      num[col[i] + 1]++;
    forn(i, ma)
      num[i + 1] += num[i];
    forn(i, n)
      p2[num[col[(p[i] - k + n) % n]]++] = (p[i] - k + n) % n;

    int cc = 0;
    forn(i, n) {
      if (i && (col[p2[i]] != col[p2[i - 1]] || col[(p2[i] + k) % n] != col[(p2[i - 1] + k) % n]))
        cc++;
      num[p2[i]] = cc;
    }
    forn(i, n)
      p[i] = p2[i], col[i] = num[i];
  }

  int i = 0;
  while (i < n && col[i] != K - 1)
    i++;
  if (i == n)
    puts("IMPOSSIBLE");
  else
    forn(j, n)
      putc(s[(i + j) % n], stdout);
}
