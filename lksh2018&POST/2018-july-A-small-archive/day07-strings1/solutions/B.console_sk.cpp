/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int textLen = 1e6 + 2;
const int wordLen = 80 + 2;
const int maxN = 1000;
const int maxV = maxN * wordLen + 1;
const int E = 127 - 32;

int n, m, root = 0, vn = 1, Next[maxV][E], p[maxV], suf[maxV];
char is[maxV], pc[maxV];
int qst, qen, q[maxV];

char text[textLen], word[wordLen];

void add( char *s ) {
  int v = root;
  while (*s) {
    int ch = *s++ - 32;
    if (ch < 0) continue;
    int &r = Next[v][ch];
    if (!r) {
      assert(vn < maxV);
      p[vn] = v, pc[vn] = ch;
      r = vn++;
    }
    v = r;
  }
  is[v] = 1;
}

void build() {
  qst = qen = 0;
  q[qen++] = 0;
  while (qst < qen) {
    int v = q[qst++];
    forn(i, E)
      if (Next[v][i])
        q[qen++] = Next[v][i];
    if (!v || !p[v])
      suf[v] = 0;
    else {
      suf[v] = Next[suf[p[v]]][(int)pc[v]];
      is[v] |= is[suf[v]];
    }
    int *a = Next[suf[v]];
    forn(i, E)
      if (!Next[v][i])
        Next[v][i] = a[i];
  }
}

int main() {
  assert(scanf("%d", &m) == 1);
  fgets(word, wordLen, stdin);
  forn(i, m)
    fgets(word, wordLen, stdin), add(word);

  build();

  while (fgets(text, textLen, stdin)) {
    int v = 0;
    for (int i = 0; text[i]; i++) {
      if (text[i] < 32) continue;
      v = Next[v][text[i] - 32];
      if (is[v]) {
        printf("%s", text);
        break;
      }
    }
  }
}
