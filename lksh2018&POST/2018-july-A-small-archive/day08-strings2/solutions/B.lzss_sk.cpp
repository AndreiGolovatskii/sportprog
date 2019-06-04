/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5;

struct Automaton {
	static const int VN = 2 * N + 1;
	int last, n, len[VN], suf[VN], pos[VN], to[VN][26];

	int newV( int l, int _suf ) {
		assert(n < VN);
		memset(to[n], 0, sizeof(to[n]));
		len[n] = l, suf[n] = _suf;
		return n++;
	}
	void init() {
		n = 1, pos[last = newV(0, 0)] = 0;
	}
	void add( int ch ) {
		int r, q, p = last;
		last = newV(len[last] + 1, 0);
		while (!to[p][ch])
			to[p][ch] = last, p = suf[p];
		if (!p)
			suf[last] = 1;
		else if (len[q = to[p][ch]] == len[p] + 1)
			suf[last] = q;
		else {
			r = newV(len[p] + 1, suf[q]);
			suf[last] = suf[q] = r, pos[r] = pos[q];
			memcpy(to[r], to[q], sizeof(to[r]));
			while (p && to[p][ch] == q)
				to[p][ch] = r, p = suf[p];
		}
	}
	void process( char *s ) {
		for (int k, i = 0; s[i]; i += k) {
			int v = 1, prev = 0;
			for (k = 0; v && pos[v] < i + k; k++)
				prev = v, v = s[i + k] ? to[v][s[i + k] - 'a'] : 0;
			if (--k <= 0)	
				writeInt(-1, ' '), writeInt(s[i], '\n'), k = 1;
			else
				writeInt(k, ' '), writeInt(pos[prev] - k, '\n');
		}
	}
} a;

char s[N + 1];

int main() {
	readWord(s);
	for (int t = 1; !seekEof(); t++) {
		readWord(s);
		writeWord("Case #"), writeInt(t), writeWord(":\n");
		a.init();
		for (int i = 0; s[i]; i++)
			a.add(s[i] - 'a'), a.pos[a.last] = i + 1;
		a.process(s);
	}
}
