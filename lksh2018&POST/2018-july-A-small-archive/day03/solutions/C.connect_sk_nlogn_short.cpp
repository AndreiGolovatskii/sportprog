/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define forit(i, a) for (__typeof((a).begin()) i = (a).begin(); i != (a).end(); i++)
#define pb push_back
#define sz(a) (a).size()

const int N = 3e5;

struct edge {
	int a, b, l, r;
};
typedef vector<edge> List;

int cnt[N + 1], ans[N], u[N], color[N], deg[N];
vector<int> g[N];

void add( int a, int b ) {
	g[a].pb(b), g[b].pb(a);
}

void dfs( int v, int value ) {
	u[v] = 1, color[v] = value;
	for (int j : g[v])
		if (!u[j])
			dfs(j, value);
}

void go( int l, int r, const List &v, int vn, int add_vn ) { // [l, r)
	if (cnt[l] == cnt[r])
		return; // no queries, only changes
	if (!v.size()) {
		while (l < r)
			ans[l++] = vn + add_vn;
		return;
	}	

	List v1;
	forn(i, vn)
		g[i].clear();
	for (auto e : v)
		if (e.a != e.b) {
			if (e.l <= l && r <= e.r)
				add(e.a, e.b);
			else if (l < e.r && e.l < r)
				v1.pb(e);
		}

	int vn1 = 0;
	fill(u, u + vn, 0);
	forn(i, vn)
		if (!u[i])
			deg[vn1] = 0, dfs(i, vn1++);
	
	for (auto &e : v1) {
		e.a = color[e.a];
		e.b = color[e.b];
		if (e.a != e.b)
			deg[e.a]++, deg[e.b]++;
	}

	vn = vn1, vn1 = 0;
	forn(i, vn)
		u[i] = vn1, vn1 += (deg[i] > 0), add_vn += !deg[i];
	for (auto &e : v1) {
		e.a = u[e.a];
		e.b = u[e.b];
	}

	int m = (l + r) / 2; // [l, m) [m, r)
	go(l, m, v1, vn1, add_vn);
	go(m, r, v1, vn1, add_vn);
}

int main() {
	map<pair<int, int>, int> m;
	List v;
	int n = readInt();
	int k = readInt();
	forn(i, k) {
		char type = readChar();
		if (type == '+' || type == '-') {
			int a = readInt() - 1;
			int b = readInt() - 1;
			if (a == b) { // loop
				k--, i--;
				continue;
			}
			if (a > b)
				swap(a, b);

			if (type == '+')
				m[{a, b}] = i;
			else {
				int &j = m[{a, b}];
				v.pb({a, b, j, i});
				j = -1;
			}
		}
		else
			cnt[i + 1]++;
		cnt[i + 1] += cnt[i];
	}
	forit(it, m)
		if (it->second != -1)
			v.pb({it->first.first, it->first.second, it->second, k});

	go(0, k, v, n, 0);
	
	forn(i, k)
		if (cnt[i + 1] != cnt[i])
			writeInt(ans[i], '\n');
}
