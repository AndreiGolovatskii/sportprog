#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < n; i++)

typedef vector <int> vi;

int a[153][153];

// min = sum of a[pa[i],i]
// you may optimize speed by about 15%, just change all vectors to static arrays
const int inf = 1e9;
vi Hungrian( int n ) {
  vi pa(n + 1, -1), str(n + 1, 0), col(n + 1, 0), la(n + 1);
  forn(k, n) {
    vi u(n + 1, 0), d(n + 1, inf);
    pa[n] = k;
    int l = n, x;
    while ((x = pa[l]) != -1) {
      u[l] = 1;
      #define F(v, i) (a[v][i] + str[v] + col[i])
      int mi = inf, tmp, l0 = l;
      forn(j, n)
        if (!u[j]) {
          if ((tmp = F(x, j)) < d[j])
            d[j] = tmp, la[j] = l0;
          if (d[j] < mi)
            mi = d[j], l = j;
        }
      forn(j, n + 1)
        if (u[j])
          col[j] += mi, str[pa[j]] -= mi;
        else
          d[j] -= mi;
    }
    while (l != n)
      pa[l] = pa[la[l]], l = la[l];
  }
  return pa;
}
