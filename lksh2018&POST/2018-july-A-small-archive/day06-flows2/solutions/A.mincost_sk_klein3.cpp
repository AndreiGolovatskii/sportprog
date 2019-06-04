/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 *
 * Klein's algo with cost scaling. Negative cycle with queue.
 */

#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define fill(a, x) memset(a, x, sizeof(a))

const double eps = 1e-12;

typedef long long ll;

int cnt_edges = 0, cnt_cycles = 0;

template <const int maxV, const int _maxE>
struct Graph {
	static const int maxE = 2 * _maxE;
	int n, s, t, e, head[maxV], next[maxE], from[maxE], to[maxE], f[maxE], c[maxE], w[maxE];
	int cc, u[maxV], prev[maxE];
	int head2[maxV], next2[maxE];
	double d[maxV];

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

	bool pushNegativeCycle( double delta ) {
		fill(head2, -1);
		forn(j, e)
			if (f[j] < c[j])
				next2[j] = head2[from[j]], head2[from[j]] = j;

		fill(d, 0), fill(prev, -1), fill(u, 0);
		queue<int> q;
		forn(v, n)
			q.push(v), u[v] = 1;
		int cnt = 0;
		cnt_cycles++;
		while (q.size()) {
			int v = q.front(); q.pop();
			u[v] = 0; // not in queue
			for (int x, j = head2[v]; j != -1; j = next2[j]) {
				cnt_edges++, cnt++;
				if (d[x = to[j]] > d[from[j]] + w[j] - delta + eps) {
					d[x] = d[from[j]] + w[j] - delta;
					prev[x] = j;
					if (!u[x])
						q.push(x), u[x] = 1;
					if (++cnt >= n) {
						cnt = 0;
						int push = INT_MAX, p = j;
						for (int _ = 0; _ < n && p != -1; _++) {
							p = prev[from[p]];
						}
						if (p == -1)
							continue;
						vector<int> cycle;
						for (int e = p; !cycle.size() || to[e] != to[p]; e = prev[from[e]]) {
							cycle.push_back(e);
							push = min(push, c[e] - f[e]);
						}
						ll sum = 0;
						for (int e : cycle) {
							sum += w[e];
							f[e] += push, f[e ^ 1] -= push;
						}
						return 1;
					}
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
	int n, m, a, b, c, w, maxC = 0;
	cin >> n >> m;
	g.init(n, 0, n - 1);
	while (m--) {
		cin >> a >> b >> c >> w;
		g.add(--a, --b, c, w);
		maxC = max(maxC, abs(w));
	}
	g.getMaxFlow();
	for (double delta = -maxC; delta * (n + 1) <= -0.5; delta *= 0.5) {
		while (g.pushNegativeCycle(delta))
			;
		// fprintf(stderr, "delta = %g: %d edges, %d cycles, final cost = %lld\n", delta, cnt_edges, cnt_cycles, g.cost());
		// cnt_edges = cnt_cycles = 0;
	}
	cout << g.cost() << endl;
	fprintf(stderr, "%d edges\n%d cycles\n", cnt_edges, cnt_cycles);
}
