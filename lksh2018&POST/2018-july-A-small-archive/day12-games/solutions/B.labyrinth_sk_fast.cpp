#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

template <const int V, const int E>
struct MultiList {
  int e, he[V], ne[E + 1], to[E + 1];
  MultiList() : e(1) { }
  void add( int v, int x ) {
    assert(e <= E);
    to[e] = x, ne[e] = he[v], he[v] = e++;
  }
};

const int maxN = 1e5, maxM = 1e5;
const int INF = 1e9;

enum {DRAW, WIN, LOSE};

int n, m, deg[maxN], res[maxN], len[maxN];
int qst, qen, q[maxN];

MultiList<maxN, maxM> c, rc;

void Win( int v );

void Lose( int v ) {
  if (res[v])
    return;
  res[v] = LOSE;
  for (int e = rc.he[v]; e; e = rc.ne[e])
    Win(rc.to[e]);
}

void Win( int v ) {
  if (res[v])
    return;
  res[v] = WIN;
  for (int x, e = rc.he[v]; e; e = rc.ne[e])
    if (!--deg[x = rc.to[e]])
      Lose(x);
}

void AddQ( int v, int res ) {
  len[v] = res;
  q[qen++] = v;
}

int main() {
  assert(freopen("labyrinth.in", "r", stdin));
  assert(freopen("labyrinth.out", "w", stdout));

  n = readInt();
  m = readInt();
  while (m--) {
    int a = readInt() - 1;
    int b = readInt() - 1;
    c.add(a, b);
    rc.add(b, a);
    deg[a]++;
  }
  forn(i, n)
    if (!c.he[i])
      Lose(i);

  forn(i, n) {
    len[i] = INF, deg[i] = 0;
    if (res[i] == WIN)
      for (int e = c.he[i]; e; e = c.ne[e])
        deg[i] += (res[c.to[e]] == LOSE);
  }
  forn(i, n)
    if (res[i] == LOSE && !c.he[i])
      AddQ(i, 0);

  while (qst < qen) {
    int v = q[qst++];
    for (int x, e = rc.he[v]; e; e = rc.ne[e])
      if (len[x = rc.to[e]] == INF)
        if (res[v] == WIN) {
          if (res[x] == LOSE)
            AddQ(x, len[v] + 1);
        } else {
          if (res[x] == WIN && --deg[x] == 0)
            AddQ(x, len[v] + 1);
        }
  }

  forn(i, n)
    if (res[i] == DRAW)
      writeWord("DRAW\n");
    else {
      writeWord(res[i] == WIN ? "WIN " : "LOSE ");
      if (len[i] == INF)
        writeWord("INF");
      else
        writeInt(len[i]);
      writeChar('\n');
    }
}
