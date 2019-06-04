/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define pb push_back
#define sz(a) (int)(a).size()

typedef long double dbl;
typedef long long ll;

const int N = 1 << 20;
const ll inf = 1e18;

int n, q, a[N];
vector<int> ind[N];
vector<dbl> xs[N];

dbl get( int i, dbl x ) {
	return a[i] + i * x;
}
dbl get_x( int i, int j ) {
	return (dbl)(a[i] - a[j]) / (j - i);
}

void build( int v, int vl, int vr ) {
	ind[v].pb(vl);
	for (int i = vl + 1; i < vr; i++) {
		while (sz(xs[v]) && get(ind[v].back(), xs[v].back()) <= get(i, xs[v].back()))
			ind[v].pop_back(), xs[v].pop_back();
		if (a[ind[v].back()] <= a[i]) 
			ind[v].pop_back();
		else
			xs[v].pb(get_x(ind[v].back(), i));
		ind[v].pb(i);
	}
	if (vr - vl == 1)
		return;
	int vm = (vl + vr) / 2;
	build(2 * v, vl, vm);
	build(2 * v + 1, vm, vr);
}

#define all(a) (a).begin(), (a).end()
#define BS(a, x) (lower_bound(all(a), x) - (a).begin())
ll inner_get( int v, int x ) {
	int pos = BS(xs[v], x);
	int i = ind[v][pos];
	return a[i] + (ll)i * x;
}

ll get( int v, int vl, int vr, int l, int r, int x ) {
	if (vr <= l || r <= vl)
		return -inf;
	if (l <= vl && vr <= r)
		return inner_get(v, x);
	int vm = (vl + vr) / 2;
	return max(get(2 * v, vl, vm, l, r, x), get(2 * v + 1, vm, vr, l, r, x));
}

int main() {
	int n = readInt();
	int q = readInt();
	forn(i, n) 
		a[i] = readInt();
	build(1, 0, n);
	while (q--) {
		int l = readInt() - 1;
		int r = readInt();
		int x = readInt();
		writeInt(get(1, 0, n, l, r, x) - (ll)(l - 1) * x, '\n'); 
	}
}
