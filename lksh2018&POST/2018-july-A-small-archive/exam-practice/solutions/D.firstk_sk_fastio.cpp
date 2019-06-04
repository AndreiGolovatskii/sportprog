/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#define FAST_ALLOCATOR_MEMORY 2e8 // количество байт
#include "optimization.h"

#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <set>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define mp make_pair

const int maxN = (int)1e5;
const int M = 100;
const int maxK = 10;

int T, q, n, a[maxN], b[maxN], r[maxN], l[maxN], k[maxN];
vector<int> g[maxN / M + 1];
int ans[maxN][maxK];

inline bool rless( int i, int j ) { return mp(r[i], l[i]) < mp(r[j], l[j]); }

int main() {
  n = readInt();
  forn(i, n)
    a[i] = readInt();
  q = readInt();
  forn(i, q) {
    l[i] = readInt() - 1;
    r[i] = readInt();
    k[i] = readInt();
  }
  
  int sorted = 1;
  forn(i, q - 1)
    sorted &= (l[i] <= l[i + 1] && r[i] <= r[i + 1]);
  int M = max(1, (int)sqrt(n));
  forn(i, q)
    g[sorted ? 0 : l[i] / M].push_back(i);

  forn(t, n / M + 1) {
    sort(g[t].begin(), g[t].end(), rless);
    int l0 = t * M, r0 = l0;
    multiset<int> s;
    forn(_i, g[t].size()) {  
      int i = g[t][_i];
      while (r0 < r[i]) T++, s.insert(a[r0++]);
      while (l0 < l[i]) T++, s.erase(s.find(a[l0++]));
      while (l0 > l[i]) T++, s.insert(a[--l0]);
      assert(l0 == l[i] && r0 == r[i]);
      multiset<int>::iterator it = s.begin();
      forn(j, k[i]) ans[i][j] = *it++;
    }
  }
  fprintf(stderr, "%d queries [sorted = %d]\n", T, sorted), fflush(stderr);
  forn(i, q)
    forn(j, k[i])
      writeInt(ans[i][j], " \n"[j == k[i] - 1]);
}
