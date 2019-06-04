/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * OK, O(nlogn), 1.136 sec, 217 mb
 */

#include "optimization.h"
#include <cstdio>
#include <unordered_set>
#include <cassert>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int MAX_MEM = (int)2.5e8;

int mpos, max_mpos;
char mem[MAX_MEM];

inline void * operator new ( size_t n ) {
  char *res = mem + mpos;
  mpos += n;
  assert(mpos <= MAX_MEM);
  return (void *)res;
}

inline void operator delete ( void * ) { }

/**
 * Main part 
 */

const int maxn = 1e6 + 1;

int root, n, col[maxn], ans[maxn];
int e = 1, ne[maxn], he[maxn], to[maxn];

void Calc( int v, unordered_set <int> &s ) {
  s.insert(col[v]);
  for (int i = he[v]; i; i = ne[i]) {
    unordered_set <int> tmp;
    Calc(to[i], tmp);
    if (s.size() < tmp.size())
      s.swap(tmp);
    for (auto x : tmp)
      s.insert(x);
  }
  ans[v] = s.size();
}

int main() {
  n = readInt();
  forn(i, n) {
    int p = readInt() - 1;
    col[i] = readInt();
    if (p == -1)
      root = i;
    else
      ne[e] = he[p], to[e] = i, he[p] = e++;
  }

  unordered_set<int> tmp;
  Calc(root, tmp);
  forn(i, n)
    writeInt(ans[i], ' ');
}
