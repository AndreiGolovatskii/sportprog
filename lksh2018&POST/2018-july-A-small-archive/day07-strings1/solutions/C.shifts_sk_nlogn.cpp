/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef unsigned long long ull;

struct StrComparator {
  static const ull P = 239017;
  static vector <ull> deg;

  int n;
  const char *s;
  ull *h;

  StrComparator( int n, const char *s ) : n(n), s(s) {
    h = new ull[n + 1];
    h[0] = 0;
    forn(i, n)
      h[i + 1] = h[i] * P + s[i]; // mod 2^{64}, tests are weak =)
    while ((int)deg.size() <= n)
      deg.push_back(*deg.rbegin() * P);      
  }

  ull substr( int i, int len ) const { return h[i + len] - h[i] * deg[len]; }

  int cmp( int a, int b ) const {
    if (a == b)
      return 0;
    int len = min(n - a, n - b), L = 0, R = len;
    while (L < R) {
      int M = (L + R + 1) / 2;
      if (substr(a, M) == substr(b, M))
        L = M;
      else
        R = M - 1;
    }
    return L < len ? s[a + L] - s[b + L] : b - a;
  }

  inline bool operator() ( int a, int b ) const { return cmp(a, b) < 0; }
};
vector <ull> StrComparator::deg(1, 1);

const int mLen = 1e5;

char s[mLen * 2 + 1];
int k, n, T;

int main() {
  scanf("%s%d", s, &k), k--;
  n = strlen(s);
  memcpy(s + n, s, n);
  StrComparator *x = new StrComparator(2 * n, s);
  for (int i = 1; i <= n; i++)
    if (n % i == 0 && x->substr(0, n - i) == x->substr(i, n - i))
      T = i, i = n + 1;
  if (!(0 <= k && k < T)) {
    puts("IMPOSSIBLE");
    return 0;
  }

  int a[T];
  forn(i, T)
    a[i] = i;
  nth_element(a, a + k, a + T, *x); // O(nlogn)!
  forn(i, n)
    putchar(s[a[k] + i]);
}
