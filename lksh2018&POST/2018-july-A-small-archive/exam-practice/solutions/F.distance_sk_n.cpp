// OK

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long double dbl;

const dbl eps = 1e-9;
const dbl inf = 1e100;

struct pnt
{
  dbl x, y;

  pnt() {}
  pnt( dbl _x, dbl _y ) { x = _x, y = _y; } 

  pnt operator + ( pnt a ) { return pnt(x + a.x, y + a.y); }
  pnt operator - ( pnt a ) { return pnt(x - a.x, y - a.y); }
  pnt operator * ( dbl k ) { return pnt(x * k, y * k); }
  pnt operator / ( dbl k ) { return pnt(x / k, y / k); }

  dbl operator ^ ( pnt p ) { return x * p.x + y * p.y; }

  pnt ort() { return pnt(-y, x); }
  dbl d2() { return x * x + y * y; }
  dbl d() { return sqrt(d2()); }

  void norm()
  {
    if (fabs(x) > eps || fabs(y) > eps)
      *this = *this / d();
  }

  string s()
  {
    char t[100];
    sprintf(t, "(%.20f,%.20f)", (double)x, (double)y);
    return string(t);
  }
};

#define maxn 100010

struct poly
{
  int n;
  pnt a[maxn];
};

dbl Read()
{
  double x;
  scanf("%lf", &x);
  return x;
}

void ReadP( poly &p )
{
  scanf("%d", &p.n);
  forn(i, p.n)
    p.a[i].x = Read(), p.a[i].y = Read();
  p.a[p.n] = p.a[0];
}

poly A, B;

pnt p1, p2, rp1, rp2;
dbl d2, rd2 = inf;

void Relax( pnt a, pnt b )
{
  dbl t;
  if ((t = (a - b).d2()) < d2)
    d2 = t, p1 = a, p2 = b;
}

int IsIn( pnt p, pnt a, pnt b )
{
  return
    min(a.x, b.x) - eps < p.x && p.x < max(a.x, b.x) + eps &&
    min(a.y, b.y) - eps < p.y && p.y < max(a.y, b.y) + eps;
}

dbl Calc( int i, int j )
{
  d2 = inf;

  pnt a = A.a[i], b = A.a[i + 1], c = B.a[j], d = B.a[j + 1];
  forn(t, 2)
  {
    forn(s, 2)
    {
      pnt V = (d - c).ort();
      V.norm();
      dbl dist = V ^ (a - c);
      pnt q = a - V * dist;
      if (IsIn(q, c, d))
        Relax(a, q);
      Relax(a, d);
      swap(a, b);
    }
    swap(a, d), swap(b, c);
  }

  if (d2 < rd2)
    rd2 = d2, rp1 = p1, rp2 = p2;
  return d2;
}

int main( int argc, char *argv[] )
{
  ReadP(A), ReadP(B);

  int i = 0, mj = 0;
  dbl f = Calc(i, mj), tmp;
  forn(j, B.n)
    if (f > (tmp = Calc(i, j)))
      mj = j, f = tmp;

  forn(i, A.n)
  {
    int j1;
    f = Calc(i, mj);
    for (int k = -1; k <= 1; k += 2)
      while (f > (tmp = Calc(i, j1 = (mj + B.n + k) % B.n)) + eps)
      {
        mj = j1, f = tmp;
        if (rd2 > f)
          rd2 = f, rp1 = p1, rp2 = p2;
      }
  }

  printf("%s %s %s\n", rp1.s().c_str(), rp2.s().c_str(), (rp1 - rp2).s().c_str());
  printf("%.20f\n", (double)(rp1 - rp2).d());
}
