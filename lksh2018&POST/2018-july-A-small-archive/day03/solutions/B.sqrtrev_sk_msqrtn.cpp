/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int maxN = 1e5;
const int SIZE = 1500;

int mem[2][maxN];
int n, sn, *a = mem[0], *b = mem[1];

struct Seg {
	int st, len, rev, set;

	Seg() { }
	Seg( int _st, int _len, int _rev, int _set ) : st(_st), len(_len), rev(_rev), set(_set) { }

	int get( int x ) {
		if (set != -1)
			return set >= x ? len : 0;
		return (b + st + len) - lower_bound(b + st, b + st + len, x);
	}
};

Seg s[SIZE + 3];

void Init() {
	forn(i, n)
		b[i] = a[i];
	sn = 0;
	int pos = 0, x = n / (SIZE / 2) + 1;
	while (pos < n) {
		int p = min(pos + x, n);
		s[sn++] = Seg(pos, p - pos, 0, -1);
		sort(b + pos, b + p);
		pos = p;
	}
	s[sn].len = 1;
}

int Split( int x ) {
	int pos = 0, i = 0;
	while (pos + s[i].len <= x)
		pos += s[i++].len;
	if (pos != x) {
		memmove(s + i + 2, s + i + 1, sizeof(Seg) * (sn - i - 1));
		sn++;

		int k = x - pos;
		s[i + 1].set = s[i].set;
		s[i + 1].len = s[i].len - k;
		s[i].len = k;
		if (s[i].rev)
		{
			s[i + 1].rev = 1;
			s[i + 1].st = s[i].st;
			s[i].st += s[i + 1].len;
		}
		else
		{
			s[i + 1].rev = 0;
			s[i + 1].st = s[i].st + k;
		}
		forn(t, 2)
		{
			memcpy(b + s[i + t].st, a + s[i + t].st, s[i + t].len * sizeof(a[0]));
			sort(b + s[i + t].st, b + s[i + t].st + s[i + t].len);
		}
		s[sn].len = 1;
		i++;
	}
	return i;
}

int main() {
	n = readInt();
	forn(i, n)
		a[i] = readInt();
	Init();

	int m = readInt();
	while (m--)
	{
		char com[9];
		readWord(com);
		int l = Split(readInt() - 1);
		int r = Split(readInt());
		if (!strcmp(com, "get")) {
			int cnt = 0, x = readInt();
			while (l < r)
				cnt += s[l++].get(x);
			writeInt(cnt, '\n');
		} else if (!strcmp(com, "set"))	{
			int x = readInt();
			while (l < r)
				s[l++].set = x;
		}	else { // reverse
			reverse(s + l, s + r);
			while (l < r)
				s[l++].rev ^= 1;
		}		 

		if (sn >= SIZE)	{
			n = 0;
			forn(i, sn)
				if (s[i].set != -1)	{
					int x = s[i].set, m = s[i].len;
					while (m--)
						b[n++] = x;
				}	else {
					int pos = n, *A = a + s[i].st, m = s[i].len;
					while (m--)
						b[n++] = *A++;
					if (s[i].rev)
						reverse(b + pos, b + n);
				}
			swap(a, b);
			Init();
		}
	}
}
