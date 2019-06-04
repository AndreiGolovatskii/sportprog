/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * OK, O(nlogn), 0.817 sec, 61 mb
 */

#include <cstdio>
#include <cstring>
#include "optimization.h"

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxn = 1e6 + 1;

int last[maxn], P[maxn];
int n, root, p[maxn], x[maxn], sum[maxn];
int e = 1, ne[maxn], he[maxn], to[maxn];

int Get( int v ) {
  return (P[v] == v ? v : (P[v] = Get(P[v])));
}

void dfs( int v ) {
  int &L = last[x[v]];
  if (L != -1)
    sum[Get(L)]--;
  L = v;
  for (int i = he[v]; i; i = ne[i])
    dfs(to[i]), sum[v] += sum[to[i]];
  P[v] = p[v];
}

int main() {
  memset(last, -1, sizeof(last));
  n = readInt();
  forn(i, n) {
    p[i] = readInt() - 1;
    x[i] = readInt() - 1;
    sum[i] = 1, P[i] = i;
    if (p[i] == -1)
      root = i;
    else
      ne[e] = he[p[i]], to[e] = i, he[p[i]] = e++;
  }
  dfs(root);
  forn(i, n)
    writeInt(sum[i], ' ');
}
