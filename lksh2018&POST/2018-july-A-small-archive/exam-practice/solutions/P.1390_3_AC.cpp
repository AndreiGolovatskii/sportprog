/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = (int)5e4;
const int maxA = 1 << 18;
const double inf = 1e9;

char com[9];
int an, n, type[maxN], X1[maxN], Y1[maxN], X2[maxN], Y2[maxN];
double A1[maxN], A2[maxN], D1[maxN], D2[maxN], a[maxA];
vector <int> v[2 * maxA];

double D( double x, double y ) { return sqrt(x * x + y * y); }
double A( double y, double x ) { return atan2(y, x); }

int get( double ang ) {
  return lower_bound(a, a + an, ang) - a;
}

void Set( int l, int r, int i ) {
  for (l += maxA, r += maxA; l <= r; l >>= 1, r >>= 1) {
    if (l % 2 == 1) v[l++].push_back(i);
    if (r % 2 == 0) v[r--].push_back(i);
  }
}

int main() {
  for (n = 0; scanf("%s", com) == 1 && strcmp(com, "end"); n++)
    if (!strcmp(com, "shot"))
    {
      type[n] = 1;
      scanf("%d%d", &X1[n], &Y1[n]);
      D1[n] = D(X1[n], Y1[n]);
      a[an++] = A1[n] = A(Y1[n], X1[n]);
    }
    else
    {
      type[n] = 2;
      scanf("%d%d", &X1[n], &Y1[n]);
      scanf("%d%d", &X2[n], &Y2[n]);
      D1[n] = D(X1[n], Y1[n]);
      D2[n] = D(X2[n], Y2[n]);
      a[an++] = A1[n] = A(Y1[n], X1[n]);
      a[an++] = A2[n] = A(Y2[n], X2[n]);
    }
  sort(a, a + an);
  an = unique(a, a + an) - a;

  forn(i, n)
    if (type[i] == 1)
    {
      int no = get(A1[i]);
      double res = inf, t;
      for (no += maxA; no > 0; no >>= 1)
        forn(j, v[no].size())
        {
          int s = v[no][j];
          if (X2[s] * Y1[s] - X1[s] * Y2[s] == 0)
            t = min(D1[s], D2[s]) / D1[i];
          else
          {
            double dx = X2[s] - X1[s], dy = Y2[s] - Y1[s];
            t = (X1[s] * dy - Y1[s] * dx) / (X1[i] * dy - Y1[i] * dx);
          }
          res = min(res, t);
        }
      if (res == inf)
        puts("Infinite");
      else
        printf("%.20f\n", res);
    }
    else
    {
      int l = get(A1[i]), r = get(A2[i]);
      if (l > r)
        swap(l, r);
      if (fabs(A1[i] - A2[i]) > M_PI)
        Set(r, an - 1, i), Set(0, l, i);
      else
        Set(l, r, i);
    }
}
