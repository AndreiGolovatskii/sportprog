/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 *
 * Time: O(nm) 
 * AC: 1.109 seconds
 * Comment: dfs from all vertices of the first part in order of decreasing w[v]
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fornd(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define sz(a) (int)(a).size()

const int maxN = 5003;

int n, m, e, wa[maxN], wb[maxN], v[maxN];
int pa1[maxN], pa2[maxN];
int cc, u2[maxN], color[maxN], p1[maxN], p2[maxN];
vector<int> c[maxN], ind[maxN];
int res, rn, r[maxN];

bool wless( int i, int j ) {
  return wa[i] > wa[j];
}

void dfs( int v, int col ) {
  int y;
  for (int x : c[v]) 
    if (u2[x] != cc) {
      color[x] = col, u2[x] = cc;
      if ((y = pa2[x]) != -1)
        p1[y] = v, dfs(y, col);
      else
        p2[x] = v;
    }
}

int main() {
  n = readInt();
  m = readInt();
  e = readInt();
  forn(i, n)
    pa1[i] = -1, wa[i] = readInt(), v[i] = i;
  forn(i, m)
    pa2[i] = -1, wb[i] = readInt();
  sort(v, v + n, wless);
  forn(i, e) {
    int a = readInt() - 1;
    int b = readInt() - 1;
    c[a].push_back(b);
    ind[a].push_back(i + 1);
  }

  int sum = 0, x;
  while (1) {
    cc++;
    forn(i, n)
      if (pa1[x = v[i]] == -1)
        p1[x] = -1, dfs(x, wa[x]);

    int rj = -1, res = -1, tmp;
    forn(j, m)
      if (pa2[j] == -1 && u2[j] == cc && res < (tmp = color[j] + wb[j]))
        res = tmp, rj = j;
    if (res == -1)
      break;    
    sum += res;
 
    x = rj;
    for (int tmp, v = p2[x]; v != -1; v = p1[v], x = tmp) 
      tmp = pa1[v], pa1[v] = x, pa2[x] = v;
  }
  forn(i, n)
    forn(j, c[i].size())
      if (c[i][j] == pa1[i])
        r[rn++] = ind[i][j], pa1[i] = -1;
  writeInt(sum, '\n');
  writeInt(rn, '\n');
  forn(i, rn)
    writeInt(r[i], " \n"[i == rn - 1]);
}
