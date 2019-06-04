/** Refactored by Burunduk1 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

const double eps = 1e-7, pi = acos(-1.0);

typedef long long ll;

struct point {
	int x, y;
	double a;
	point operator + (const point &p) const { return {x + p.x, y + p.y}; }
	point operator - (const point &p) const { return {x - p.x, y - p.y}; }
	ll operator * (const point &p) const { return (ll)x * p.y - (ll)y * p.x; }
	double len() const { return sqrt((ll)x*x + (ll)y*y); }
	void neg() { x = -x, y = -y; }
	void scan()	{ x = readInt(), y = readInt(); }
	void calcAlpha() { 
		a = atan2(y,x); 
		if (a < -eps)
			a += 2*pi;
	}
	bool operator < (const point & p) const { return a < p.a; }
};

bool lessp(const point &p1, const point & p2) {
	return fabs(p1.y - p2.y) > eps ? p1.y < p2.y : p1.x < p2.x;
}

const int size = 5e4;

vector<point> ps;
point p[size+1]; 

struct polygon {
	point min;
	int n;
	void read( int i ) {
		forn(j, n) {
			p[j].scan();
			if (i == 0)
				p[j].neg();
			if (!j || lessp(p[j], min))
				min = p[j];
		}
		p[n] = p[0];
		forn(j, n)
			ps.push_back(p[j+1] - p[j]);
	}
} poly[2];

int main() {
	poly[0].n = readInt();
	poly[1].n = readInt();
	ps.reserve(poly[0].n + poly[1].n);
	forn(i, 2) 
		poly[i].read(i);
	for (auto &x : ps)
		x.calcAlpha();
	sort(ps.begin(), ps.end());
	double ans = 1e100;
	point p1 = poly[0].min + poly[1].min, p2;
	for (auto x : ps) {
		p2 = p1 + x;
		ans = min(ans, (p1 * p2) / x.len());
		p1 = p2;
	}
	printf("%.10f\n", max(0., ans - 60));
}
