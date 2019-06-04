/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 50, L = 512, LEN = 1e5, L1 = L - 1;
const int VN = L * L / 2;

char s[N][L + 1], t[LEN + 1], pc[VN];
int tn, n, f[L][N + 1], len[LEN + 1][N];
int vn, Next[VN][26], p[VN], suf[VN], dep[VN];

inline void relax( int &a, int b ) {
  a = min(a, b);
}

inline int newV( int parent, int c ) {
  assert(vn < VN);
  p[vn] = parent, pc[vn] = c;
  suf[vn] = (!vn || !parent) ? 0 : -1;
  dep[vn] = !vn ? 0 : (1 + dep[parent]);
  memset(Next[vn], -1, sizeof(Next[0]));
  return vn++;
}

int getNext( int v, int c );

inline int getSuf( int v ) {
  return suf[v] != -1 ? suf[v] : (suf[v] = getNext(getSuf(p[v]), pc[v]));
}

inline int getNext( int v, int c ) {
  return Next[v][c] != -1 ? Next[v][c] : (Next[v][c] = (!v ? 0 : getNext(getSuf(v), c)));
}

int main() {
  n = readInt();
  forn(i, n) 
    readLine(s[i]);
  readLine(t), tn = strlen(t);
  forn(i, tn)
    t[i] -= 'a';
  forn(i, n) {
    vn = 0, newV(0, 0);
    int v, pos;
    for (char *y, *x = s[i]; *x; x++) 
      for (y = x, v = 0; *y; ) {
        int c = *y++ - 'a', &r = Next[v][c];
        if (r == -1)
          r = newV(v, c);
        v = r;
      }
    v = 0, pos = 0;
    forn(j, tn) {
      v = getNext(v, t[j]);
      while (pos < j + 1 - dep[v]) 
        len[pos][i] = j - pos, pos++;
    }
    while (pos < tn)
      len[pos][i] = tn - pos, pos++;
  }
  fprintf(stderr, "build & read\n");

  memset(f, 0x10, sizeof(f));
  f[0][n] = 0;
  forn(i, tn) {
    int mi = *min_element(f[i & L1], f[i & L1] + n + 1) + 1;
    memset(f[(i + L - 1) & L1], 0x10, sizeof(f[0]));
    forn(j, n + 1)
      relax(f[i & L1][j], mi);
    forn(j, n + 1) {
      relax(f[(i + 1) & L1][j], f[i & L1][j] + 1);
      if (j < n) 
        relax(f[(i + len[i][j]) & L1][j], f[i & L1][j] + 1);
    }
  }
  printf("%d\n", *min_element(f[tn & L1], f[tn & L1] + n + 1));
  return 0;
}
