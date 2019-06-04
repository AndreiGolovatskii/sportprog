/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long double dbl;
typedef long long ll;
typedef pair<ll, ll> pii;

const dbl EPS = 1e-6;

struct pnt {
	dbl x, y;
	bool operator < ( pnt p ) const { return x < p.x; }
};
struct line {
	ll k, b;
	pnt intersect( line l ) {
		// k*x + b = l.k*x+l.b
		dbl x = (dbl)(l.b - b) / (k - l.k);
		return {x, k * x + b};
	}
	bool under( pnt p ) {
		return k * p.x + b + EPS < p.y;
	}
};

struct CHT {
	vector<line> l;
	vector<pnt> p;
	void addLine( ll k, ll b ) { 
		assert(l.empty() || l.back().k > k); // k decreases!
		line new_l = {k, b};
		while (!p.empty() && new_l.under(p.back()) > EPS)
			l.pop_back(), p.pop_back();
		if (!l.empty())
			p.push_back(l.back().intersect(new_l));
		l.push_back(new_l);
	}
	ll getMin( int x ) {
		int i = lower_bound(p.begin(), p.end(), pnt {(dbl)x, (dbl)0}) - p.begin();
		return l[i].k * x + l[i].b;
	}
} cht;

int main() {
	int n;
	scanf("%d", &n);
	vector<int> a(n), b(n);
	vector<long long> f(n, 1e18);
	forn(i, n) scanf("%d", &a[i]);
	forn(i, n) scanf("%d", &b[i]);
	f[0] = 0;
	for (int j = 1; j < n; j++) {
		cht.addLine(b[j - 1], f[j - 1]);
		f[j] = cht.getMin(a[j]);
	}
	printf("%lld\n", f[n - 1]);
}
