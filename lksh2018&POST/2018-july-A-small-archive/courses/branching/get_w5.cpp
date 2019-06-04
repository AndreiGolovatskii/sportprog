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

double get( double w2, double w3, double w4, bool debug = 0 ) {
	w3 = max(w2, w3);
	w4 = max(w3, w4);

	double w[] = {0, 0, w2, w3, w4, 1};
	double ans = 0;
	int ra, rb, rc, rd, re;
	auto relax = [&]( int a, int b, int c, int d, int e, double dx, double dy ) {
		double t =  getTime(dx, dy);
		if (t > ans)
			ans = t, ra = a, rb = b, rc = c, rd = d, re = e;
	};
	auto z = [&]( int i ) {
		return w[i] - w[i - 1];
	};

	// 3
	for (int a = 2; a <= 3; a++)
		for (int b = 2; b <= a; b++)
			for (int c = 2; c <= b; c++)
				relax(a, b, c, -1, -1, w[3] + z(a) + z(b) + z(c), w[3] + w[a] + w[b] + w[c]);

	// 4
	for (int a = 2; a <= 4; a++)
		for (int b = 2; b <= a; b++)
			for (int c = 2; c <= b; c++)
				for (int d = 2; d <= c; d++)
					relax(a, b, c, d, -1, w[4] + z(a) + z(b) + z(c) + z(d), w[4] + w[a] + w[b] + w[c] + w[d]);

	// 5
	for (int a = 2; a <= 5; a++)
		for (int b = 2; b <= a; b++)
			for (int c = 2; c <= b; c++)
				for (int d = 2; d <= c; d++)
					for (int e = 2; e <= d; e++)
						relax(a, b, c, d, e, w[5] + z(a) + z(b) + z(c) + z(d) + z(e), w[5] + w[a] + w[b] + w[c] + w[d] + w[e]);


	if (debug)
		printf("%d %d %d %d %d\n", ra, rb, rc, rd, re);
	return ans;
}

double R() {
	return (double)rand() / RAND_MAX;
}
void optimize() {
	double l1 = 0.5, r1 = 0.7, l2 = 0.8, r2 = 1, l3 = 0.9, r3 = 1;
	while (r1 - l1 > 1e-8) {
		double opt = 1e9, optx = -1, opty = -1, optz = -1;
		forn(_, 50) {
			double x = l1 + R() * (r1 - l1);
			double y = l2 + R() * (r2 - l2);
			double z = l3 + R() * (r3 - l3);
			double tmp = get(x, y, z);
			if (tmp < opt)
				opt = tmp, optx = x, opty = y, optz = z;
		}
		double size = ((r1 - l1) / 2) * 0.8;
		l1 = max(l1, optx - size);
		r1 = min(r1, optx + size);
		l2 = max(l2, opty - size);
		r2 = min(r2, opty + size);
		l3 = max(l3, optz - size);
		r3 = min(r3, optz + size);
	}
	double w2 = (l1 + r1) / 2;
	double w3 = (l2 + r2) / 2;
	double w4 = (l3 + r3) / 2;
	printf("opt weights = %f %f %f : %f\n", w2, w3, w4, get(w2, w3, w4, 1));
}
int main() {
	// printf("%.9f\n", getTime(1, 5));
	// printf("%.9f\n", get(0.6, 0.9));
	optimize();
}

