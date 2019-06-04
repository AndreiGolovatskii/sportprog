/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

template <const int maxV, const int maxE>
struct Graph {
  int S, T, e, head[maxV], next[maxE], to[maxE], f[maxE], c[maxE];
  int cc, u[maxV];

  Graph() {
    e = 0, cc = 1;
    fill(u, 0), fill(head, -1);
  }

  void add( int a, int b, int x1, int x2 ) {
    assert(e + 2 <= maxE);
    next[e] = head[a], to[e] = b, f[e] = 0, c[e] = x1, head[a] = e++;
    next[e] = head[b], to[e] = a, f[e] = 0, c[e] = x2, head[b] = e++;
  }

  int dfs( int v ) {
    if (v == T) 
      return 1;
    u[v] = cc;
    for (int e = head[v]; e != -1; e = next[e])
      if (f[e] < c[e] && u[to[e]] != cc && dfs(to[e])) {
        f[e]++, f[e ^ 1]--;
        return 1;
      }
    return 0;
  }

  int getFlow() {
    int sum = 0;
    while (dfs(S))
      sum++, cc++;
    return sum;
  }
};

const int N = 51;

Graph<N * N + 2, N * N * 6> g; 

int main() {
  int h, w, sum = 0;
  scanf("%d%d ", &h, &w);
  auto get = [w]( int i, int j ) { return i * (w + 1) + j; };
  g.S = (h + 1) * (w + 1), g.T = g.S + 1;
  char s[w + 1];
  forn(i, h) {
    const char *str = ".HONC";
    scanf("%s", s);
    forn(j, w) {
      int x = strchr(str, s[j]) - str;
      sum += x;
      if ((i + j) & 1)
        g.add(g.S, get(i, j), x, 0);
      else
        g.add(get(i, j), g.T, x, 0);
      g.add(get(i, j), get(i + 1, j), 1, 1);
      g.add(get(i, j), get(i, j + 1), 1, 1);
    }
  }
  puts(sum && 2 * g.getFlow() == sum ? "Valid" : "Invalid");
}
