/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef long long ll;

int main() {
	int n = readInt();
	int m = readInt();
	struct Point {
		int x, y;
		Point operator - ( Point p ) { return {x - p.x, y - p.y}; }
		ll operator * ( Point p ) { return (ll)x * p.y - (ll)y * p.x; }
		ll d2() { return x * x + y * y; }
		bool operator < ( Point p ) const { return make_pair(x, y) < make_pair(p.x, p.y); }
		double ang() { return atan2(y, x); }
	};
	vector<int> a(n), b(n), c(n);
	vector<Point> p(m), h;
	forn(i, n) {
		a[i] = readInt();
		b[i] = readInt();
		c[i] = readInt();
	}
	unordered_set<ll> points;
	forn(i, m) {
		p[i].x = readInt();
		p[i].y = readInt();
		if (!points.insert((ll)p[i].x * (ll)1e9 + p[i].y).second)
			i--, m--, p.pop_back();
	}

	swap(p[0], *min_element(p.begin(), p.end()));
	sort(p.begin() + 1, p.end(), [&]( Point a, Point b) {
		a = a - p[0], b = b - p[0];
		ll x = a * b;
		return x > 0 || (x == 0 && a.d2() < b.d2());
	});
	for (auto q : p) {
		while (h.size() >= 2U && (q - h.back()) * (h.back() - h[h.size() - 2]) > 0)
			h.pop_back();
		h.push_back(q);
	}
	vector<double> ha;
	forn(i, h.size()) {
		double ang = (h[(i + 1) % h.size()] - h[i]).ang();
		if (i && ang < ha.back() - 1e-9) ang += 2 * M_PI;
		ha.push_back(ang);
	}
	auto get = [&]( int x, int y ) {
		double ang = atan2(y, x);
		if (ang < ha[0]) ang += 2 * M_PI;
		return (lower_bound(ha.begin(), ha.end(), ang) - ha.begin()) % ha.size();
	};

	vector<int> ans;
	forn(i, n) {
		int j1 = get(-b[i], a[i]);
		int j2 = get(b[i], -a[i]);
		auto f = [&]( int j ) { return (ll)a[i] * h[j].x + (ll)b[i] * h[j].y + c[i]; };
		if ((double)f(j1) * f(j2) <= 0)
			ans.push_back(i);
	}
	writeInt(ans.size(), '\n');
	for (int i : ans)
		writeInt(i + 1, ' ');
	writeChar('\n');
}
