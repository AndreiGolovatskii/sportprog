/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

template <const int maxV, const int _maxE>
struct Graph {
	static const int maxE = 2 * _maxE;
	int s, t, e, head[maxV], next[maxE], to[maxE], f[maxE], c[maxE];
	int cc, u[maxV];

	void init( int S, int T ) {
		s = S, t = T;
		e = 0, cc = 1;
		fill(u, 0), fill(head, -1);
	}

	int add( int a, int b, int x1, int x2 = 0 ) {
		assert(e + 2 <= maxE && a < maxV && b < maxV);
		next[e] = head[a], to[e] = b, f[e] = 0, c[e] = x1, head[a] = e++;
		next[e] = head[b], to[e] = a, f[e] = 0, c[e] = x2, head[b] = e++;
		return e - 2;
	}

	int dfs( int v ) {
		u[v] = cc;
		for (int e = head[v]; e != -1; e = next[e])
			if (f[e] < c[e] && u[to[e]] != cc && (to[e] == t || dfs(to[e]))) {
				f[e]++, f[e ^ 1]--;
				return 1;
			}
		return 0;
	}

	int getFlow() {
		while (dfs(s))
			cc++;
		return cc - 1;
	}
};

const int N = 20;

Graph<N * N + N + 2, 3 * N * N> g;

int n, a[N], b[N], c[N][N];

int main() {
	scanf("%d", &n);
	forn(i, n)
		scanf("%d", &a[i]);
	forn(i, n)
		scanf("%d", &b[i]);
	a[0] += b[0];
	forn(i, n)
		forn(j, n)
			scanf("%d", &c[i][j]);

	g.init(n, n + 1);
	int an = n + 2, cnt = 0;;
	forn(i, n)
		for (int j = 1; j < i; j++)
			if (c[i][j]) {
				int x = c[i][j];
				g.add(g.s, an, x);
				g.add(an, i, x);
				g.add(an, j, x);
				cnt += x, an++;
			}
	int bad = 0;
	forn(i, n) {
		int rest = a[0] - a[i];
		bad |= rest < 0;
		g.add(i, g.t, rest);
	}
	puts(bad || g.getFlow() != cnt ? "NO" : "YES");
}
