/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int textLen = 1e6;
const int wordLen = 80;
const int maxN = 1000;
const int maxV = maxN * wordLen + 1;
const int E = 127 - 32;

int n, m, root = 0, vn = 1, Next[maxV][E], p[maxV], suf[maxV];
char is[maxV], pc[maxV];

char text[textLen + 1], word[wordLen + 1];

int newV( int v, int ch ) {
  assert(vn < maxV);
  memset(Next[vn], -1, sizeof(Next[vn]));
  p[vn] = v, pc[vn] = ch;
  is[vn] = -1;
  suf[vn] = (!v ? 0 : -1);
  return vn++;
}

void add( char *s ) {
  int v = root;
  while (*s) {
    int ch = *s++ - 32, &r = Next[v][ch];
    if (r <= 0)  
      r = newV(v, ch);
    v = r;
  }
  is[v] = 1;
}

int getSuf( int v );
int getNext( int v, int c ) {
  int &r = Next[v][c];
  return r != -1 ? r : (r = getNext(getSuf(v), c));
}
int getSuf( int v ) {
  int &r = suf[v];
  return r != -1 ? r : (r = getNext(getSuf(p[v]), pc[v]));
}
int getIs( int v ) {
  char &r = is[v];
  return r != -1 ? r : (r = getIs(getSuf(v)));
}

int main() {
  m = readInt();
  forn(i, m) 
    readLine(word), add(word);

  while (!isEof()) {
    readLine(text);
    int v = 0;
    for (int i = 0; text[i]; i++) {
      v = getNext(v, text[i] - 32);
      if (getIs(v)) {
        puts(text);
        break;
      }
    }
  }
}
