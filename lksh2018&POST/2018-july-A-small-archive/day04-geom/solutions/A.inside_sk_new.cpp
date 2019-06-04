/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

struct Pnt {
	ll x, y;
	void read() {
		x = readInt();
		y = readInt();
	}
	Pnt operator - ( Pnt p ) { return {x - p.x, y - p.y}; }
	ll operator * ( Pnt p ) { return x * p.y - y * p.x; }
};

int main() {
	int n = readInt();
	vector<Pnt> p(n);
	forn(i, n)
		p[i].read();
	ll s = 0;
	forn(i, n)
		s += p[i] * p[(i + 1) % n];
	if (s > 0)
		reverse(p.begin() + 1, p.end());

	Pnt q;
	for (int k = readInt(); k > 0; k--) {
		q.read();
		int l = 1, r = n - 1;
		auto cmp = [&p]( Pnt a, Pnt b ) { return (a - p[0]) * (b - p[0]); };
		while (r - l > 1) {
			int m = (l + r) / 2;
			(cmp(p[m], q) < 0 ? l : r) = m;
		}
		ll c = (p[r] - p[l]) * (q - p[l]);
		if (c > 0 || cmp(q, p[1]) < 0 || cmp(q, p[n - 1]) > 0)
			puts("OUTSIDE");
		else if (c == 0 || !cmp(q, p[1]) || !cmp(q, p[n - 1]))
			puts("BORDER");
		else
			puts("INSIDE");
	}
}
