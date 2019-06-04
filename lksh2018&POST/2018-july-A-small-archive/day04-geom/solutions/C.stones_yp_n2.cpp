// OK

#include <fstream>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long crd;

const int maxN = 5000;
const crd maxX = 100000000;

struct vec
{
  crd x, y;
  vec() {}
  vec( crd _x, crd _y ): x(_x), y(_y) {}
  vec operator - ( vec b ) { return vec(x - b.x, y - b.y); }
  crd operator ^ ( vec b ) { return x * b.y - y * b.x; }
  crd d2() { return x * x + y * y; }
};

crd _( crd a ) { return (a > 0) ? a : -a; }
crd sq( vec a, vec b, vec c ) { return _((b - a) ^ (c - a)); }

int n, o[maxN], s[maxN * 2], k;
vec p[maxN];

crd sq( int a, int b, int c ) { return sq(p[s[a]], p[s[b]], p[s[c]]); }

bool lessLex( vec a, vec b )
{
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}

bool lessAng( int a, int b )
{
  if (((p[a] - p[o[0]]) ^ (p[b] - p[o[0]])) != 0)
    return ((p[a] - p[o[0]]) ^ (p[b] - p[o[0]])) < 0;
  return (p[a] - p[o[0]]).d2() < (p[b] - p[o[0]]).d2();
}

int main()
{
  // ifstream cin("stones.cin");
  assert(cin >> n);
  assert(4 <= n && n <= maxN);
  for (int i = 0; i < n; i++)
  {
    assert(cin >> p[i].x >> p[i].y);
    assert(-maxX <= p[i].x && p[i].x <= maxX);
    assert(-maxX <= p[i].y && p[i].y <= maxX);
  }

  for (int i = 0; i < n; i++)
  {
    o[i] = i;
    if (lessLex(p[o[i]], p[o[0]]))
      swap(o[i], o[0]);
  }
  sort(o + 1, o + n, lessAng);
  k = 0;
  for (int i = 0; i < n; s[k++] = o[i++])
    while (k >= 2 && ((p[s[k - 1]] - p[s[k - 2]]) ^ (p[o[i]] - p[s[k - 1]])) >= 0)
      k--;
  // cerr << k << endl;

  crd ans = 0;
  for (int i = 0; i < k; i++)
    s[i + k] = s[i];
  if (k == 3)
  {
    for (int i = 0; i < n; i++)
      if (i != s[0] && i != s[1] && i != s[2])
        for (int j = 0; j < k; j++)
          ans = max(ans, sq(p[s[0]], p[s[1]], p[s[2]]) -
                         sq(p[s[j]], p[s[j + 1]], p[i]));
  }
  else
    for (int i = 0; i < (k + 1) / 2; i++)
    {
      int l1 = i, l2 = i, l3 = i, l4 = i;
      while (l3 < i + k)
      {
        l3++;
        while (l2 < l3 && (l2 < l1 || sq(l1, l3, l2) < sq(l1, l3, l2 + 1)))
          l2++;
        while (l4 < l1 + k && (l4 < l3 || sq(l1, l3, l4) < sq(l1, l3, l4 + 1)))
          l4++;
        if (l1 <= l2 && l2 <= l3 && l3 <= l4 && l4 <= l1 + k)
          ans = max(ans, sq(l1, l3, l2) + sq(l1, l3, l4));
      }
    }

  // ofstream out("stones.out");
  cout << ans / 2 << "." << 5 * (ans & 1) << endl;
}
