/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
	
const int N = 2e5;

long long res = 0;

struct Automaton {
	static const int VN = 2 * N + 1;
	int root, last, n, len[VN], suf[VN];
	int to[VN][26];

	inline int newV( int l, int _suf ) {
		assert(n < VN);
		len[n] = l, suf[n] = _suf;
		return n++;
	}
	void init() {
		n = 1, root = last = newV(0, 0);
	}
	void add( int ch ) {
		int r, q, p = last;
		last = newV(len[last] + 1, 0);
		while (p && !to[p][ch])
			to[p][ch] = last, p = suf[p];
		if (!p)
			suf[last] = 1;
		else if (len[q = to[p][ch]] == len[p] + 1)
			suf[last] = q;
		else {
			r = newV(len[p] + 1, suf[q]);
			suf[last] = suf[q] = r;
			memcpy(to[r], to[q], sizeof(to[q]));
			while (p && to[p][ch] == q)
				to[p][ch] = r, p = suf[p];
		}
		res += len[last] - len[suf[last]];
		writeInt(res, '\n');
	}
} a;

char s[N + 1];

int main() {
	readLine(s);
	a.init();
	for (int i = 0; s[i]; i++) 
		a.add(s[i] - 'a');
}
