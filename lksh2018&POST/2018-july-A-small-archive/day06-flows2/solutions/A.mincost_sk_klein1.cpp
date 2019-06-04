/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 *
 * Simple Klein's algo. Negative cycle = \Theta(VE).
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

typedef long long ll;

int cnt_edges = 0, cnt_cycles = 0;

template <const int maxV, const int _maxE>
struct Graph {
	static const int maxE = 2 * _maxE;
	int n, s, t, e, head[maxV], next[maxE], from[maxE], to[maxE], f[maxE], c[maxE], w[maxE];
	int cc, u[maxV], d[maxV], prev[maxE];

	void init( int N, int S, int T ) {
		n = N, s = S, t = T;
		e = 0, cc = 1;
		fill(u, 0), fill(head, -1);
	}

	int add( int a, int b, int x, int cost ) {
		assert(e + 2 <= maxE && a < maxV && b < maxV);
		next[e] = head[a], from[e] = a, to[e] = b, f[e] = 0, c[e] = x, w[e] = cost, head[a] = e++;
		next[e] = head[b], from[e] = b, to[e] = a, f[e] = 0, c[e] = 0, w[e] = -cost, head[b] = e++;
		return e - 2;
	}

	int k;
	int dfs( int v, int val ) {
		if (v == t) 
			return val;
		u[v] = cc;
		for (int x, e = head[v]; e != -1; e = next[e])
			if (f[e] + k <= c[e] && u[to[e]] != cc && (x = dfs(to[e], min(val, c[e] - f[e]))) > 0) {
				f[e] += x, f[e ^ 1] -= x;
				return x;
			}
		return 0;
	}

	void getMaxFlow() {
		for (k = 1 << 30; k > 0; k >>= 1) 
			for (cc++; dfs(s, INT_MAX); cc++)
				;
	}

	bool pushNegativeCycle() {
		fill(d, 0);
		cnt_cycles++;
		forn(i, n + 1) 
			forn(j, e) {
				cnt_edges++;
				if (f[j] < c[j] && d[to[j]] > d[from[j]] + w[j]) {
					d[to[j]] = d[from[j]] + w[j];
					prev[to[j]] = j;
					if (i == n) {
						vector<int> cycle;
						int push = INT_MAX;
						forn(_, n)
							j = prev[from[j]];
						for (int e = j; !cycle.size() || to[e] != to[j]; e = prev[from[e]]) {
							cycle.push_back(e);
							push = min(push, c[e] - f[e]);
						}
						for (int e : cycle)
							f[e] += push, f[e ^ 1] -= push;
						return 1;
					}
				}
			}
		return 0;
	}

	ll cost() {
		ll sum = 0;
		for (int i = 0; i < e; i += 2)
			sum += (ll)f[i] * w[i];
		return sum;
	}
};

const int N = 100, M = 1000;
Graph<N, M> g;

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int n, m, a, b, c, w;
	cin >> n >> m;
	g.init(n, 0, n - 1);
	while (m--) {
		cin >> a >> b >> c >> w;
		g.add(--a, --b, c, w);
	}
	g.getMaxFlow();
	while (g.pushNegativeCycle())
		;
	cout << g.cost() << endl;
	fprintf(stderr, "%d edges\n%d cycles\n", cnt_edges, cnt_cycles);
}
