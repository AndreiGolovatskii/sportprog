/**
 * Sergey Kopeliovich (burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

double getTime( double a, double b ) {
	// 1 = x^{-a} + x^{-b}
	double l = 1, r = 10;
	forn(t, 30) {
		double x = (l + r) / 2;
		if (1 < pow(x, -a) + pow(x, -b))
			l = x;
		else
			r = x;
	}
	return (l + r) / 2;
}

double get( double w2, double w3 ) {
	double w[] = {0, 0, w2, w3, 1};
	double ans = 0;
	int ra, rb, rc, rd;
	auto relax = [&]( int a, int b, int c, int d, double dx, double dy ) {
		double t =  getTime(dx, dy);
		if (t > ans)
			ans = t, ra = a, rb = b, rc = c, rd = d;
	};
	auto z = [&]( int i ) {
		return w[i] - w[i - 1];
	};

	// 3
	for (int a = 2; a <= 3; a++)
		for (int b = 2; b <= a; b++)
			for (int c = 2; c <= b; c++)
				relax(a, b, c, -1, w[3] + z(a) + z(b) + z(c), w[3] + w[a] + w[b] + w[c]);

	// 4
	for (int a = 2; a <= 4; a++)
		for (int b = 2; b <= a; b++)
			for (int c = 2; c <= b; c++)
				for (int d = 2; d <= c; d++)
					relax(a, b, c, d, w[4] + z(a) + z(b) + z(c) + z(d), w[4] + w[a] + w[b] + w[c] + w[d]);

	return ans;
}

double R() {
	return (double)rand() / RAND_MAX;
}
void optimize() {
	double l1 = 0, r1 = 1, l2 = 0, r2 = 1;
	while (r1 - l1 > 1e-6) {
		double opt = 1e9, optx = -1, opty = -1;
		forn(_, 50) {
			double x = l1 + R() * (r1 - l1);
			double y = l2 + R() * (r2 - l2);
			double tmp = get(x, y);
			if (tmp < opt)
				opt = tmp, optx = x, opty = y;
		}
		double size = ((r1 - l1) / 2) * 0.8;
		l1 = max(l1, optx - size);
		r1 = min(r1, optx + size);
		l2 = max(l2, opty - size);
		r2 = min(r2, opty + size);
	}
	double w2 = (l1 + r1) / 2;
	double w3 = (l2 + r2) / 2;
	printf("opt weights = %f %f : %f\n", w2, w3, get(w2, w3));
}
int main() {
	optimize();
}
