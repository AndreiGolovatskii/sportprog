/** OK, 0.003 sec, <1 mb */

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int mlen = 30000 + 1;

char s[mlen];
int n, pos = 1, ne[mlen][2], en[mlen], pr[mlen], ch[mlen];
int qSt, qEn, q[mlen], f[mlen];
int to[mlen][2], u[mlen];

void Add( int t, char *s ) {
  while (*s) {
    int cur = *s++ - '0', &r = ne[t][cur];
    if (r == -1) {
      pr[pos] = t;
      ch[pos] = cur;
      r = pos++;
    }
    t = r;
  }
  en[t] = 1;
}

void dfs( int v ) {
  int x;
  u[v] = 2;
  forn(i, 2)
    if (!en[x = to[v][i]]) {
      if (u[x] == 2) {
        puts("TAK");
        exit(0);
      }
      else if (!u[x])
        dfs(x);
    }
  u[v] = 1;
}

int main() {
  scanf("%d ", &n);
  memset(ne, -1, sizeof(ne));
  pr[0] = 0;
  while (n--)
    gets(s), Add(0, s);

  qSt = qEn = 0;
  q[qEn++] = 0;
  while (qSt < qEn) {
    int v = q[qSt++];
    forn(i, 2)
      if (ne[v][i] != -1)
        q[qEn++] = ne[v][i];
    int p = f[pr[v]];
    if (!pr[v]) {
      forn(i, 2)
        to[v][i] = (ne[v][i] != -1 ? ne[v][i] : to[f[v]][i]);
      continue;
    }
    while (p && ne[p][ch[v]] == -1)
      p = f[p];
    if (ne[p][ch[v]])
      p = ne[p][ch[v]];
    f[v] = p;
    if (en[p])
      en[v] = 1;
    forn(i, 2)
      if (ne[v][i] != -1)
        to[v][i] = ne[v][i];
      else
        to[v][i] = to[f[v]][i];
  }
  dfs(0);
  puts("NIE");
}
