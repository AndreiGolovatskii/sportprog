/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const int N = 1e5, VN = 2 * N;

char s[N + 1];
int t[VN][26];
int l[VN], r[VN], p[VN]; // ребро p[v] -> v это отрезок [l[v], r[v]) исходной строки
int cc, n, suf[VN], vn = 2, v = 1, pos; // идём по ребру из p[v] в v, сейчас стоим в pos

void go( int v ) {
	int no = cc++;
	forn(i, 26)
		if (t[v][i]) {
			int x = t[v][i];
			printf("%d %d %d\n", no, l[x], min(n, r[x]));
			go(x);
		}
}

void add() {
	for (; s[n]; n++) {
		int c = s[n] = tolower(s[n]) - 'a';
		auto new_leaf = [&]( int v ) {
			assert(vn < VN);
			p[vn] = v, l[vn] = n, r[vn] = N, t[v][c] = vn++;
		};
		go:;
		if (r[v] <= pos) { 
			if (!t[v][c]) {
				new_leaf(v), v = suf[v], pos = r[v];
				goto go;
			}
			v = t[v][c], pos = l[v] + 1;
		} else if (c == s[pos]) {
			pos++;
		} else {
			int x = vn++;
			l[x] = l[v], r[x] = pos, l[v] = pos;
			p[x] = p[v], p[v] = x;
			t[p[x]][(int)s[l[x]]] = x, t[x][(int)s[pos]] = v;
			new_leaf(x);
			v = suf[p[x]], pos = l[x];
			while (pos < r[x])
				v = t[v][(int)s[pos]], pos += r[v] - l[v];
			suf[x] = (pos == r[x] ? v : vn);
			pos = r[v] - (pos - r[x]);
			goto go;
		}
	}
}

int main() {
	assert(freopen("suftree.in", "r", stdin));
	assert(freopen("suftree.out", "w", stdout));

	assert(scanf("%s", s) == 1);
	forn(i, 26) t[0][i] = 1; // 0 = фиктивная, 1 = корень
	l[1] = -1;

	add();
	printf("%d\n", vn - 1);
	go(1);
}
