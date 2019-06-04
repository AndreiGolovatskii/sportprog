/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 */

#include <bits/stdc++.h>
#include "optimization.h"

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef double dbl;
typedef long long ll;

const int maxlog = 17;
const int maxn = 1 << maxlog;
const int blen = 4;
const int base = 1e4;

struct num {
	dbl x, y;
	num() { }
	num( dbl a ) : x(cos(a)), y(sin(a)) { }
	num( dbl x, dbl y ) : x(x), y(y) { }
	num operator * ( double k ) const     { return num(x * k, y * k); }
	num operator + ( const num &a ) const { return num(x + a.x, y + a.y); }
	num operator - ( const num &a ) const { return num(x - a.x, y - a.y); }
	num operator * ( const num &a ) const { return num(x * a.x - y * a.y, x * a.y + y * a.x); }
	num ort() { return num(x, -y); }
};

char s[maxn * blen + 1];

void read( num *a, bool f ) {
	readWord(s);
	for (int j = 0, x = 1, i = strlen(s) - 1; i >= 0; i--) {
		(f ? a[j].y : a[j].x) += (s[i] - '0') * x, x *= 10;
		if (x == base)
			j++, x = 1;
	}
}

num a[maxn], b[maxn], f[maxn], root[maxn];
int rev[maxn];
ll res[maxn];

void fft( const num *a, num *res ) {
	forn(i, maxn)
		res[rev[i]] = a[i];
	for (int k = 1; k < maxn; k *= 2)
		for (int i = 0; i < maxn; i += 2 * k)
			forn(j, k) {
				num tmp = root[k + j] * res[i + j + k];
				res[i + j + k] = res[i + j] - tmp;
				res[i + j] = res[i + j] + tmp;
			}
}

void out( ll *a ) {
	int i = maxn - 1;
	while (i && !a[i])
		i--;
	writeInt((int)a[i--]);
	while (i >= 0)
		writeInt((int)a[i--], blen);
}

int main() {
	forn(i, maxn)
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (maxlog - 1));
	for (int k = 1; k < maxn; k *= 2) {
		num tmp(M_PI / k);
		root[k] = {1, 0};
		for (int i = 1; i < k; i++)
			root[k + i] = (i & 1) ? root[(k + i) >> 1] * tmp : root[(k + i) >> 1]; // Way #2
	}
	read(a, 0);
	read(a, 1);

	fft(a, f);
	forn(i, maxn / 2 + 1) {
		int j = i ? maxn - i : 0;
		num z0 = f[i], z1 = f[j];
		f[i] = num(z0.x + z1.x, z0.y - z1.y) * num(z0.y + z1.y, z1.x - z0.x) * 0.25;
		f[j] = f[i].ort();
	}
	fft(f, a);
	reverse(a + 1, a + maxn);
	forn(i, maxn)
		if ((res[i] += (ll)(a[i].x / maxn + 0.5)) >= base)
			res[i + 1] += res[i] / base, res[i] %= base;

	out(res);
	fprintf(stderr, "time = %.2f\n", 1. * clock() / CLOCKS_PER_SEC); // stamp
}
