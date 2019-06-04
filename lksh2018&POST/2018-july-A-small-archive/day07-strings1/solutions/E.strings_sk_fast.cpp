/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int E = 26;
const int N = 1e6;
const int VN = 2 * N + 1;

int sn, n, root, last, Next[VN][E], len[VN], suf[VN];
char s[N + 1], t[N + 1];

inline int newV( int l, int _suf ) {
	assert(n < VN);
	len[n] = l, suf[n] = _suf;
	return n++;
}

void init() {
	n = 1, root = last = newV(0, 0);
	forn(i, E)
		Next[0][i] = 1;
}

void add_c( int ch ) {
	int R, Q, P = last;
	last = newV(len[last] + 1, 0);
	while (!Next[P][ch])
		Next[P][ch] = last, P = suf[P];
	if (!P)
		suf[last] = 1;
	else if (len[Q = Next[P][ch]] == len[P] + 1)
		suf[last] = Q;
	else {
		R = newV(len[P] + 1, suf[Q]);
		suf[last] = suf[Q] = R;
		memcpy(Next[R], Next[Q], sizeof(Next[R]));
		while (P && Next[P][ch] == Q)
			Next[P][ch] = R, P = suf[P];
	}
}

int res_l = -1, res_r = -1, res = INT_MIN;

inline void relax( int l, int r ) {
	int f = (r - l + 1) - max(l, sn - r - 1);
	if (f > res)
		res = f, res_l = l, res_r = r;
}

int main() {
	readWord(s), sn = strlen(s);
	readWord(t);
	init();
	for (int i = 0; t[i]; i++)
		add_c(t[i] - 'a');

	int v = root, r = 0, l = 0, x;
	while (s[l]) {
		r = max(r, l);
		while (s[r] && (x = Next[v][s[r] - 'a']) != 0)
			v = x, r++;
		if (v == root) {
			l++;
			continue;
		}
		while (len[suf[v]] < r - l)
			relax(l++, r - 1);
		v = suf[v];
	}
	printf("%d %d\n", res_l, res_r);
	return 0;
}
